#pragma once
#include <cmath> //C++
#include <Vector3.h> 
#include <Matrix4x4.h> 
#include "cassert"


/*-----------------------------------------------------------------------*/
//
//								4x4
//
/*-----------------------------------------------------------------------*/


// 1. 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// 2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 1 X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// 2 Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// 3 Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

/*-----------------------------------------------------------------------*/
//
//								3次元ベクトル
//
/*-----------------------------------------------------------------------*/

// ３次元ベクトルの値を表示する
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);
// 加算
Vector3 Vector3Add(const Vector3& v1, const Vector3& v2);
// 減算
Vector3 Vector3Subtract(const Vector3& v1, const Vector3& v2);
// スカラー倍
Vector3 Vector3Multiply(float scalar, const Vector3& v);
// 内積
float Vector3Dot(const Vector3& v1, const Vector3& v2);
// 長さ
float Vector3Length(const Vector3& v);
// 正規化
Vector3 Vector3Normalize(const Vector3& v);
