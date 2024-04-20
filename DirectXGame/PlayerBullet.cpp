#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	/// 1.nullptrチェック
	assert(model);

	/// 2.データをメンバ変数に移し替える
	// テクスチャハンドル
	textureHandle_ = TextureManager::Load("white1x1.png");
	// 3Dモデルデータ
	model_ = model;

	/// 3.ワールド変換の初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセットする
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() { 
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

