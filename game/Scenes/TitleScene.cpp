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
	blueMoon_ = BlueMoon::GetInstance();
	
	input = Input::GetInstance();
	Change = SceneChange::GetInstance();
	Change->Initialize();
	count = 0;
	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(playerModel_.get(),{8.0f,0.0f,-2.0f});
	plane_ = std::make_unique<Plane>();
	plane_->Initialize();
	worldTransformPlane_.Initialize();
	worldTransformPlane_.translation_ = { 0.0f,-13.9f,10.8f };
	worldTransformPlane_.scale_ = { 53.9f,31.0f,1.0f };
	worldTransformPlane_.rotation_ = { 1.2f,0.0f,0.0f };
	Stagenum = 0;
	texturehandle = textureManager_->Load("Resource/haike.png");
	titleHandle_[0] = textureManager_->Load("Resource/taitoru.png");
	titleHandle_[1] = textureManager_->Load("Resource/supe.png");
	for (int i = 0; i < 2; i++) {
		sprite_[i] = std::make_unique<Sprite>();
		sprite_[i]->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 1280.0f,720.0f,0.0f,0.0f });
		spriteTransform_[i] = { { 1.0f,1.0f,1.0f},{ 0.0f,0.0f,0.0f} ,{ 1.0f,1.0f,1.0f} };
	}
	sceneNum = 0;
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	
}

void TitleScene::Update()
{

	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &Stagenum);
	ImGui::DragFloat3("plane", &worldTransformPlane_.rotation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransformPlane_.scale_.x, 0.1f);

	ImGui::DragFloat3("Z", &worldTransformPlane_.translation_.x, 0.1f);
	ImGui::Text("count %d", count);
	ImGui::End();
	player_->TitleUpdate();
	if (player_->GetWorldTransform().GetWorldPos().y >= 15.0f) {
		Change->setmoveFlag();
	}
	Change->Update();
	if (Change->getchangeFlag() == true) {
		sceneNum = STAGESELECT_SCENE;
		
	}

	if (sceneNum < 0) {
		sceneNum = 0;

	}
	viewProjection_.translation_ = { 0.0f,20.3f,-2.1f };
	viewProjection_.rotation_ = { 1.2f, 0.0f, 0.0f };
	worldTransformPlane_.UpdateMatrix();
	/*if (count >= 60) {
		sceneNum=GAME_SCENE;
	}*/
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

void TitleScene::Draw()
{
	
	blueMoon_->ModelPreDraw();
	player_->Draw(viewProjection_);
	plane_->Draw(worldTransformPlane_, viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, texturehandle);
	
blueMoon_->SpritePreDraw();
	blueMoon_->SetBlendMode(0);
	for (int i = 0; i < 2; i++) {
		sprite_[i]->Draw(spriteTransform_[i], SpriteuvTransform, { 1.0f,1.0f,1.0f,1.0f }, titleHandle_[i]);

	}
	Change->Draw();
	ImGui::Begin("TITLE");
	ImGui::Text("PushA:Start");
	ImGui::End();
}

void TitleScene::Finalize()
{
}