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
	stageTextueHandle[5] = textureManager_->Load("Resource/StageSelect_1.png");
	stageTextueHandle[6] = textureManager_->Load("Resource/StageSelect_2.png");
	stageTextueHandle[7] = textureManager_->Load("Resource/StageSelect_3.png");
	stageTextueHandle[8] = textureManager_->Load("Resource/StageSelect_4.png");
	stageTextueHandle[9] = textureManager_->Load("Resource/StageSelect_5.png");
	backGroundhandle[0] = textureManager_->Load("Resource/BG1.png");
	backGroundhandle[1] = textureManager_->Load("Resource/BG2.png");
	backGroundhandle[2] = textureManager_->Load("Resource/BG3.png");
	backGroundhandle[3] = textureManager_->Load("Resource/BG4.png");
	backGroundhandle[4] = textureManager_->Load("Resource/BG5.png");
	arrowR = textureManager_->Load("Resource/arrowR.png");
	arrowL = textureManager_->Load("Resource/arrowL.png");

	index = Stagenum;
	blueMoon_ = BlueMoon::GetInstance();
	input = Input::GetInstance();
	Change = SceneChange::GetInstance();
	Change->Initialize();
	PlayerRespornPos[0] = { 2.0f,-2.0f,-2.0f };
	PlayerRespornPos[1] = { 24.0f,-2.0f,-2.0f };
	PlayerRespornPos[2] = { 46.0f,-2.0f,-2.0f };
	PlayerRespornPos[3] = { 68.0f,-2.0f,-2.0f };
	PlayerRespornPos[4] = { 90.0f,-2.0f,-2.0f };
	viewProjection_.translation_ = { 2.0f,0.0f,-12.0f };
	viewProjection_.rotation_ = { 0.0f, 0.0f, 0.0f };
	cameraPos[0]= { 1.9f,0.0f,-12.0f };
	cameraPos[1] = { 23.8f,0.0f,-12.0f };
	cameraPos[2] = { 45.7f,0.0f,-12.0f };
	cameraPos[3] = { 67.6f,0.0f,-12.0f };
	cameraPos[4] = { 89.5f,0.0f,-12.0f };
	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(playerModel_.get(),PlayerRespornPos[Stagenum]);
	for (int i = 0; i < 15; i++) {
		plane_[i] = std::make_unique<Plane>();
		plane_[i]->Initialize();
		worldTransformPlane_[i].Initialize();
		worldTransformPlane_[i].scale_ = { 0.0f,0.0f,0.0f };
	}
	worldTransformPlane_[10].scale_ = { 21.9f,12.3f,0.0f };
	worldTransformPlane_[11].scale_ = { 21.9f,12.3f,0.0f };
	worldTransformPlane_[12].scale_ = { 21.9f,12.3f,0.0f };
	worldTransformPlane_[13].scale_ = { 21.9f,12.3f,0.0f };
	worldTransformPlane_[14].scale_ = { 21.9f,12.3f,0.0f };
	worldTransformPlane_[0].translation_ = { -3.6f,2.4f,2.2f };
	worldTransformPlane_[1].translation_ = { 18.3f,2.4f,2.2f };
	worldTransformPlane_[2].translation_ = { 40.2f,2.4f,2.2f };
	worldTransformPlane_[3].translation_ = { 62.1f,2.4f,2.2f };
	worldTransformPlane_[4].translation_ = { 84.0f,2.4f,2.2f };
	worldTransformPlane_[5].translation_ = { 6.8f,3.2f,2.2f };
	worldTransformPlane_[6].translation_ = { 28.7f,3.2f,2.2f };
	worldTransformPlane_[7].translation_ = { 50.6f,3.2f,2.2f };
	worldTransformPlane_[8].translation_ = { 72.5f,3.2f,2.2f };
	worldTransformPlane_[9].translation_ = { 94.4f,3.2f,2.2f };
	worldTransformPlane_[10].translation_ = { 1.9f,0.0f,2.8f };
	worldTransformPlane_[11].translation_ = { 23.8f,0.0f,2.8f };
	worldTransformPlane_[12].translation_ = { 45.7f,0.0f,2.8f };
	worldTransformPlane_[13].translation_ = { 67.6f,0.0f,2.8f };
	worldTransformPlane_[14].translation_ = { 89.5f,0.0f,2.8f };
	player_->SetStageSelectNum(index);
	LerpTimer = 0.0f;
	
	InitializeFloatingGimmick();
	for (int i = 0; i < 2; i++) {
		arrow_[i] = std::make_unique<Sprite>();
		arrow_[i]->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 150.0f,150.0f,0.0f,0.0f });
	}

	transformR_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{890.0f,474.0f,1.0f} };
	transformL_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{280.0f,474.0f,1.0f} };
	
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
}

