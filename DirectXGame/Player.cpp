#include <Player.h>

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		// bulletの開放
		delete bullet;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
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

	radius_ = 1;
}

void Player::Update() {
	//
	/// 寿命が尽きた弾丸を消滅させる
	//
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

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

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
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

	/// 弾丸を表描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
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

		// 弾丸の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransforNormal(velocity, worldTransform_.matWorld_);

		// 弾丸を生成・初期化する
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);
		// 弾丸を登録する
		bullets_.push_back(newBullet);
	}
}

void Player::OnCollision() {
	//何もしない
}

Vector3 Player::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}