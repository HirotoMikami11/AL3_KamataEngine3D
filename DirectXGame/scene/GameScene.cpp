#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"

#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelSkydome_;
	delete player_;
	delete debugCamera_;
	for (Enemy* enemy_ : enemies_) {
		delete enemy_;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	delete skydome_;
	delete railCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	playerTextureHandle_ = TextureManager::Load("uvChecker.png");
	playerBulletTextureHandle_ = TextureManager::Load("white1x1.png");
	enemyTextureHandle_ = TextureManager::Load("cube/cube.jpg");
	enemyBulletTextureHandle_ = TextureManager::Load("axis/axis.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skyDome", true);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// デバッグカメラの生成(引数は画面の横幅、縦幅)
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	
	// レールカメラの生成
	railCamera_ = new RailCamera();
	railCamera_->Initialize({0, 0, 0}, {0, 0, 0});

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// 自キャラの生成
	player_ = new Player();
	Vector3 playerPos(0, 0, railCamera_->GetPositionZ() + 15);
	// 自キャラの初期化
	player_->Initialize(model_,playerTextureHandle_, playerBulletTextureHandle_, playerPos);

	/// csvロードするよ
	LoadEnemyPopData();
	AddEnemy(Vector3(0, 10, 200));

	// 天球の生成・初期化
	skydome_ = new SkyDome();
	skydome_->Initialize(modelSkydome_);

	// 自キャラとレールカメラの親子関係を結ぶ
	player_->SetParent(&railCamera_->GetWorldTrasnform());
}

void GameScene::Update() {

	player_->Update(viewProjection_);

	/// 敵の出現コマンド
	UpdateEnemyPopCommands();

	/// 敵リストの更新
	for (Enemy* enemy_ : enemies_) {
		if (enemy_ != nullptr) {
			enemy_->Update();
		}
	}

	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});
	/// 敵弾リストの更新
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

	/// 寿命が尽きた敵の弾丸を消滅させる
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	CheakAllCollision();

#ifdef _DEBUG
	//
	///	デバッグカメラ
	//

	/// ENTERキーでデバッグカメラの有効フラグをトグル
	if (input_->TriggerKey(DIK_RETURN)) {
		if (isDebugCameraActive_) {
			isDebugCameraActive_ = false;
		} else {
			isDebugCameraActive_ = true;
		}
	}

	/// カメラの処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		/// レールカメラ
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
		// ビュープロジェクション行列の更新と転送
		// viewProjection_.UpdateMatrix();
	}

#endif
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 天球
	skydome_->Draw(viewProjection_);

	// 自キャラの描画
	player_->Draw(viewProjection_);
	// 敵を描画
	for (Enemy* enemy_ : enemies_) {
		if (enemy_ != nullptr) {
			enemy_->Draw(viewProjection_);
		}
	}
	// 敵弾丸の描画
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//2DのUiを描画
	player_->DrawUI();
	//


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheakAllCollision() {
	// 判定対象のAとBの座標
	Vector3 posA, posB;

	// 自機弾丸リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

#pragma region "自機と敵弾丸の当たり判定"

	// 自機の座標.
	posA = player_->GetWorldPosition();
	// 自機と敵弾丸全ての当たり判定
	for (EnemyBullet* EBullet : enemyBullets_) {
		// 敵弾丸の座標
		posB = EBullet->GetWorldPosition();
		// 自機と敵弾丸の距離
		float AtoBDistance = Vector3Distance(posA, posB);

		// 衝突していたら~~
		if (AtoBDistance <= powf((player_->GetRadius() + EBullet->GetRadius()), 2)) {

			// 自機の衝突時コールバックを呼び出す
			player_->OnCollision();
			// 自機の衝突時コールバックを呼び出す
			EBullet->OnCollision();
		}
	}

#pragma endregion

#pragma region "自機弾丸と敵の当たり判定"
	for (Enemy* enemy_ : enemies_) {
		// 敵の座標
		posB = enemy_->GetWorldPosition();
		for (PlayerBullet* bullet : playerBullets) {
			// 自機弾丸の座標
			posA = bullet->GetWorldPosition();
			// 敵と自機弾丸の距離
			float AtoBDistance = Vector3Distance(posA, posB);
			// 衝突していたら~~
			if (AtoBDistance <= powf((enemy_->GetRadius() + bullet->GetRadius()), 2)) {

				// 敵の衝突時コールバックを呼び出す
				enemy_->OnCollision();
				// 自機弾丸の衝突時コールバックを呼び出す
				bullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region "自機弾丸と敵弾丸の当たり判定"
	// 敵の座標

	for (PlayerBullet* PBullet : playerBullets) {
		// 自機弾丸の座標
		posA = PBullet->GetWorldPosition();
		for (EnemyBullet* EBullet : enemyBullets_) {
			// 敵弾丸の座標
			posB = EBullet->GetWorldPosition();
			// 自機弾丸と敵弾丸の距離
			float AtoBDistance = Vector3Distance(posA, posB);
			// 衝突していたら~~
			if (AtoBDistance <= powf((PBullet->GetRadius() + EBullet->GetRadius()), 2)) {

				// 自機弾丸の衝突時コールバックを呼び出す
				PBullet->OnCollision();
				// 敵弾丸の衝突時コールバックを呼び出す
				EBullet->OnCollision();
			}
		}
	}
#pragma endregion
}

/// <summary>
/// 敵弾を追加する
/// </summary>
/// <param name="enemyBullet">敵弾</param>
void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::AddEnemy(const Vector3& position) {
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(model_, enemyTextureHandle_,enemyBulletTextureHandle_,position, {0, 0, -1});
	// リストに登録する
	enemies_.push_back(newEnemy);
	// 敵に自キャラのアドレスを渡し、GameSceneがenemy_にplayer_を貸し出す
	newEnemy->SetPlayer(player_);
	// 敵キャラにゲームシーンを渡す
	newEnemy->SetGameScene(this);
}

/// <summary>
/// 敵発生データの読み込み
/// </summary>
void GameScene::LoadEnemyPopData() {

	// ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {

	if (isWait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			isWait = false;
		}
		return;
	}

	// 1行列の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくなる
		std::istringstream line_stream(line); // 1行取り出す

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ','); //,が現れるまでの文字列をwordに入れる

		//"//"から始める行はコメント
		if (word.find("//") == 0) {
			// コメント行列を飛ばす
			continue;
		}

		//
		/// POPコマンド
		//
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵発生
			AddEnemy(Vector3(x, y, z));
		}

		//
		/// WAITコマンド
		//
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');
			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWait = true;
			waitTimer = waitTime;
			// コマンドループを抜ける
			break;
		}
	}
}