#include "StageSelectScene.h"

void StageSelectScene::Initialize()
{
	viewProjection_.Initialize();
	
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
	viewProjection_.translation_ = { 2.0f,0.0f,-12.0f };
	viewProjection_.rotation_ = { 0.0f, 0.0f, 0.0f };
	cameraPos[0]= { 1.9f,0.0f,-12.0f };
	cameraPos[1] = { 23.8f,0.0f,-12.0f };
	cameraPos[2] = { 45.7f,0.0f,-12.0f };
	cameraPos[3] = { 67.6f,0.0f,-12.0f };
	cameraPos[4] = { 89.5f,0.0f,-12.0f };
	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(playerModel_.get());
	for (int i = 0; i < 5; i++) {
		plane_[i] = std::make_unique<Plane>();
		plane_[i]->Initialize();
		worldTransformPlane_[i].Initialize();
		worldTransformPlane_[i].scale_ = { 6.0f,6.0f,2.8f };
	}
	worldTransformPlane_[0].translation_ = { -6.0f,3.2f,2.8f };
	worldTransformPlane_[1].translation_ = { 15.9f,3.2f,2.8f };
	worldTransformPlane_[2].translation_ = { 37.8f,3.2f,2.8f };
	worldTransformPlane_[3].translation_ = { 59.7f,3.2f,2.8f };
	worldTransformPlane_[4].translation_ = { 81.6f,3.2f,2.8f };
	Stagenum = 0;
	index = 0;
	
}

void StageSelectScene::Update()
{
	player_->SelectUpdate();
	if (player_->GetWorldTransform().GetWorldPos().y >= 15.0f || input->PushKey(DIK_M)) {
		Change->setmoveFlag();
	}
	if (player_->GetStageSelectLeft() == 0 && player_->GetStageSelectRight() == 0) {
		Change->Update();
	}Change->SelectUpdate();
	if (Change->getchangeFlag() == true) {
		sceneNum = GAME_SCENE;

	}
	if (input->PushKey(DIK_1)) {
		index++;
	}
	if (index >= 5) {
		index = 0;
	}
	if (player_->GetStageSelectLeft() ==  4|| player_->GetStageSelectRight() == 4) {
		Change->setSelectMoveFlag();
		
		}
	if (player_->GetStageSelectRight() == 6 && preRightMoveCount_ == 5) {
		index++;
		
	}
	if (player_->GetStageSelectLeft() == 6 && preLeftMoveCount_ == 5) {
		index--;

	}
	if (index >= 5) {
		index = 0;
		//player_->SetTranslation({ -8.0f,0.0f,0.0f });
	}
	if (index < 0) {
		index = 4;
	}
	viewProjection_.translation_ = cameraPos[index];
	Stagenum = index;
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &Stagenum);
	ImGui::DragFloat3("rotate4", &worldTransformPlane_[3].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale4", &worldTransformPlane_[3].scale_.x, 0.1f);
	ImGui::DragFloat3("trans4", &worldTransformPlane_[3].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate5", &worldTransformPlane_[4].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale5", &worldTransformPlane_[4].scale_.x, 0.1f);
	ImGui::DragFloat3("trans5", &worldTransformPlane_[4].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransformPlane_[0].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransformPlane_[0].scale_.x, 0.1f);
	ImGui::DragFloat3("translate", &worldTransformPlane_[0].translation_.x, 0.1f);
	ImGui::End();
	ImGui::Begin("view");
	ImGui::DragFloat3("1", &cameraPos[0].x, 0.1f);
	ImGui::DragFloat3("2", &cameraPos[1].x, 0.1f);
	ImGui::DragFloat3("3", &cameraPos[2].x, 0.1f);
	ImGui::DragFloat3("4", &cameraPos[3].x, 0.1f);
	ImGui::DragFloat3("5", &cameraPos[4].x, 0.1f);
	ImGui::End();
	for (int i = 0; i < 5; i++) {
		worldTransformPlane_[i].UpdateMatrix();
	}
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
	preLeftMoveCount_ = player_->GetStageSelectLeft();
	preRightMoveCount_ = player_->GetStageSelectRight();
}

void StageSelectScene::Draw()
 {
	blueMoon_->ModelPreDraw();
	for (int i = 0; i < 5; i++) {
		plane_[i]->Draw(worldTransformPlane_[i], viewProjection_, {1.0f,1.0f,1.0f,1.0f}, stageTextueHandle[i]);
	}//plane_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformPlane_, stageTextueHandle[0],viewProjection_);
	player_->Draw(viewProjection_);
	
	Change->Draw();

}

void StageSelectScene::Finalize()
{
}
