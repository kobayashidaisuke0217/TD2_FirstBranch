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
enum Score {
	Level1,
	Level2,
	Level3,
};
class Stage{
public:

	void Initialize(const std::vector<Model*>& models, int stagenum);

	void Update();
	void Draw(const ViewProjection& view);

	void Stage1Initialize();
	void Stage2Initialize();
	void Stage3Initialize();
	void Stage4Initialize();
	void Stage5Initialize();

	int LevelCheck(int count);

	int GetMap(int i, int j);

	// ワールド座標を取得 地面
	Vector3 GetWorldPositionNormal(int i);
	// ワールド座標を取得 壁
	Vector3 GetWorldPositionUp(int i);

	//bool GetBlockUp() { return blockUp; }
	bool SetSwitch(const bool up);
	bool GetShake() { return shake_; }
	void SetGoalModel(Model* model);
	void SetCountOver(bool flag) { countOver_ = flag; }
private:
	WorldTransform worldTransformNormal_[49] = {};
	WorldTransform worldTransformUp_[49] = {};
	WorldTransform worldTransformDown_[49] = {};
	WorldTransform worldTransformHeart_;
	WorldTransform worldTransformDiamond_;
	WorldTransform worldTransformGoal_;
	Model* modelNormal_;
	Model* modelFloorMove_;
	Model* modelHeart_;
	Model* modelDiamond_;
	Model* modelGoal_;
	int map_[7][7];
	int index = 0;
	
	 int Clearlevel2_;
	 int Clearlevel3_;
	Input* input_ = nullptr;
	bool blockUp = false;
	float Up = 0;
	float Down = -2.0f;
	bool shake_ = false;
	bool countOver_;
	float move[53];
	int shakeCount_;
};