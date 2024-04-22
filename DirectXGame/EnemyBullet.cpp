#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);
	model_ = model;
	//テクスチャ読込
	textureHandle_ = TextureManager::Load("axis/axis.jpg");
	//ワールドトランスフォーム
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;

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
