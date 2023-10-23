#include "StageSelectScene.h"

void StageSelectScene::Initialize()
{
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	textureManager_ = Texturemanager::GetInstance();
	textureManager_->Initialize();
	stageTextueHandle[0] = textureManager_->Load("Resource/Stage_1.png");
	stageTextueHandle[1] = textureManager_->Load("Resource/Stage_2.png");
	stageTextueHandle[2] = textureManager_->Load("Resource/Stage_3.png");
	stageTextueHandle[3] = textureManager_->Load("Resource/Stage_4.png");
	stageTextueHandle[4] = textureManager_->Load("Resource/Stage_5.png");
	
	blueMoon_ = BlueMoon::GetInstance();
	input = Input::GetInstance();
	Change = SceneChange::GetInstance();
	Change->Initialize();
	
	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(playerModel_.get());
	plane_ = std::make_unique<Plane>();
	plane_->Initialize();
	worldTransformPlane_.Initialize();
	Stagenum = 0;
}

void StageSelectScene::Update()
{
	player_->TitleUpdate();
	if (player_->GetWorldTransform().GetWorldPos().y >= 15.0f) {
		Change->setmoveFlag();
	}
	Change->Update();
	if (Change->getchangeFlag() == true) {
		sceneNum = GAME_SCENE;

	}

	if (sceneNum < 0) {
		sceneNum = 0;

	}
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &Stagenum);
	ImGui::DragFloat3("rotate", &worldTransformPlane_.rotation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransformPlane_.scale_.x, 0.1f);
	ImGui::DragFloat3("trans", &worldTransformPlane_.translation_.x, 0.1f);
	ImGui::End();
	viewProjection_.translation_ = { 0.0f,20.3f,-2.1f };
	viewProjection_.rotation_ = { 1.2f, 0.0f, 0.0f };
	worldTransformPlane_.UpdateMatrix();
	
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

void StageSelectScene::Draw()
 {
	blueMoon_->ModelPreDraw();
	plane_->Draw(worldTransformPlane_, viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, stageTextueHandle[0]);
	//plane_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformPlane_, stageTextueHandle[0],viewProjection_);
	player_->Draw(viewProjection_);
	
	Change->Draw();

}

void StageSelectScene::Finalize()
{
}
