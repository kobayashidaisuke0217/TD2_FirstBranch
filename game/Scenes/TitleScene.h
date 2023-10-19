#pragma once
#include "Iscene.h"
#include "Input.h"
#include "SceneChange.h"
#include "BlueMoon.h"
#include "player.h"
#include "model.h"
#include "Plane.h"
#include "WorldTransform.h"
class TitleScene:public Iscene
{
private:
	int count;
public:
	~TitleScene()override;
	 void Initialize() override;

	 void Update() override;

	 void Draw() override;
	 void Finalize()override;
private:
	ViewProjection viewProjection_;
	BlueMoon* blueMoon_;
	Texturemanager* textureManager_;
	Input* input=nullptr;
	SceneChange* Change;
	WorldTransform worldTransformPlane_;
	std::unique_ptr<Model> playerModel_ = nullptr;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Plane> plane_;

	
};

