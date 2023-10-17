#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include"ICharactor.h"

class Stage{
public:
	void Initialize(Model* models);
	void Update();
	void Draw(const ViewProjection& view);

	void Stage1Initialize();
	void Stage2Initialize();
	void Stage3Initialize();

	void stage1();
	void stage2();
	void stage3();

private:
	WorldTransform worldTransformNormal_[25] = {};
	Model* modelNormal_;

	int map[5][5];

	//ブロックの番号
	enum {
		NORMALBLOCK, // 0
		REDBLOCK,    // 1
		BLUEBLOCK,   // 2
		GREENBLOCK,  // 3
		YELLOWBLOCK  // 4
	};
};