#pragma once
#include <cstdint>
#include <worldTransform.h>
#include <Model.h>


class Fireworks {
public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(
		Model* model,const Vector3& position, const Vector3& scale, Vector3& rotation,
		const Vector3& velocity);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewprojection);

	bool IsDead() const { return isDead_; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();


	// ギミック初期化
	void InitializeFloatingGimmick();

	// ギミックの更新
	void UpdateFloatingGimmick();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	
	// 速度
	Vector3 velocity_;

	// 寿命
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;


	
};