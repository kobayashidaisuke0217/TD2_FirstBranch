#include "Player.h"
#include "ImguiManger.h"
#include "mymath.h"

void Player::Initialize(Model* model)
{
	
	worldTransform_.Initialize();
	worldTransform_.matWorld_.m[3][0] = 2.0f;
	worldTransform_.matWorld_.m[3][2] = -2.0f;
	input_ = Input::GetInstance();
	
	efectManager_ = EfectManager::GetInstance();
	model_ = model;
	isHit_ = true;
	SetCollisionAttribute(CollisionConfig::kCollisionAttributePlayer);
	SetCollisionMask(~CollisionConfig::kCollisionAttributePlayer);
	color = { 1.0f,1.0f,1.0f,1.0f };
	moveSpeed = 0.0f;
	goal_ = worldTransform_.matWorld_;
	start_ = worldTransform_.matWorld_;
	worldTransform_.translation_ = worldTransform_.GetWorldPos();
	Translation_ = worldTransform_.translation_;
	quaternion_ = createQuaternion(0.0f, { 0.0f,1.0f,0.0f });
	quaternion_ = Normalize(quaternion_);
	titleCount_ = 0;
	JumFlag_ = false;

	goalNum_ = 0.0f;
	goalFlag1_ = false;
	goalFlag2_ = false;
	goalFlag3_ = false;

	stageSelectMoveLeftCoumt_ = 0;
	stageSelectMoveRightCoumt_ = 0;
	stageSelectCount_ = 0;


	stepsCount_ = 0;

	audio_ = Audio::GetInstance();
	audio_->Initialize();
	//サウンドデータ
	audio_->soundDatas[0] = audio_->SoundLoadWave("resource/Audio/playerSE.wav");
	audio_->soundDatas[1] = audio_->SoundLoadWave("resource/Audio/PressurePlate.wav");
	audio_->soundDatas[2] = audio_->SoundLoadWave("resource/Audio/PressureClearPlate.wav");
	
}

void Player::Update()
{
	if (worldTransform_.matWorld_.m[3][1] < -100.0f) {
		gameOver = true;
	}

	//落ちる処理
	if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y)] == 0) {
		IsFall();
	}

	model_->SetColor(color);
	structSphere_.center = worldTransform_.GetWorldPos();
	structSphere_.radius = 1.5f;
	if (worldTransform_.matWorld_.m[3][1] >= -1.0f) {
		Move();
	}

	if (!switch_) {
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {

				if (map_[i][j] == 2) {
					map_[i][j] = 1;

				}
				if (sMap_[i][j] == 3) {
					map_[i][j] = 3;

				}
			}
		}

	}
	else {
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {

				if (sMap_[i][j] == 2) {
					map_[i][j] = 2;

				}
				if (map_[i][j] == 3) {
					map_[i][j] = 1;

				}

			}
		}

	}

	
	if (count_ < stepsCount_) {
		if (num2_ != 9) {
			num1_ += 1;
			if (num1_ > 9) {
				num1_ = 0;
				num2_ += 1;
			}
		}
		count_ = stepsCount_;
	}
	

	Vector3 WorldPos = worldTransform_.GetWorldPos();
	Vector4 Mat1 = { goal_.m[3][0],goal_.m[3][1],goal_.m[3][2],goal_.m[3][3] };
	Vector4 Mat2 = { start_.m[3][0],start_.m[3][1],start_.m[3][2],start_.m[3][3] };
	PlayerMap = { (goal_.m[3][2] / 2) * -1,(goal_.m[3][0] / 2) };
	ImGui::Begin("player");
	ImGui::DragFloat4("translation", &WorldPos.x, 0.01f);
	ImGui::DragFloat2("translation", &PlayerMap.x, 0.01f);
	ImGui::DragFloat4("translation", &Mat2.x, 0.01f);
	ImGui::End();
	//worldTransform_.UpdateMatrix();
	ImGui::Begin("number");
	ImGui::Text("step %d", stepsCount_);
	ImGui::Text("NuwNumber %d", map_[(int)(PlayerMap.x)][(int)(PlayerMap.y)]);
	ImGui::Text("number %f", number);
	ImGui::Text("goNumber %f", goalNum_);

	ImGui::Text(" switch_%d", isHit_);

	ImGui::Text(" clear%d", gameClear);
	ImGui::Text(" %d%d", num2_,num1_);

	ImGui::End();
	worldTransform_.TransferMatrix();
	

}

