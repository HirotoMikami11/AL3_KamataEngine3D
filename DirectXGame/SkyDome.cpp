#include "SkyDome.h"
/// <summary>
/// 初期化
/// </summary>
void SkyDome::Initialize(Model* model) {
	///03_11_p24から再開
	//天球の初期化、更新、描画などを書く
		assert(model);

		/// 2.データをメンバ変数に移し替える
		// 3Dモデルデータ
		model_ = model;

		/// 3.ワールド変換の初期化
		worldTransform_.Initialize();

}
/// <summary>
/// 更新
/// </summary>
void SkyDome::Update() {

}
/// <summary>
/// 描画
/// </summary>
void SkyDome::Draw(ViewProjection& viewProjection) {
		// 3Dモデルを描画
		model_->Draw(worldTransform_, viewProjection);
}