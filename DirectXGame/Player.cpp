#include <Player.h>

Player::~Player() {
	//bulletの開放
	delete bullet_;
}

void Player::initialize(Model* model, uint32_t textureHandle) {
	/// 1.nullptrチェック
	assert(model);

	/// 2.データをメンバ変数に移し替える
	// テクスチャハンドル
	textureHandle_ = textureHandle;
	// 3Dモデルデータ
	model_ = model;

	/// 3.ワールド変換の初期化
	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
	//
	///	キーボード入力によって回転ベクトルを変更する処理
	//

	Rotate();

	//
	///	キーボード入力によって移動ベクトルを変更する処理
	//

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_ = Vector3Add(worldTransform_.translation_, move);

	// 移動限界座標
	const float kMoveLimitX = 32.0f;
	const float kMoveLimitY = 18.0f;
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);

	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	//
	///  行列更新
	//

	worldTransform_.UpdateMatrix();



	//
	/// キャラクター攻撃処理
	//
	Attack();

	if (bullet_) {
		bullet_->Update();
	}




	//
	/// 　ImGui
	//

	ImGui::Begin("Position");

	/// キャラクターの座標を画面表示する処理
	ImGui::SliderFloat3("Player", &worldTransform_.translation_.x, -50.0f, 50.0f);

	ImGui::End();

}

void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	
	///弾丸を表描画
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}

};

void Player::Rotate() {
	/// 回転速さ[radian/frame]
	const float kRotSpeed = 0.02f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
}

void Player::Attack() {
	// SPACEキーで発射
	if (input_->TriggerKey(DIK_SPACE)) {

		//弾丸があれば解放する
		if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}

	//弾丸を生成・初期化する
		PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(model_,worldTransform_.translation_);
	//弾丸を登録する
	bullet_ = newBullet;
	}
}
