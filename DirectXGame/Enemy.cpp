#include "Enemy.h"

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// nullcheak
	assert(model);
	//
	textureHandle_ = TextureManager::Load("cube/cube.jpg");
	// 3Dモデル
	model_ = model;
	/// 3.ワールド変換の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセットする
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	worldTransform_.scale_ = {3, 3, 3};
	}
// メンバ関数ポインタのテーブル
	void(Enemy::*Enemy::spFuncTable[])() = {&Enemy::ApproachAction, &Enemy::LeaveAction};



void Enemy::Update() {

	/// フェーズによって行動を変化させる
	//switch (phase_) {
	//case Enemy::Phase::Approach:
	//default:
	//	ApproachAction;
	//	break;
	//case Enemy::Phase::Leave:
	//	LeaveAction;
	//	break;
	//}
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void Enemy::ApproachAction() {

	// approachの速度に変更
	velocity_ = {0, 0, -1};

	// 座標を移動させる(１フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;

	// 基底の位置に到達したら離脱
	if (worldTransform_.translation_.z < 50.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveAction() {
	velocity_ = {1, 1, -1};
	// 座標を移動させる(１フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
}
