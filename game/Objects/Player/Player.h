#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "ViewProjection.h"
#include "Collider.h"
#include "CollisionConfig.h"
class Player:public Collider
{
public:
	void Initialize( Model* model);
	void Update();
	void Draw(const ViewProjection& view);
    WorldTransform GetWorldTransform()override { return worldTransform_; }
	const WorldTransform& GetWorldTransformBase() { return worldTransform_; }
	void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }
	void IsFall();
	StructSphere GetStructSphere() { return structSphere_; }
	bool isHit_;
	bool isGameover() { return gameOver; }
	void OnCollision() override;
	void OutCollision() ;
	void OnWallCollision();
	void OutWallCollision();
	void Setparent(const WorldTransform* parent);
	void IsCollision(const WorldTransform& worldtransform );
	void DeleteParent() { worldTransform_.parent_ = nullptr; worldTransform_.translation_ = worldTransform_.GetWorldPos(); }
	Vector3 GetWorldPosition();
	Vector3 GetMoveWorldPosition();
	void SetMap(const int map[5][5]);
	bool GetSwitch() { return switch_; };
private:
	Vector4 color;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;
	Model* model_;
	StructSphere structSphere_;
	bool gameOver = false;
	bool gameClear = false;
	WorldTransform worldTransform_;
	Matrix4x4 goal_;
	Matrix4x4 start_;
	Vector3 Translation_;
	bool MoveFlag = false;
	float moveSpeed;
	//!< 回転角度(90度の回転）
	float rad = 90 * 3.14f / 180;
	Quaternion quaternion_;
	float number;

	DualQuaternion Dual_;
	
	bool wallHit_ = false;
	float speed_ = 0;
	Matrix4x4 playerMove_;
	Matrix4x4 playerNowPos_;
	int map_[5][5];
	int moveMap_[5][5];
	Vector2 PlayerMap;
	bool switch_ = true;
	bool blockUp_;
private:
	void Move();
	float CheckNumber();
};

