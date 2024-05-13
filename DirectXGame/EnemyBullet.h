#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <MyMath.h>
#include <TextureManager.h>

// 自機クラスの前方宣言
// インクルードせずにプレイヤークラスのポインタを持つことができる
class Player;

class EnemyBullet {
private:
	Model* model_;
	WorldTransform worldTransform_;
	Vector3 velocity_;
	uint32_t textureHandle_;

	/// 自キャラ
	Player* player_ = nullptr;

	// 寿命
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

	// ホーミング
	//  横軸方向の長さを求める
	float velocityXZLen_;
	// 敵弾丸から自キャラへのベクトルを計算
	Vector3 toPlayer_;
	float t_;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標（敵の座標）</param>
	/// <param name="velcity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	// setter
	void SetPlayer(Player* player) { player_ = player; }

	// getter
	bool IsDead() const { return isDead_; };

	Vector3 GetWorldPosition();
};
