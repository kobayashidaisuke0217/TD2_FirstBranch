#include "Player.h"
#include "ImguiManger.h"
#include "mymath.h"

void Player::Initialize(Model* model)
{
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	model_ = model;
	isHit_ = false;
	SetCollisionAttribute(CollisionConfig::kCollisionAttributePlayer);
	SetCollisionMask(~CollisionConfig::kCollisionAttributePlayer);
	color={ 1.0f,1.0f,1.0f,1.0f };
	moveSpeed = 0.0f;
	goal_= worldTransform_.matWorld_;
	start_ = worldTransform_.matWorld_;
	Translation_ = worldTransform_.translation_;
	quaternion_ = createQuaternion(0.0f, { 0.0f,1.0f,0.0f });
	quaternion_ = Normalize(quaternion_);
}

void Player::Update()
{
	if (worldTransform_.translation_.y < -10.0f) {
		gameOver = true;
	}
	
	
	model_->SetColor(color);
	structSphere_.center = worldTransform_.GetWorldPos();
	structSphere_.radius = 1.5f;
	Move();
	Vector3 WorldPos = worldTransform_.GetWorldPos();
	Vector4 Mat1 = { goal_.m[3][0],goal_.m[3][1],goal_.m[3][2],goal_.m[3][3] };
	Vector4 Mat2 = { start_.m[3][0],start_.m[3][1],start_.m[3][2],start_.m[3][3] };
	ImGui::Begin("player");
	ImGui::DragFloat4("translation", &WorldPos.x,0.01f);
	ImGui::DragFloat4("translation", &Mat1.x, 0.01f);
	ImGui::DragFloat4("translation", &Mat2.x, 0.01f);
	ImGui::End();
	//worldTransform_.UpdateMatrix();
	ImGui::Begin("number");
	ImGui::Text("number %f", number);
	ImGui::End();
	worldTransform_.TransferMatrix();
	
}

void Player::Draw(const ViewProjection& view)
{
	model_->Draw(worldTransform_, view);
}

void Player::IsFall()
{
	worldTransform_.translation_.y -= 0.1f;
}

void Player::OnCollision()
{
	gameOver = true;
}

void Player::Setparent(const WorldTransform* parent)
{
	
		worldTransform_.parent_ = parent;
	
	
}

void Player::IsCollision(const WorldTransform& worldtransform)
{
	if (!worldTransform_.parent_) {
		worldTransform_.translation_.y = worldtransform.translation_.y;
		worldTransform_.matWorld_.m[3][0] -= worldtransform.matWorld_.m[3][0];
		worldTransform_.matWorld_.m[3][1] -= worldtransform.matWorld_.m[3][1];
		worldTransform_.matWorld_.m[3][2] -= worldtransform.matWorld_.m[3][2];

		Setparent(&worldTransform_);
	}
}

