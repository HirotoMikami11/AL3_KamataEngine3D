#include "Enemy.h"

// ヘッダ同士でインクルードしあっていないのでセーフ
#include "GameScene.h"
#include "Player.h"

Enemy ::~Enemy() {}

void Enemy::Initialize(Model* model, uint32_t enemyTextureHandle, uint32_t bulletTextureHandle, const Vector3& position, const Vector3& velocity) {
	// nullcheak
	assert(model);

	//
	textureHandle_ = enemyTextureHandle;
	bulletTextureHandle_ = bulletTextureHandle;

	// 3Dモデル
	model_ = model;
	/// 3.ワールド変換の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセットする
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	worldTransform_.scale_ = {3, 3, 3};
	radius_ = 3;
}

// メンバ関数ポインタのテーブル
void (Enemy::*Enemy::spFuncTable[])() = {&Enemy::ApproachAction, &Enemy::LeaveAction};

void Enemy::Update() {

	// 発射間隔
	fireTimer_--;
	if (fireTimer_ <= 0) {
		Fire();
		// インターバルの値に戻す
		fireTimer_ = kfireInterval;
	}

	/// フェーズによって行動を変化させる
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void Enemy::ApproachAction() {

	// approachの速度に変更
	velocity_ = {0, 0, -0.5f};

	// 座標を移動させる(１フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;

	// 基底の位置に到達したら離脱
	if (worldTransform_.translation_.z < 50.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveAction() {
	velocity_ = {0.5f, 0.5f, -0.5f};
	// 座標を移動させる(１フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
}

void Enemy::Fire() {

	// プレイヤーが存在しなければエラー
	assert(player_);
	// 弾丸の速度
	const float kBulletSpeed = -1.0f;
	// Vector3 velocity(0, 0, kBulletSpeed);
	//// 速度ベクトルを敵の向きに合わせて回転させる
	// velocity = TransforNormal(velocity, worldTransform_.matWorld_);

	// 自キャラのワールド座標を取得する
	Vector3 playerPos_ = player_->GetWorldPosition();
	// 敵キャラのワールド座標を取得する
	Vector3 enemyPos_ = GetWorldPosition();
	// 敵キャラ→自キャラの差分ベクトルを音求める
	Vector3 subtractV = Vector3Subtract(enemyPos_, playerPos_);
	// ベクトルの正規化
	Vector3 subtractVNotmalize = Vector3Normalize(subtractV);
	// ベクトルの長さを速さに合わせる
	Vector3 velocity = Vector3Multiply(kBulletSpeed, subtractVNotmalize);

	// 弾丸を生成・初期化する
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_,bulletTextureHandle_, worldTransform_.translation_, velocity);
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::OnCollision() {
	// 何もしない
	isDead_ = true;
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}