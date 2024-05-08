#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <ImGuiManager.h>
#include <MyMath.h>
#include <TextureManager.h>

#include <EnemyBullet.h>

// 自機クラスの前方宣言
// インクルードせずにプレイヤークラスのポインタを持つことができる
class Player;

/// <summary>
/// 敵
/// </summary>
class Enemy : Collider{
private:
	/// <summary>
	/// フェーズ
	/// </summary>
	enum class Phase {
		Approach, // 接近する
		Leave     // 離脱する
	};

	/// 自キャラ
	Player* player_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;
	// フェーズ
	Phase phase_ = Phase::Approach;

	float radius_;
	/*-----------------------------------------------------------------------*/
	//								弾丸関係の変数
	/*-----------------------------------------------------------------------*/

	std::list<EnemyBullet*> bullets_;
	// 発射までのインターバル
	static const int kfireInterval = 60;
	// 発射するタイマー
	int32_t fireTimer_ = kfireInterval;
	// メンバ関数ポインタのテーブル
	static void (Enemy::*spFuncTable[])();

	/// <summary>
	/// 弾を撃つ
	/// </summary>
	void Fire();

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">座標</param>
	/// <param name="velocity">速さ</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

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
	/// Approachフェーズの処理
	/// </summary>
	void ApproachAction();

	/// <summary>
	/// Leaveフェーズの処理
	/// </summary>
	void LeaveAction();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision() override;

	//setter
	void SetPlayer(Player* player) { player_ = player; }
	//gettrer
	Vector3 GetWorldPosition() override;

	float GetRadius() { return radius_; };
	/// <summary>
	/// 弾丸リストを取得
	/// </summary>
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }
};
