#include "TitleScene.h"
#include "ImGuiManger.h"

TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	textureManager_ = Texturemanager::GetInstance();
	textureManager_->Initialize();
	 blueMoon_= BlueMoon::GetInstance();
	input = Input::GetInstance();
	Change = SceneChange::GetInstance();
	Change->Initialize();
	count = 0;
	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ =std:: make_unique<Player>();
	player_->Initialize(playerModel_.get());

}

void TitleScene::Update()
{

	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("count %d", count);
	ImGui::End();
	player_->TitleUpdate();
	if (input->PushKey(DIK_SPACE)) {
		Change->setmoveFlag();
	}
	Change->Update();
	if (Change->getchangeFlag() == true) {
		sceneNum = GAME_SCENE;
	}

	if (sceneNum < 0) {
		sceneNum = 0;

	}
	viewProjection_.translation_ = { 0.0f,9.3f,-2.1f };
	viewProjection_.rotation_ = { 1.2f, 0.0f, 0.0f };
	/*if (count >= 60) {
		sceneNum=GAME_SCENE;
	}*/
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

void TitleScene::Draw()
{
	
	Change->Draw();
	blueMoon_->ModelPreDraw();
	player_->Draw(viewProjection_);
	ImGui::Begin("TITLE");
	ImGui::Text("PushA:Start");
	ImGui::End();
}

void TitleScene::Finalize()
{
}
