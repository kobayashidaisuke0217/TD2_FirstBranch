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
	void InitializeFloatingGimmick();
	void FloatingGimmick();
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
	Audio* audio_ = nullptr;
	//矢印のアニメーション
	Transform transformR_;
	Transform transformL_;
	Transform SpriteuvTransform;
	uint32_t arrowR;
	uint32_t arrowL;
	std::unique_ptr<Sprite>arrow_[2] = { nullptr };

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	// 浮遊移動サイクル
	float cycle = 0;
	// 浮遊の振幅
	float amplitude = 0.0f;
	float amplitudeArm = 0.4f;
	//円周率
	float Pi = 0.0f;
};

