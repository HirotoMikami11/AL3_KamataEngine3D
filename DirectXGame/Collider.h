#pragma once
#include<MyMath.h>
/// <summary>
/// 衝突判定オブジェクト
/// </summary>
class Collider {
private:
	//衝突判定
	float radius_ = 1;




public:
	//半径を取得
	float GetRadius() { return radius_; };
	//半径を設定
	void SetRadius(float radius) { radius_ = radius; };
	//衝突時に呼ばれる関数
	virtual void OnCollision();
	//ワールド関数を取得
	virtual Vector3 GetWorldPosition();
};