void StageSelectScene::Update()
{
	player_->SelectUpdate();
	
	if ( input->PushKey(DIK_SPACE)) {
		Change->setmoveFlag();
	}
	if (player_->GetStageSelectLeft() == 0 && player_->GetStageSelectRight() == 0) {
		Change->Update();
	}
	Change->SelectUpdate();
	if (Change->getchangeFlag() == true) {
		sceneNum = GAME_SCENE;

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
	
	}
	if (index < 0) {
		index = 4;
	}
	if (player_->GetStageSelectLeft() == 0 && player_->GetStageSelectRight() == 0) {

		if (LerpTimer < 1.0f) {
			LerpTimer += 0.05f;
		}
		else
		{
			LerpTimer = 1.0f;
		}
		worldTransformPlane_[index].scale_ = Lerp(LerpTimer, { 0.0f,0.0f,0.0f }, { 6.0f,6.0f,2.8f });
		worldTransformPlane_[index + 5].scale_ = Lerp(LerpTimer, { 0.0f,0.0f,0.0f }, { 8.0f,4.5f,2.8f });
	}
	else {
		LerpTimer = 0.0f;
	}
	for (int i = 0; i < 5; i++) {
		if (i != index ) {
			worldTransformPlane_[i].scale_ = { 0.0f,0.0f,0.0f };
			worldTransformPlane_[i+5].scale_ = { 0.0f,0.0f,0.0f };
		}
	}
	FloatingGimmick();
	viewProjection_.translation_ = cameraPos[index];
	Stagenum = index;
	Vector3 pos = player_->GetWorldPosition();
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &Stagenum);
	ImGui::DragFloat3("ArrowR", &transformR_.translate.x, 2.0f);
	ImGui::DragFloat3("ArrowL", &transformL_.translate.x, 2.0f);
	ImGui::DragFloat3("scale1", &worldTransformPlane_[0].scale_.x, 0.1f);
	ImGui::DragFloat3("trans1", &worldTransformPlane_[0].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate1", &worldTransformPlane_[0].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale5", &worldTransformPlane_[5].scale_.x, 0.1f);
	ImGui::DragFloat3("trans5", &worldTransformPlane_[5].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate5", &worldTransformPlane_[5].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale2", &worldTransformPlane_[1].scale_.x, 0.1f);
	ImGui::DragFloat3("trans2", &worldTransformPlane_[1].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate2", &worldTransformPlane_[1].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale6", &worldTransformPlane_[6].scale_.x, 0.1f);
	ImGui::DragFloat3("trans6", &worldTransformPlane_[6].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate6", &worldTransformPlane_[6].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale3", &worldTransformPlane_[2].scale_.x, 0.1f);
	ImGui::DragFloat3("translate3", &worldTransformPlane_[2].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate3", &worldTransformPlane_[2].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale7", &worldTransformPlane_[7].scale_.x, 0.1f);
	ImGui::DragFloat3("trans7", &worldTransformPlane_[7].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate7", &worldTransformPlane_[7].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale4", &worldTransformPlane_[3].scale_.x, 0.1f);
	ImGui::DragFloat3("trans4", &worldTransformPlane_[3].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate4", &worldTransformPlane_[3].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale8", &worldTransformPlane_[8].scale_.x, 0.1f);
	ImGui::DragFloat3("trans8", &worldTransformPlane_[8].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate8", &worldTransformPlane_[8].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale9", &worldTransformPlane_[4].scale_.x, 0.1f);
	ImGui::DragFloat3("translate9", &worldTransformPlane_[4].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate9", &worldTransformPlane_[4].rotation_.x, 0.1f);
	ImGui::DragFloat3("scale10", &worldTransformPlane_[9].scale_.x, 0.1f);
	ImGui::DragFloat3("trans10", &worldTransformPlane_[9].translation_.x, 0.1f);
	ImGui::DragFloat3("rotate10", &worldTransformPlane_[9].rotation_.x, 0.1f);
	ImGui::End();
	ImGui::Begin("view");
	ImGui::DragFloat3("1", &cameraPos[0].x, 0.1f);
	ImGui::DragFloat3("2", &cameraPos[1].x, 0.1f);
	ImGui::DragFloat3("3", &cameraPos[2].x, 0.1f);
	ImGui::DragFloat3("4", &cameraPos[3].x, 0.1f);
	ImGui::DragFloat3("5", &cameraPos[4].x, 0.1f);
	ImGui::End();
	for (int i = 0; i < 15; i++) {
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
	for (int i = 0; i < 10; i++) {
		plane_[i]->Draw(worldTransformPlane_[i], viewProjection_, {1.0f,1.0f,1.0f,1.0f}, stageTextueHandle[i]);
	}
	plane_[10]->Draw(worldTransformPlane_[10], viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, backGroundhandle[0]);
	plane_[11]->Draw(worldTransformPlane_[11], viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, backGroundhandle[1]);
	plane_[12]->Draw(worldTransformPlane_[12], viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, backGroundhandle[2]);
	plane_[13]->Draw(worldTransformPlane_[13], viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, backGroundhandle[3]);
	plane_[14]->Draw(worldTransformPlane_[14], viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, backGroundhandle[4]);
	
	//plane_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformPlane_, stageTextueHandle[0],viewProjection_);
	player_->Draw(viewProjection_);
	blueMoon_->SpritePreDraw();
	blueMoon_->SetBlendMode(0);
	if (player_->GetStageSelectLeft() ==0 && player_->GetStageSelectRight() == 0) {
		arrow_[0]->Draw(transformR_, SpriteuvTransform, { 1.0f,1.0f,1.0f,1.0f }, arrowR);
		arrow_[1]->Draw(transformL_, SpriteuvTransform, { 1.0f,1.0f,1.0f,1.0f }, arrowL);
	}
	
	Change->Draw();
	
}

void StageSelectScene::Finalize()
{
}

void StageSelectScene::InitializeFloatingGimmick() {
	floatingParameter_ = 0.0f;

	// 浮遊移動サイクル
	cycle = 60;
	Pi = 3.1415f;
	// 浮遊の振幅
	amplitude = 2.0f;
	amplitudeArm = 0.4f;
}

void StageSelectScene::FloatingGimmick() {
	// 1フレームでのパラメータ加算値
	const float steppe = 2.0f * Pi / cycle;

	// パラメータを1分加算
	floatingParameter_ += steppe;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * Pi);


	transformR_.translate.x =  transformR_.translate.x + std::sin(floatingParameter_) * amplitude;
	transformL_.translate.x = transformL_.translate.x - std::sin(floatingParameter_) * amplitude;
	
}
