#pragma once
#pragma region エンジン
#include "BlueMoon.h"
#include "Input.h"
#include "Texturemanager.h"
#include "Audio.h"
#include "GlobalVariables.h"
#include "ImGuiManger.h"
#include"DirectionalLight.h"

#pragma endregion
#pragma region シーン
#include <game/Scenes/Iscene.h>
#include<game/Scenes/gameScene.h>
#include <game/Scenes/TitleScene.h>
#include "sceneChange.h"
#pragma endregion
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
#pragma region default
	void Initialize();
	/*void Update();
	void Draw();
	void Finalize();*/
#pragma endregion 
	void Run();
	
private:
	BlueMoon* blueMoon_;
	WinApp* winApp_ = nullptr;
	Input* input ;
	Texturemanager* textureManager_;
	Audio* audio_;
	std::unique_ptr<Iscene> sceneArr_[2];
	GlovalVariables* glovalVariables_;
	ImGuiManger* imguiManager_;
	DirectionalLight* directionallight_;
	std::unique_ptr<SceneChange>sceneChange_;
	int sceneNum_;
	int preSceneNum_;

};