void Player::TitleUpdate()
{



	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };
	if (MoveFlag == false && JumFlag_ == false) {
		if (titleCount_ < 3) {
			Vector3 move = { 0.0f,0.0f,2.0f };

			Quaternion	newquaternion_ = createQuaternion(rad, { -1.0f,0.0f,0.0f });
			newquaternion_ = Normalize(newquaternion_);
			quaternion_ = Multiply(quaternion_, newquaternion_);
			Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);
			//Vector3 rotatedVector = rotateVectorWithQuaternion(quaternion_, Move);
			Translation_ = Add(move, Translation_);
			/*	Matrix4x4 a = MakeTranslateMatrix(Translation_);
				quaternionMat = Multiply(quaternionMat, a);
				Matrix4x4 goalmatrix = Multiply(worldTransform_.matWorld_, quaternionMat);*/
			Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
			goal_ = goalmatrix;
			start_ = worldTransform_.matWorld_;
			MoveFlag = true;
			
		}
		else if (titleCount_ < 6) {


			Vector3 move = { -2.0f,0.0f,0.0f };
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
		else if (titleCount_ < 9) {
			Vector3 move = { 0.0f,0.0f,-2.0f };
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

		else if (titleCount_ < 12) {
			Vector3 move = { 2.0f,0.0f,0.0f };
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


	}
	if (input_->PushKey(DIK_RETURN)) {
		if (MoveFlag == false) {
			
			Vector3 move = { 0.0f,2.0f,0.0f };
			Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,1.0f,0.0f });
			newquaternion_ = Normalize(newquaternion_);
			quaternion_ = Multiply(quaternion_, newquaternion_);
			Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

			Translation_ = Add(move, Translation_);

			Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
			goal_ = goalmatrix;
			start_ = worldTransform_.matWorld_;
		}
		//MoveFlag = false;
		JumFlag_ = true;
	}
	if (MoveFlag == true) {
		if (moveSpeed <= 1.0f) {
			moveSpeed += 0.05f;
		}
		else
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
			titleCount_++;
			if (JumFlag_ == true) {

				Vector3 move = { 0.0f,2.0f,0.0f };
				Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,1.0f,0.0f });
				newquaternion_ = Normalize(newquaternion_);
				quaternion_ = Multiply(quaternion_, newquaternion_);
				Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

				Translation_ = Add(move, Translation_);

				Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
				goal_ = goalmatrix;
				start_ = worldTransform_.matWorld_;
			}
		}
		if (titleCount_ >= 12) {
			titleCount_ = 0;
		}

	}
	if (JumFlag_ == true) {
		if (moveSpeed <= 1.0f) {
			moveSpeed += 0.05f;
		}
		else
		{
			moveSpeed = 1.0f;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				worldTransform_.matWorld_.m[i][j] = Lerp(moveSpeed, start_.m[i][j], goal_.m[i][j]);
			}
		}if (moveSpeed >= 1.0f) {
			worldTransform_.matWorld_ = goal_;
			Vector3 move = { 0.0f,3.0f,0.0f };
			Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,1.0f,0.0f });
			newquaternion_ = Normalize(newquaternion_);
			quaternion_ = Multiply(quaternion_, newquaternion_);
			Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

			Translation_ = Add(move, Translation_);

			Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
			goal_ = goalmatrix;
			start_ = worldTransform_.matWorld_;
			JumFlag_ = true;
			moveSpeed = 0.0f;
		}

	}
	worldTransform_.TransferMatrix();
}

