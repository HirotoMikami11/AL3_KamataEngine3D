#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <MyMath.h>
#include <ImGuiManager.h>
/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;


public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">ワールド座標</param>
	/// <param name="rotate">回転角</param>
	void Initialize(const Vector3&position,const Vector3 &rotate);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// デバッグ時のみ表示してみる
	/// </summary>
	void DebugDraw();



	/// <summary>
	/// ビュープロジェクション行列を取得する
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	const ViewProjection& GetViewProjection() { return viewProjection_; };
	/// <summary>
	/// ワールドトランスフォーム行列を取得する
	/// </summary>
	/// <returns></returns>
	const WorldTransform& GetWorldTrasnform() { return worldTransform_; };

	const float& GetPositionZ() { return worldTransform_.translation_.z; };

};
