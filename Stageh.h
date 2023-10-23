#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include"ICharactor.h"
#include <Input.h>
enum  St {
	Stages1,
	Stages2,
	Stages3,
	Stages4,
	Stages5,

};
class Stage{
public:

	void Initialize(const std::vector<Model*>& models);

	void Update();
	void Draw(const ViewProjection& view);

	void Stage1Initialize();
	void Stage2Initialize();
	void Stage3Initialize();
	void Stage4Initialize();
	void Stage5Initialize();

	

	int GetMap(int i, int j);

	// ワールド座標を取得 地面
	Vector3 GetWorldPositionNormal(int i);
	// ワールド座標を取得 壁
	Vector3 GetWorldPositionUp(int i);

	//bool GetBlockUp() { return blockUp; }
	bool SetSwitch(const bool up);
	bool GetShake() { return shake_; }

	void SetGoalModel(Model* model);

private:
	WorldTransform worldTransformNormal_[49] = {};
	WorldTransform worldTransformUp_[49] = {};
	WorldTransform worldTransformDown_[49] = {};
	WorldTransform worldTransformHeart_;
	WorldTransform worldTransformDiamond_;
	WorldTransform worldTransformGoal_;
	Model* modelNormal_;
	Model* modelHeart_;
	Model* modelDiamond_;
	Model* modelGoal_;
	int map_[7][7];
	int index = 0;
	
	Input* input_ = nullptr;
	bool blockUp;
	float Up = 0;
	float Down = -2.0f;
	bool shake_;
};