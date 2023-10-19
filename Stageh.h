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
	void Initialize(Model* models,int stagenum);
	void Update();
	void Draw(const ViewProjection& view);

	void Stage1Initialize();
	void Stage2Initialize();
	void Stage3Initialize();
	void Stage4Initialize();
	void Stage5Initialize();

	void stage1();
	void stage2();
	void stage3();

	int GetMap(int i, int j);

	// ワールド座標を取得 地面
	Vector3 GetWorldPositionNormal(int i);
	// ワールド座標を取得 壁
	Vector3 GetWorldPositionUp(int i);

	//bool GetBlockUp() { return blockUp; };
	bool SetSwitch(const bool up);
private:
	WorldTransform worldTransformNormal_[49] = {};
	WorldTransform worldTransformUp_[49] = {};
	WorldTransform worldTransformDown_[49] = {};
	Model* modelNormal_;

	int map_[7][7];
	int index = 0;
	//ブロックの番号
	enum {
		NORMALBLOCK, // 0
		REDBLOCK,    // 1
		BLUEBLOCK,   // 2
		GREENBLOCK,  // 3
		YELLOWBLOCK  // 4
	};

	Input* input_ = nullptr;
	bool blockUp;
	float Up = 0;
	float Down = -2.0f;
};