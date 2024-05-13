#include "MyMath.h"

/*-----------------------------------------------------------------------*/
//
//								4x4
//
/*-----------------------------------------------------------------------*/

// 1. 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = {(m1.m[i][0] * m2.m[0][j]) + (m1.m[i][1] * m2.m[1][j]) + (m1.m[i][2] * m2.m[2][j]) + (m1.m[i][3] * m2.m[3][j])};
		}
	}

	return result;
}

// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	//|A|を求める
	float A = {
	    1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

	         - (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

	         - (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

	         + (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

	         + (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])

	         - (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

	         - (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])

	         + (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))};

	// 00_02のP11　１/｜A｜の後ろを書く
	Matrix4x4 m1 = {0};
	m1.m[0][0] =
	    ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2]) - (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) -
	     (m.m[1][1] * m.m[2][3] * m.m[3][2]));
	m1.m[0][1] =
	    (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2]) + (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) +
	     (m.m[0][1] * m.m[2][3] * m.m[3][2]));
	m1.m[0][2] =
	    ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2]) - (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) -
	     (m.m[0][1] * m.m[1][3] * m.m[3][2]));

	m1.m[0][3] =
	    (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2]) + (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) +
	     (m.m[0][1] * m.m[1][3] * m.m[2][2]));

	m1.m[1][0] =
	    (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2]) + (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) +
	     (m.m[1][0] * m.m[2][3] * m.m[3][2]));

	m1.m[1][1] =
	    ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2]) - (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) -
	     (m.m[0][0] * m.m[2][3] * m.m[3][2]));

	m1.m[1][2] =
	    (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2]) + (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) +
	     (m.m[0][0] * m.m[1][3] * m.m[3][2]));

	m1.m[1][3] =
	    ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2]) - (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) -
	     (m.m[0][0] * m.m[1][3] * m.m[2][2]));

	m1.m[2][0] =
	    ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1]) - (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) -
	     (m.m[1][0] * m.m[2][3] * m.m[3][1]));

	m1.m[2][1] =
	    (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) +
	     (m.m[0][0] * m.m[2][3] * m.m[3][1]));

	m1.m[2][2] =
	    ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1]) - (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) -
	     (m.m[0][0] * m.m[1][3] * m.m[3][1]));

	m1.m[2][3] =
	    (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) +
	     (m.m[0][0] * m.m[1][3] * m.m[2][1]));

	m1.m[3][0] =
	    (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1]) + (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) +
	     (m.m[1][0] * m.m[2][2] * m.m[3][1]));

	m1.m[3][1] =
	    ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) -
	     (m.m[0][0] * m.m[2][2] * m.m[3][1]));

	m1.m[3][2] =
	    (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1]) + (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) +
	     (m.m[0][0] * m.m[1][2] * m.m[3][1]));

	m1.m[3][3] =
	    ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) -
	     (m.m[0][0] * m.m[1][2] * m.m[2][1]));

	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = A * m1.m[i][j];
		}
	}

	return result;
}

// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = {m.m[j][i]};
		}
	}

	return result;
}

// 6. 単位行列の生成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 0を入れる
			result.m[i][j] = 0;
			// iとjの値が同じ時に1を入れる
			if (i == j) {
				result.m[i][j] = 1;
			}
		}
	}
	return result;
};
// 1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 TranslateMatrix = {0};

	TranslateMatrix.m[0][0] = 1;
	TranslateMatrix.m[0][1] = 0;
	TranslateMatrix.m[0][2] = 0;
	TranslateMatrix.m[0][3] = 0;

	TranslateMatrix.m[1][0] = 0;
	TranslateMatrix.m[1][1] = 1;
	TranslateMatrix.m[1][2] = 0;
	TranslateMatrix.m[1][3] = 0;

	TranslateMatrix.m[2][0] = 0;
	TranslateMatrix.m[2][1] = 0;
	TranslateMatrix.m[2][2] = 1;
	TranslateMatrix.m[2][3] = 0;

	TranslateMatrix.m[3][0] = translate.x;
	TranslateMatrix.m[3][1] = translate.y;
	TranslateMatrix.m[3][2] = translate.z;
	TranslateMatrix.m[3][3] = 1;

	return TranslateMatrix;
};

