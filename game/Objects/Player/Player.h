#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "ViewProjection.h"
#include "Collider.h"
#include "CollisionConfig.h"
#include "EfectManager.h"
class Player:public Collider
{
public:
	void Initialize( Model* model);
	void Update();
	void TitleUpdate();
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
	void SetMap(const int map[7][7]);
	bool GetSwitch() { return switch_; };
	bool GetHeart() { return heart_; };
	bool GetDiamond() { return diamond_; };
private:
	EfectManager* efectManager_;
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
	int sMap_[7][7];
	int map_[7][7];
	int moveMap_[7][7];
	Vector2 PlayerMap;
	bool switch_ = true;
	bool blockUp_;

	float goalNum_ = 0.0f;
	bool goalFlag1_ = false;
	bool goalFlag2_ = false;
	bool goalFlag3_ = false;
	int titleCount_;
	bool JumFlag_;


	Vector3 goalPos_;

	int stepsCount_ = 0;
	int count_ = 0;
	int num1_;
	int num2_;

	bool heart_ = false;
	bool diamond_ = false;

private:
	void Move();
	float CheckNumber();
};

