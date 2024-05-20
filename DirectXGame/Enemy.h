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
//GameSceneの前方宣言
class GameScene;

/// <summary>
/// 敵
/// </summary>
class Enemy {
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
	///　ゲームシーン
	GameScene* gameScene_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t bulletTextureHandle_ = 0u;
	// 速度
	Vector3 velocity_;
	// フェーズ
	Phase phase_ = Phase::Approach;

	float radius_;


	//ですフラグ
	bool isDead_=false;
	/*-----------------------------------------------------------------------*/
	//								弾丸関係の変数
	/*-----------------------------------------------------------------------*/

	//std::list<EnemyBullet*> bullets_;
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
	void Initialize(Model* model, uint32_t enemyTextureHandle, uint32_t bulletTextureHandle, const Vector3& position, const Vector3& velocity);

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
	void OnCollision();

	//setter
	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	// getter
	bool IsDead() const { return isDead_; };
	Vector3 GetWorldPosition();

	float GetRadius() { return radius_; };

};
