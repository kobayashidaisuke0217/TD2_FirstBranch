#include "Fireworks.h"

void Fireworks::Initialize(
	Model* model,const Vector3& position, const Vector3& scale, Vector3& rotation,
	const Vector3& velocity) {

	assert(model);
	
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = rotation;
	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
};

/// <summary>
/// 毎フレーム処理
/// </summary>
void Fireworks::Update() {

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();
};

/// <summary>
/// 描画
/// </summary>
void Fireworks::Draw(const ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection);
};