void Player::SelectUpdate()
{
	
	ImGui::Begin("pp");
	ImGui::DragFloat3("transform", &Translation_.x);
	ImGui::End();
	if (input_->PushKey(DIK_A) || stageSelectMoveLeftCoumt_ != 0) {
		if (stageSelectCount_ < 1 && stageSelectMoveLeftCoumt_ == 6) {
			SetTranslation({ 100.0f,0.0f,0.0f });
			worldTransform_.TransferMatrix();
		}
		if (MoveFlag == false && stageSelectMoveRightCoumt_ == 0) {
			if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y - 1)] != 2 && map_[(int)(PlayerMap.x + 1)][(int)(PlayerMap.y)] != 3) {
				Vector3 move = { -2.0f,0.0f,0.0f };
				Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,0.0f,-1.0f });
				newquaternion_ = Normalize(newquaternion_);
				quaternion_ = Multiply(quaternion_, newquaternion_);
				Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

				Translation_ = Add(move, Translation_);

				Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
				goal_ = goalmatrix;
				start_ = worldTransform_.matWorld_;
				MoveFlag = true;
				stageSelectMoveLeftCoumt_++;
			}
		}
	}


	if (input_->PushKey(DIK_D)||stageSelectMoveRightCoumt_!=0  ) {
		if (stageSelectCount_ > 3&& stageSelectMoveRightCoumt_==6) {
			SetTranslation({ -8.0f,0.0f,0.0f });
			worldTransform_.TransferMatrix();
		}
		
		if (MoveFlag == false && stageSelectMoveLeftCoumt_ == 0) {
			if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y + 1)] != 2 && map_[(int)(PlayerMap.x)][(int)(PlayerMap.y + 1)] != 3) {
				Vector3 move = { 2.0f,0.0f,0.0f };
				Quaternion	newquaternion_ = createQuaternion(rad, { 0.0f,0.0f,1.0f });
				newquaternion_ = Normalize(newquaternion_);
				quaternion_ = Multiply(quaternion_, newquaternion_);
				Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);

				Translation_ = Add(move, Translation_);

				Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
				goal_ = goalmatrix;
				start_ = worldTransform_.matWorld_;
				MoveFlag = true;
				stageSelectMoveRightCoumt_++;
			}
		}
	}


	worldTransform_.scale_ = { 1,1,1 };



	if (MoveFlag == true) {
		if (moveSpeed <= 1.0f) {
			moveSpeed += 0.05f;
		}
		else
		{
			moveSpeed = 1.0f;
		}



		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {

				worldTransform_.matWorld_.m[i][j] = Lerp(moveSpeed, start_.m[i][j], goal_.m[i][j]);


			}

		}


		if (moveSpeed >= 1.0f) {
			MoveFlag = false;
			moveSpeed = 0.0f;
			if (stageSelectMoveRightCoumt_ >= 11) {
				stageSelectMoveRightCoumt_ = 0;
				stageSelectCount_++;
				if (stageSelectCount_ >= 5) {
					stageSelectCount_ = 0;
				}
			}
			if (stageSelectMoveLeftCoumt_ >= 11) {
				stageSelectMoveLeftCoumt_ = 0;
				stageSelectCount_--;
				if (stageSelectCount_ < 0) {
					stageSelectCount_ = 4;
				}
			}
		}
	}
	worldTransform_.TransferMatrix();
}


void Player::Draw(const ViewProjection& view)
{
	
	model_->Draw(worldTransform_, view);
}

void Player::IsFall()
{

	speed_ += 0.01f;
	worldTransform_.matWorld_.m[3][1] -= speed_;
	worldTransform_.translation_.y -= 0.1f;
}

void Player::OnCollision()
{
	speed_ = 0;
	isHit_ = true;
}

void Player::OutCollision()
{

	isHit_ = false;


}

void Player::OnWallCollision()
{
	wallHit_ = true;
}

void Player::OutWallCollision()
{
	wallHit_ = false;
}

void Player::Setparent(const WorldTransform* parent)
{

	worldTransform_.parent_ = parent;


}

void Player::SetMap(const int map[7][7])
{
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = map[i][j];
			sMap_[i][j] = map[i][j];
			if (map_[i][j] == 6) {
				goalPos_ = { 0.0f + j * 2, -2.0f, 0.0f - i * 2 };
			}

		}
	}


}

