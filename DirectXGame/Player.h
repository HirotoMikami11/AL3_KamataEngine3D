#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "cassert"
#include <ImGuiManager.h>
#include <MyMath.h>
#include <list>
#include <Sprite.h>


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
	//スプライト
	//2Dレティクル用のスプライト
	Sprite* sprite2DReticle_ = nullptr;
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, 1280, 720, 0, 1);
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t bulletTextureHandle_ = 0u;

	/// 弾丸
	std::list<PlayerBullet*> bullets_;

	///3Dレティクル
	//3Dレティクル用のワールドトランスフォーム
	WorldTransform worldTransform3Dreticle_;

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
	void Initialize(Model* model, uint32_t playerTextureHandle, uint32_t bulletTextureHandle, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const ViewProjection& viewProjection);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

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

	/// <summary>
	/// 3Dレティクルの配置
	/// </summary>
	void Set3DreticlePosition();

	/// <summary>
	/// マウス3Dレティクルの配置
	/// </summary>
	void Set3DreticlePositionForMouse(const ViewProjection& viewProjection);

	/// <summary>
	/// 3Dレティクルのワールド座標を2Dレティクルのスクリーン座標に変換
	/// </summary>
	void convertWorldToScreenCoordsReticle(const ViewProjection& viewProjection);


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
	/// 3Dレティクルのワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition3Dreticle();


	/// <summary>
	/// 弾丸リストを取得
	/// </summary>
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	float GetRadius() { return radius_; };


};