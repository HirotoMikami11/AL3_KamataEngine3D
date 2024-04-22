#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include <TextureManager.h>
#include "cassert"
#include <ImGuiManager.h>
#include <MyMath.h>
/// <summary>
/// 敵
/// </summary>
class Enemy {
private:
	/// <summary>
	/// フェーズ
	/// </summary>
	enum class Phase {
		Approach,	//接近する
		Leave		//離脱する
	};

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;

	//フェーズ
	Phase phase_ = Phase::Approach;

public:
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);
	/// <summary>
	/// Approachフェーズの処理
	/// </summary>
	/// <param name="Velocity">Approachフェーズの速度</param>
	void ApproachAction(const Vector3& velocity); 
	/// <summary>
	/// Leaveフェーズの処理
	/// </summary>
	/// <param name="Velocity">Leaveフェーズの速度</param>
	void LeaveAction(const Vector3& velocity); 
	public:

};