// 2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 ScaleMatrix = {0};

	ScaleMatrix.m[0][0] = scale.x;
	ScaleMatrix.m[0][1] = 0;
	ScaleMatrix.m[0][2] = 0;
	ScaleMatrix.m[0][3] = 0;

	ScaleMatrix.m[1][0] = 0;
	ScaleMatrix.m[1][1] = scale.y;
	ScaleMatrix.m[1][2] = 0;
	ScaleMatrix.m[1][3] = 0;

	ScaleMatrix.m[2][0] = 0;
	ScaleMatrix.m[2][1] = 0;
	ScaleMatrix.m[2][2] = scale.z;
	ScaleMatrix.m[2][3] = 0;

	ScaleMatrix.m[3][0] = 0;
	ScaleMatrix.m[3][1] = 0;
	ScaleMatrix.m[3][2] = 0;
	ScaleMatrix.m[3][3] = 1;

	return ScaleMatrix;
};

// 3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = {0}; // w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f); // bベクトルに対して基本的な操作を行う秒列ではｗ＝０にならない
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

// 1 X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 RotateMatrix = {0};

	RotateMatrix.m[0][0] = 1;
	RotateMatrix.m[0][1] = 0;
	RotateMatrix.m[0][2] = 0;
	RotateMatrix.m[0][3] = 0;

	RotateMatrix.m[1][0] = 0;
	RotateMatrix.m[1][1] = std::cosf(radian);
	RotateMatrix.m[1][2] = std::sinf(radian);
	RotateMatrix.m[1][3] = 0;

	RotateMatrix.m[2][0] = 0;
	RotateMatrix.m[2][1] = -(std::sinf(radian));
	RotateMatrix.m[2][2] = std::cosf(radian);
	RotateMatrix.m[2][3] = 0;

	RotateMatrix.m[3][0] = 0;
	RotateMatrix.m[3][1] = 0;
	RotateMatrix.m[3][2] = 0;
	RotateMatrix.m[3][3] = 1;

	return RotateMatrix;
};

// 2 Y軸回転行列

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 RotateMatrix = {0};

	RotateMatrix.m[0][0] = std::cosf(radian);
	RotateMatrix.m[0][1] = 0;
	RotateMatrix.m[0][2] = -(std::sinf(radian));
	RotateMatrix.m[0][3] = 0;

	RotateMatrix.m[1][0] = 0;
	RotateMatrix.m[1][1] = 1;
	RotateMatrix.m[1][2] = 0;
	RotateMatrix.m[1][3] = 0;

	RotateMatrix.m[2][0] = std::sinf(radian);
	RotateMatrix.m[2][1] = 0;
	RotateMatrix.m[2][2] = std::cosf(radian);
	RotateMatrix.m[2][3] = 0;

	RotateMatrix.m[3][0] = 0;
	RotateMatrix.m[3][1] = 0;
	RotateMatrix.m[3][2] = 0;
	RotateMatrix.m[3][3] = 1;

	return RotateMatrix;
};

// 3 Z軸回転行列

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 RotateMatrix = {0};

	RotateMatrix.m[0][0] = std::cosf(radian);
	RotateMatrix.m[0][1] = std::sinf(radian);
	;
	RotateMatrix.m[0][2] = 0;
	RotateMatrix.m[0][3] = 0;

	RotateMatrix.m[1][0] = -(std::sinf(radian));
	RotateMatrix.m[1][1] = std::cosf(radian);
	;
	RotateMatrix.m[1][2] = 0;
	RotateMatrix.m[1][3] = 0;

	RotateMatrix.m[2][0] = 0;
	RotateMatrix.m[2][1] = 0;
	RotateMatrix.m[2][2] = 1;
	RotateMatrix.m[2][3] = 0;

	RotateMatrix.m[3][0] = 0;
	RotateMatrix.m[3][1] = 0;
	RotateMatrix.m[3][2] = 0;
	RotateMatrix.m[3][3] = 1;

	return RotateMatrix;
};

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	// 並行移動行列
	Matrix4x4 TranslateMatrix = MakeTranslateMatrix(translate);

	// 各軸の回転行列
	Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z);
	// 回転行列
	Matrix4x4 rotateXYZ = Multiply(rotateX, Multiply(rotateY, rotateZ));
	// 拡大縮小行列
	Matrix4x4 ScaleMatrix = MakeScaleMatrix(scale);

	// 全部合わせてアフィン行列を作る
	Matrix4x4 AffineMatrix = Multiply(Multiply(ScaleMatrix, rotateXYZ), TranslateMatrix);

	return AffineMatrix;
};
/*-----------------------------------------------------------------------*/
//
//								2次元ベクトル
//
/*-----------------------------------------------------------------------*/

