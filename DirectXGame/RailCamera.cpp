#include "RailCamera.h"

/// <summary>
/// 初期化
/// </summary>
void RailCamera::Initialize(const Vector3& position, const Vector3& rotate) {
	
	//ワールドトランスフォームの初期化設定
	//カメラは描画しないので初期化関数呼び出しはいらない
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotate;
	
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {
	




}

/// <summary>
/// デバッグ時のみ表示してみる
/// </summary>
void RailCamera::DebugDraw() {
#if _DEBUG

	/// デバッグの時だけ表示してみる

#endif // _DEBUG
}