void Player::SetTranslation(Vector3 translation)
{
	worldTransform_.matWorld_.m[3][0] = translation.x; 
	worldTransform_.matWorld_.m[3][1] = translation.y;
	worldTransform_.matWorld_.m[3][2] = translation.z;
	Translation_ = translation;
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

	if (input_->PushKey(DIK_SPACE) && MoveFlag == false) {
		if ((sMap_[(int)(PlayerMap.x)][(int)(PlayerMap.y)] != 2) && (sMap_[(int)(PlayerMap.x)][(int)(PlayerMap.y)] != 3)) {
			if (switch_) {
				switch_ = false;

			}
			else {
				switch_ = true;

			}
		}

	}

	if (input_->PushKey(DIK_W) && MoveFlag == false) {
		if (map_[(int)(PlayerMap.x - 1)][(int)(PlayerMap.y)] != 2 && map_[(int)(PlayerMap.x - 1)][(int)(PlayerMap.y)] != 3) {
			Vector3 move = { 0.0f,0.0f,2.0f };

			Quaternion	newquaternion_ = createQuaternion(rad, { -1.0f,0.0f,0.0f });
			newquaternion_ = Normalize(newquaternion_);
			quaternion_ = Multiply(quaternion_, newquaternion_);
			Matrix4x4 quaternionMat = quaternionToMatrix(quaternion_);
			//Vector3 rotatedVector = rotateVectorWithQuaternion(quaternion_, Move);
			Translation_ = Add(move, Translation_);
			Matrix4x4 goalmatrix = MakeQuatAffineMatrix({ 1.0f,1.0f,1.0f }, quaternionMat, Translation_);
			goal_ = goalmatrix;
			start_ = worldTransform_.matWorld_;
			MoveFlag = true;

		}
	}


	if (input_->PushKey(DIK_S) && MoveFlag == false) {
		if (map_[(int)(PlayerMap.x + 1)][(int)(PlayerMap.y)] != 2 && map_[(int)(PlayerMap.x +1 )][(int)(PlayerMap.y)] != 3) {
			Vector3 move = { 0.0f,0.0f,-2.0f };
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
	}


	if (input_->PushKey(DIK_A) && MoveFlag == false) {

		if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y - 1)] != 2 && map_[(int)(PlayerMap.x)][(int)(PlayerMap.y-1)] != 3) {
			Vector3 move = { -2.0f,0.0f,0.0f };
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
	}


	if (input_->PushKey(DIK_D) && MoveFlag == false) {
		if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y + 1)] != 2 && map_[(int)(PlayerMap.x)][(int)(PlayerMap.y + 1)] != 3) {
			Vector3 move = { 2.0f,0.0f,0.0f };
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
	}

	
	worldTransform_.scale_ = { 1,1,1 };



	if (MoveFlag == true) {
		if (moveSpeed <= 1.0f) {
			moveSpeed += 0.05f;
		}
		else
		{
			moveSpeed = 1.0f;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {

				worldTransform_.matWorld_.m[i][j] = Lerp(moveSpeed, start_.m[i][j], goal_.m[i][j]);


			}

		}


		if (moveSpeed >= 1.0f) {
			MoveFlag = false;
			moveSpeed = 0.0f;
			audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[0]);
			//サイコロの目を確認(今は、わかりやすいよう上面の番号を表示している)
			number = CheckNumber();
			//感圧版の当たり判定
			if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y)] == 4 && number == 5 && !goalFlag1_) {
				goalFlag1_ = true;
				if (goalFlag2_) {
					goalNum_ = 5;
                    diamond_ = true;
					efectManager_->SetPanelGoal();
					efectManager_->SelectGoal(Ster);
					efectManager_->SetGoalTransform ( goalPos_);
					audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[2]);

				}
				else {
					audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[1]);
				}
				efectManager_->SetPanelSter();
				efectManager_->SetSterTransform({ GetWorldPosition().x,GetWorldPosition().y-1.0f,GetWorldPosition().z });
			}

			if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y)] == 5 && number == 2 && !goalFlag2_) {
				goalFlag2_ = true;
				if (goalFlag1_) {
					goalNum_ = 2;
                    heart_ = true;
					efectManager_->SetPanelGoal();
					efectManager_->SelectGoal(Hert);
					efectManager_->SetGoalTransform(goalPos_);
					audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[2]);
				}
				else {
					audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[1]);

				}
				
				efectManager_->SetPanelHert();
				efectManager_->SetHertTransform({ GetWorldPosition().x,GetWorldPosition().y - 1.0f,GetWorldPosition().z });

			}

			//ゴールの当たり判定
			if (map_[(int)(PlayerMap.x)][(int)(PlayerMap.y)] == 6 && number == goalNum_) {
				gameClear = true;
			}

        stepsCount_ += 1;

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

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる関数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;

}

Vector3 Player::GetMoveWorldPosition() {
	// ワールド座標を入れる関数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = playerMove_.m[3][0];
	worldPos.y = playerMove_.m[3][1];
	worldPos.z = playerMove_.m[3][2];

	return worldPos;


}

