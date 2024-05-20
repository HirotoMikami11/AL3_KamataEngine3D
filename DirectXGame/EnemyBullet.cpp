#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, uint32_t textureHandle, const Vector3& position, const Vector3& velocity) {

	assert(model);
	model_ = model;
	//テクスチャ読込
	textureHandle_ = textureHandle;
	//ワールドトランスフォーム
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	radius_ = 1;

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
void EnemyBullet::OnCollision() { isDead_ = true; }

Vector3 EnemyBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