void Player::Move()
{
	
	if (input_->PushKey(DIK_W)&&MoveFlag==false) {
		Vector3 move = { 0.0f,0.0f,1.0f };
	    
	Quaternion	newquaternion_ = createQuaternion(rad, { -1.0f,0.0f,0.0f });
	newquaternion_ = Normalize(newquaternion_);
	quaternion_ = Multiply(quaternion_, newquaternion_);
		Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);
		//Vector3 rotatedVector = rotateVectorWithQuaternion(quaternion_, Move);
		Translation_ =Add(move, Translation_);
	/*	Matrix4x4 a = MakeTranslateMatrix(Translation_);
		quaternionMat = Multiply(quaternionMat, a);
		Matrix4x4 goalmatrix = Multiply(worldTransform_.matWorld_, quaternionMat);*/
		Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
		goal_ = goalmatrix;
		start_ = worldTransform_.matWorld_;
		MoveFlag = true;
		
	}
	if (input_->PushKey(DIK_S) && MoveFlag == false) {
		Vector3 move = { 0.0f,0.0f,-1.0f };
		Quaternion	newquaternion_ = createQuaternion(rad, { 1.0f,0.0f,0.0f });
		newquaternion_ = Normalize(newquaternion_);
		quaternion_ = Multiply(quaternion_, newquaternion_);
		Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);
		
		Translation_ = Add(move, Translation_);
		
		Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
		goal_ = goalmatrix;
		start_ = worldTransform_.matWorld_;
		MoveFlag = true;
	}
	if (input_->PushKey(DIK_A) && MoveFlag == false) {
		
	
		Vector3 move = { -1.0f,0.0f,0.0f };
		Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,0.0f,-1.0f });
		newquaternion_ = Normalize(newquaternion_);
		quaternion_ = Multiply(quaternion_, newquaternion_);
		Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

		Translation_ = Add(move, Translation_);

		Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
		goal_ = goalmatrix;
		start_ = worldTransform_.matWorld_;
		MoveFlag = true;
	}
	if (input_->PushKey(DIK_D) && MoveFlag == false) {
		Vector3 move = { 1.0f,0.0f,0.0f };
		Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,0.0f,1.0f });
		newquaternion_ = Normalize(newquaternion_);
		quaternion_ = Multiply(quaternion_, newquaternion_);
		Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

		Translation_ = Add(move, Translation_);

		Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
		goal_ = goalmatrix;
		start_ = worldTransform_.matWorld_;
		MoveFlag = true;
	}
	

	
	if (MoveFlag == true) {
		if (moveSpeed <= 1.0f) {
			moveSpeed += 0.05f;
		}else
		 {
			moveSpeed = 1.0f;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				worldTransform_.matWorld_.m[i][j] = Lerp(moveSpeed, start_.m[i][j], goal_.m[i][j]);
			}
		}if (moveSpeed >= 1.0f) {
			MoveFlag = false;
			moveSpeed = 0.0f;
			//サイコロの目を確認(今は、わかりやすいよう上面の番号を表示している)
			number = CheckNumber();
		}
		
	}
}

float Player::CheckNumber() {
	float number = 0;
	Vector3 RightVector = GetRightVectorFromModelMatrix(worldTransform_.matWorld_);
	Vector3 UPVector = GetUpVectorFromModelMatrix(worldTransform_.matWorld_);
	Vector3 FrontVector = GetFrontVectorFromModelMatrix(worldTransform_.matWorld_);

	if (RightVector.y >= 0.9f) {

		if (UPVector.z >= 0.9f) {
			number = 1.0f;

		}
		else if (FrontVector.z <= -0.8f) {
			number = 4.0f;

		}
		else if (UPVector.z <= -0.8f) {
			number = 6.0f;

		}
		else {
			number = 3.0f;
		}

	}
	else if (RightVector.y <= -0.8f) {

		if (UPVector.z >= 0.9f) {
			number = 1.0f;

		}
		else if (FrontVector.z <= -0.8f) {
			number = 3.0f;

		}
		else if (UPVector.z <= -0.8f) {
			number = 6.0f;

		}
		else {
			number = 4.0f;
		}

	}
	else if (UPVector.y >= 0.9f) {
		number = 5.0f;

	}
	else if (UPVector.y <= -0.8f) {
		number = 2.0f;

	}
	else if (FrontVector.y >= 0.9f) {

		if (RightVector.z >= 0.9f) {
			number = 4.0f;

		}
		else if (RightVector.z <= -0.8f) {
			number = 3.0f;

		}
		else if (UPVector.z >= 0.9f) {
			number = 1.0f;

		}
		else {
			number = 6.0f;
		}
	}
	else if (FrontVector.y <= -0.8f) {

		if (RightVector.z <= -0.8f) {
			number = 4.0f;

		}
		else if (RightVector.z >= 0.9f) {
			number = 3.0f;

		}
		else if (UPVector.z <= 0.8f) {
			number = 6.0f;

		}
		else {
			number = 1.0f;
		}
	}

	return number;

	ImGui::Begin("vector");
	ImGui::Text("Right X %f,Y %f,Z %f", &RightVector.x, RightVector.y, RightVector.z);
	ImGui::Text("Up X %f,Y %f,Z %f", &UPVector.x, UPVector.y, UPVector.z);
	ImGui::Text("Front X %f,Y %f,Z %f", &FrontVector.x, FrontVector.y, FrontVector.z);
	ImGui::End();
}
