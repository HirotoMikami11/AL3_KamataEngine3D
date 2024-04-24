#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	/// 1.nullptrチェック
	assert(model);

	/// 2.データをメンバ変数に移し替える
	// テクスチャハンドル
	textureHandle_ = TextureManager::Load("white1x1.png");
	// 3Dモデルデータ
	model_ = model;

	/// 3.ワールド変換の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセットする
	worldTransform_.translation_ = position;
	//　引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	radius_ = 1;
}

void PlayerBullet::Update() { 
	//座標を移動させる(１フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
	//行列を更新
	worldTransform_.UpdateMatrix();

	//時間経過で消える
	if (--deathTimer_<=0) {
		isDead_ = true;
	}

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}