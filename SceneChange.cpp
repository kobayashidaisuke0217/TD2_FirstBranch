#include "SceneChange.h"
#include "Engine/base/ImGuiManger.h"
SceneChange* SceneChange::GetInstance()
{
	static SceneChange Instance;
	return &Instance;
}
void SceneChange::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();
	texturManager_ = Texturemanager::GetInstance();
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 1280.0f,720.0f,0.0f,0.0f });
	tex = texturManager_->Load("Resource/wi.png");
	saikorotransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	
}

void SceneChange::Update()
{
	Move();
	if (material.w < 0.0f) {
		moveFlag_ = false;
		arfaUp_ = true;
		material.w = 0.0f;
	}
	if (material.w >= 1.0f) {
		ChangeFlag_ = true;
		arfaUp_ = false;
	}
	ImGui::Begin("change");
	ImGui::DragFloat4("mat", &material.x);
	ImGui::End();
}

void SceneChange::SelectUpdate()
{
	if (selectmoveFlag_ == true) {
		if (selectarfaUp_ == true) {
			material.w += 0.02f;
		}
		else {
			material.w -= 0.02f;
		}
	}
	if (material.w < 0.0f) {
		selectmoveFlag_ = false;
		selectarfaUp_ = true;
		material.w = 0.0f;
	}
	if (material.w >= 1.0f) {
		
		selectarfaUp_ = false;
	}
	ImGui::Begin("change");
	ImGui::DragFloat4("translate", &material.x);
	ImGui::End();
}

void SceneChange::Draw()
{
	blueMoon_->SpritePreDraw();
	blueMoon_->SetBlendMode(0);
	sprite_->Draw(saikorotransform_, SpriteuvTransform, material, tex);

}

void SceneChange::Move()
{
	ChangeFlag_ = false;
	if (moveFlag_ == true) {
		if (arfaUp_ == true) {
			material.w += 0.01f;
		}
		else {
			material.w -= 0.01f;
		}
	}
}