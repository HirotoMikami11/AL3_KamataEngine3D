#include "EnemyBullet.h"
// ヘッダ同士でインクルードしあっていないのでセーフ
#include "Player.h"
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);
	model_ = model;
	// テクスチャ読込
	textureHandle_ = TextureManager::Load("axis/axis.jpg");
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	// 球を伸ばす
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	// 速度を代入
	velocity_ = velocity;
	///*		進行方向に弾丸を向ける 解法２を実施	*///
	// Y軸周りの角度(0y)
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	// 横軸方向の長さを求める
	velocityXZLen_ = Vector2Length(velocity_.x, velocity_.z);
	// X軸周りの角度(0x)
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZLen_);
	t_ = 0.05f;
}

void EnemyBullet::Update() {
	// 敵弾丸から自キャラへのベクトルを計算
	toPlayer_ = Vector3Subtract(player_->GetWorldPosition(), GetWorldPosition());
	// ベクトルを正規化する
	toPlayer_ = Vector3Normalize(toPlayer_);
	velocity_ = Vector3Normalize(velocity_);

	// 球面線形補間により、今の速度と自キャラへのベクトルを内挿し、新たな速度とする
	velocity_ = Vector3Multiply(1.5f, MySlerp(velocity_, toPlayer_, t_));
	MySlerp(velocity_, toPlayer_, t_);

	// 進行方向に見た目の回転を合わせる(ex1で行ったもの)
	// Y軸周りの角度(0y)
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	// 横軸方向の長さを求める
	velocityXZLen_ = Vector2Length(velocity_.x, velocity_.z);
	// X軸周りの角度(0x)
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZLen_);

	// 速度を座標に与える
	worldTransform_.translation_ += velocity_;
	// 行列を計算転送
	worldTransform_.UpdateMatrix();

	if (--deathTimer_ < 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 EnemyBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}