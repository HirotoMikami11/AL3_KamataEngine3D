#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include "Input.h"
#include <MyMath.h>
#include <ImGuiManager.h>


/// <summary>
/// 自キャラ
/// </summary>

class Player {

	private:
		//キーボード入力
	    Input* input_ = nullptr;

		//ワールド変換データ
	    WorldTransform worldTransform_;
		//モデル
	    Model* model_ = nullptr;
		//テクスチャハンドル
	    uint32_t textureHandle_ = 0u;

	public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void initialize(Model* model,uint32_t textureHandle);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	void Draw(ViewProjection& viewProjection);
};