float Vector2Length(const float& x, const float& y) {
	float result = sqrtf(x * x + y * y);
	return result;
}

float clamp(float& x, float max) {

	if (x < max) {
		return x;
	} else {
		return max;
	}
}
float clamp(float& x, float min, float max) {
	if (x < min) {
		return min;
	} else if (x > max) {
		return max;
	} else {
		return x;
	}
}

// 線形補間関数
float Lerp(const float& a, const float& b, float t) {

	float result = t * a + (1.0f - t) * b;

	return result;
}

/*-----------------------------------------------------------------------*/
//
//								3次元ベクトル
//
/*-----------------------------------------------------------------------*/

Vector3 Vector3Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return result;
}

Vector3 Vector3Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};

	return result;
}
Vector3 Vector3Multiply(float scalar, const Vector3& v) {
	Vector3 result = {v.x * scalar, v.y * scalar, v.z * scalar};

	return result;
}
float Vector3Dot(const Vector3& v1, const Vector3& v2) {

	float result = {(v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z)};
	return result;
}
float Vector3Length(const Vector3& v) {
	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}
Vector3 Vector3Normalize(const Vector3& v) {
	Vector3 result = {0, 0, 0};
	float length = Vector3Length(v);

	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}

	return result;
}
Vector3 Vector3Lerp(const Vector3& a, const Vector3& b, float t) {
	// tが0から1の間に収まるように制限する
	t = clamp(t, 0.0f, 1.0f);
	// ベクトルの線形補間を計算する
	Vector3 result;
	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;
	return result;
}

// ベクトル変換
// 平行移動を無視してスケーリングと回転のみを適用する
Vector3 TransforNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0], v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1], v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}

// 球面線形補間(Slerp)
// 正規化も行う
Vector3 MySlerp(const Vector3& v1, const Vector3& v2, float t) {

	Vector3 result;
	Vector3 v1Normalize = Vector3Normalize(v1);
	Vector3 v2Normalize = Vector3Normalize(v2);
	// 内積を求める
	float dot = Vector3Dot(v1Normalize, v2Normalize);
	// 誤差により1.0fを超えるのを防ぐ
	dot = clamp(dot, 0.0f,1.0f);
	// アークコサインでθの角度を求める
	float theta = std::acos(dot);
	// θの角度からsinθを求める
	float sinTheta = std::sin(theta);
	// サイン（θ(1-t)）を求める
	float sinThetaFrom = std::sin((1 - t) * theta);
	// サイン（θt）を求める
	float sinThetaTo = std::sin(t * theta);
	// 球面線形補間した単位ベクトル
	Vector3 SlerpVector;
	// ゼロ除算を防ぐ
	if (sinTheta < 1.0e-5) {
		SlerpVector = v1Normalize;
	} else {
		Vector3 a = Vector3Multiply(sinThetaFrom / sinTheta, v1Normalize);
		Vector3 b = Vector3Multiply(sinThetaTo / sinTheta, v2Normalize);
		SlerpVector = Vector3Add(a, b);
	}

	// 真逆の場合の滑らかな遷移
	if (dot < 0.0f) {
		// 一時的なベクトルを定義、v1とv2の中間点に位置
		Vector3 middle = Vector3Normalize(Vector3Add(v1, v2));
		// 滑らかな遷移をするために、中間点に対する補間をすｒ
		SlerpVector = Vector3Normalize(Vector3Lerp(SlerpVector, middle, 1.0f - t));
	}

	// ベクトルの長さはv1v2の長さを線形補間
	float lengthv1 = Vector3Length(v1);
	float lengthv2 = Vector3Length(v2);
	// 補間ベクトルの長さを求める
	float length = Lerp(lengthv1, lengthv2, t);
	// 長さを反映
	result = Vector3Multiply(length, SlerpVector);
	return result;

	///*											*///
	///*	v1とv2が真逆の向きの時v1を返すことになる		*///
	///*											*///

	// 解決方法
}

Vector3& operator+=(Vector3& v1, Vector3& v2) {
	v1 = Vector3Add(v1, v2);
	return v1;
};

Vector3& operator-=(Vector3& v1, Vector3& v2) {
	v1 = Vector3Subtract(v1, v2);
	return v1;
};