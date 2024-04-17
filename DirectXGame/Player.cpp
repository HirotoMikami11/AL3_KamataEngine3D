#include <Player.h>

void Player::initialize(Model* model, uint32_t textureHandle) {
	/// 1.nullptrチェック
	assert(model);

	/// 2.データをメンバ変数に移し替える
	// テクスチャハンドル
	textureHandle_ = textureHandle;
	// 3Dモデルデータ
	model_ = model;

	/// 3.ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


}
void Player::Draw(ViewProjection& viewProjection){
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
};
