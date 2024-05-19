#include "RailCamera.h"

/// <summary>
/// 初期化
/// </summary>
void RailCamera::Initialize(const Vector3& position, const Vector3& rotate) {
	worldTransform_.Initialize();
	// ワールドトランスフォームの初期化設定
	// カメラは描画しないので初期化関数呼び出しはいらない
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotate;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {

	// 移動ベクトル
	Vector3 move = {0, 0, 0};
	// 回転ベクトル
	Vector3 rotate = {0, (1.0f/600.0f)*float(M_PI), 0};

	worldTransform_.translation_ += move;

	worldTransform_.rotation_ += rotate;




	worldTransform_.UpdateMatrix();
	
	//カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	

	///
	///ImGui
	/// 
	
	//カメラ座標を画面表示する処理
	ImGui::Begin("RailCamera");
	ImGui::SliderFloat3("RailCamera_translation", &worldTransform_.translation_.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("RailCamera_rotation", &worldTransform_.rotation_.x, 0.0f, 2.0f*float(M_PI));
	ImGui::End();

}

/// <summary>
/// デバッグ時のみ表示してみる
/// </summary>
void RailCamera::DebugDraw() {
#if _DEBUG

	/// デバッグの時だけ表示してみる

#endif // _DEBUG
}
