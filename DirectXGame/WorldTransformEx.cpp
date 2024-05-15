#include <MyMath.h>
#include <WorldTransform.h>

void WorldTransform::UpdateMatrix() {
	// 行列更新
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	// 親があれば親のワールド行列をかける
	if (parent_) {
		Multiply(matWorld_ ,parent_->matWorld_);
	}

	// 行列を定数バッファに転送
	TransferMatrix();
}