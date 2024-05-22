#pragma once
#include "cassert"
#include <Matrix4x4.h>
#include <Vector3.h>
#define _USE_MATH_DEFINES
#include <cmath> //C++

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

// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

// 6. 単位行列の生成
Matrix4x4 MakeIdentity4x4();
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
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	//
///	演算の死のオーバーロード
//

// 加算
Matrix4x4& operator+=(Matrix4x4 m1, Matrix4x4& m2);

// 減算
Matrix4x4& operator-=(Matrix4x4 m1, Matrix4x4& m2);

// 積
Matrix4x4& operator*=(Matrix4x4 m1, Matrix4x4& m2);



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

// ベクトル変換
Vector3 TransforNormal(const Vector3& v, const Matrix4x4& m);

// 3次元ベクトルの距離
float Vector3Distance(const Vector3 v1, const Vector3 v2);

Vector3 multiply(const Matrix4x4& matrix, const Vector3& vec);
//
///	演算の死のオーバーロード
//

// 加算
Vector3& operator+=(Vector3& v1, Vector3& v2);

// 減算
Vector3& operator-=(Vector3& v1, Vector3& v2);
