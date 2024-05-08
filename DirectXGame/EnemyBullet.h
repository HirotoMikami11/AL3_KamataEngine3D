#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <TextureManager.h>
#include <MyMath.h>
#include <Collider.h>

class EnemyBullet :Collider{
private:

	Model* model_;
	WorldTransform worldTransform_;
	Vector3 velocity_;
	uint32_t textureHandle_;

	// 寿命
	static const int32_t kLifeTime = 60 * 5;

	int32_t deathTimer_ = kLifeTime;
	bool isDead_= false;
	float radius_;

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

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision() override;
	// getter
	bool IsDead() const { return isDead_; };
	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition() override;

	float GetRadius() { return radius_; };
};
