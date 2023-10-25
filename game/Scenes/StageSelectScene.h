#pragma once
#include "Iscene.h"
#include "Iscene.h"
#include "Input.h"
#include "SceneChange.h"
#include "BlueMoon.h"
#include "player.h"
#include "model.h"
#include "Plane.h"
#include "WorldTransform.h"
#include "Sphere.h"
class StageSelectScene:public Iscene
{
public:
	void Initialize() override;

	void Update() override;

	void Draw() override;
	void Finalize()override;
private:
	ViewProjection viewProjection_;
	BlueMoon* blueMoon_;
	Texturemanager* textureManager_;
	Input* input = nullptr;
	SceneChange* Change;
	WorldTransform worldTransformPlane_[15];
	std::unique_ptr<Model> playerModel_  =nullptr;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Plane> plane_[15];
	uint32_t stageTextueHandle[10];
	uint32_t backGroundhandle[5];
	Vector3 cameraPos[5];
	int index;
	int preRightMoveCount_;
	int preLeftMoveCount_;
	Vector3 PlayerRespornPos[5];
	float LerpTimer;
};

