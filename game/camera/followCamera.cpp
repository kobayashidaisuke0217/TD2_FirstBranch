#include "FollowCamera.h"
#include"MyMath.h"
#include "ImguiManger.h"
void FollowCamera::Initialize() {
	viewprojection_.Initialize();
	input_ = Input::GetInstance();
	viewprojection_.translation_ = { 0.0f,7.3f,-2.1f };
	viewprojection_.rotation_ = { 1.2f,0.0f,0.0f };
	ofset =  1.0f;
	
}

void FollowCamera::Update() {

	Move();
	Rotate();
	viewprojection_.UpdateViewMatrix();
	viewprojection_.TransferMatrix();
	ImGui::Begin("Scene");
	ImGui::DragFloat3("trans", &viewprojection_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &viewprojection_.rotation_.x, 0.1f);
	ImGui::End();
	
	
}

void FollowCamera::SetTarget(const WorldTransform* target) {

	target_ = target;
}

void FollowCamera::Move() {
	/*if (target_) {

		Vector3 offset = { 0.0f, 2.0f, -10.0f };

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		viewprojection_.translation_ = Add(target_->translation_, offset);
	}*/
	



	if (shake_) {
		random.x = static_cast<float>(std::rand() % randomRange + 1);
		random.y = static_cast<float>(std::rand() % randomRange + 1);
		random.z = static_cast<float>(std::rand() % randomRange + 1);
		//viewprojection_.translation_ = { -2.8f+random.x,32.0f-random.y,-20.0f+random.y };
		viewprojection_.translation_ = { 1.6f + random.x,13.8f - random.y,-14.7f + random.y };
	}
	else {
		
		viewprojection_.translation_ = { 1.6f,13.8f,-14.7f };
	}

	
	viewprojection_.rotation_ = { 1.0f,0.5f,0.0f };

	ImGui::Begin("camera");
	ImGui::DragFloat3("ofset", &ofset, 0.1f);
	ImGui::DragFloat3("rotate", &viewprojection_.rotation_.x, 0.1f);
	ImGui::End();
}

void FollowCamera::Rotate() {
	XINPUT_STATE joystate;

	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		const float kRotateSpeed = 0.02f;
		viewprojection_.rotation_.y += (float)joystate.Gamepad.sThumbRX / SHRT_MAX * kRotateSpeed;
	}
}
bool FollowCamera::SetShake(bool const shake) {
	shake_ = shake;

	return shake_;
}