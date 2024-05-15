#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "cassert"
#include <ImGuiManager.h>
#include <MyMath.h>
#include <list>

/// <summary>
/// 自キャラ
/// </summary>

class Player {
private:
	/// <summary>
	/// 弾丸を発射
	/// </summary>
	void Attack();

	// キーボード入力
	Input* input_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	/// 弾丸
	std::list<PlayerBullet*> bullets_;

	//半径
	float radius_;
	
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle,const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();
	
	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	///**----------------------------------------------------------------------------------------------*//
	///
	///		getter,setter
	/// 
	///**----------------------------------------------------------------------------------------------*//
	
	
	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 弾丸リストを取得
	/// </summary>
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	float GetRadius() { return radius_; };


};