#include <Player.h>
#include <WinApp.h>

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		// bulletの開放
		delete bullet;
	}
	delete sprite2DReticle_;
}

void Player::Initialize(Model* model, uint32_t playerTextureHandle, uint32_t bulletTextureHandle, const Vector3& position) {
	/// nullptrチェック
	assert(model);

	/// ワールド変換の初期化
	// 自機本体
	worldTransform_.Initialize();
	// 3Dレティクル
	worldTransform3Dreticle_.Initialize();

	/// データをメンバ変数に移し替える
	// テクスチャハンドル
	textureHandle_ = playerTextureHandle;
	bulletTextureHandle_ = bulletTextureHandle;
	// レティクル用テクスチャの取得
	uint32_t reticleTexture = TextureManager::Load("reticle.png");

	// 3Dモデルデータ
	model_ = model;
	// スプライト生成
	sprite2DReticle_ = Sprite::Create(reticleTexture, {640, 360}, {1, 1, 1, 1}, {0.5f, 0.5f});

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	worldTransform_.translation_ = position;

	matViewport= MakeViewportMatrix(0, 0, 1280, 720, 0, 1);
	radius_ = 1;
}

void Player::Update(const ViewProjection& viewProjection) {
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
	worldTransform_.translation_ += move;

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
	/// 　3Dレティクルの配置
	//

	// 自機のワールド座標から3Dレティクルのワールド座標を計算
	Set3DreticlePosition();

	convertWorldToScreenCoordsReticle(viewProjection);
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
	// ImGui::InputFloat3("Player");

	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	/// 弾丸を表描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	model_->Draw(worldTransform3Dreticle_, viewProjection);
};

void Player::DrawUI() { sprite2DReticle_->Draw(); }

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

		//// 弾丸の速度
		const float kBulletSpeed = 3.0f;

		Vector3 velocity = Vector3Subtract(GetWorldPosition3Dreticle(), GetWorldPosition());

		velocity = Vector3Multiply(kBulletSpeed, Vector3Normalize(velocity));

		// 弾丸を生成・初期化する
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, bulletTextureHandle_, GetWorldPosition(), velocity);
		// 弾丸を登録する
		bullets_.push_back(newBullet);
	}
}

void Player::OnCollision() {
	// 何もしない
}

/// <summary>
/// 3Dレティクルの配置
/// </summary>
void Player::Set3DreticlePosition() {
	// 自機のワールド座標から3Dレティクルのワールド座標を計算

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;
	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = {0, 0, 1.0f};
	// 自機のワールド行列の回転を反映
	offset = TransforNormal(offset, worldTransform_.matWorld_);
	// ベクトルの長さを整える
	offset = Vector3Multiply(kDistancePlayerTo3DReticle, offset);
	// 3Dレティクルの座標を設定する
	worldTransform3Dreticle_.translation_ = Vector3Add(GetWorldPosition(), offset);

	worldTransform3Dreticle_.UpdateMatrix();
}

void Player::convertWorldToScreenCoordsReticle(const ViewProjection& viewProjection) {
	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
	Vector3 positionReticle = GetWorldPosition3Dreticle();



	// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport = Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));

	// ワールドからスクリーン座標へ座標変換(ここで3Dから2Dに)
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	// スプライトのレティクルに座標変換
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}

void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Vector3 Player::GetWorldPosition3Dreticle() {
	// ワールド座標を入れる変数
	Vector3 worldPos3Dreticle;

	// ワールド行列の平行移動成分を取得
	worldPos3Dreticle.x = worldTransform3Dreticle_.matWorld_.m[3][0];
	worldPos3Dreticle.y = worldTransform3Dreticle_.matWorld_.m[3][1];
	worldPos3Dreticle.z = worldTransform3Dreticle_.matWorld_.m[3][2];
	return worldPos3Dreticle;
}
