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
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;

public:
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	public:

};
