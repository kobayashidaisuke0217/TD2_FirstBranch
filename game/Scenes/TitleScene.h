#pragma once
#include "Iscene.h"
#include "Input.h"
#include "SceneChange.h"
#include "BlueMoon.h"
#include "player.h"
#include "model.h"
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
	std::unique_ptr<Model> playerModel_ = nullptr;
	std::unique_ptr<Player> player_;
	
};

