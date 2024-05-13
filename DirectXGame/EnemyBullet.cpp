#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);
	model_ = model;
	//テクスチャ読込
	textureHandle_ = TextureManager::Load("axis/axis.jpg");
	//ワールドトランスフォーム
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	//球を伸ばす
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	//進行方向に弾丸を向ける
	velocity_ = velocity;
	

	///*	解法２を実施	*///
	//Y軸周りの角度(0y)
	worldTransform_.rotation_.y = std::atan2(velocity_.x,velocity_.z);
	//横軸方向の長さを求める
	float velocityXZLen = Vector2Length(velocity_.x, velocity_.z);
	//X軸周りの角度(0x)
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZLen);
}

void EnemyBullet::Update() { 
	
	worldTransform_.translation_ += velocity_;
	//行列を計算転送
	worldTransform_.UpdateMatrix();

	if (--deathTimer_<0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
