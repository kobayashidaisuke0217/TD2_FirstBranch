#include "Stageh.h"



void Stage::Initialize(const std::vector<Model*>& models,int stagenum) {

	input_ = Input::GetInstance();
	modelNormal_= models[0];
	modelHeart_ = models[1];
	modelDiamond_ = models[2];
	modelGoal_ = models[3];
	/*blockUp = false;
	shake_ = false;*/
	for (int i = 0; i < 49; i++) {
		worldTransformNormal_[i].Initialize();
		worldTransformUp_[i].Initialize();
		worldTransformDown_[i].Initialize();
	}

	worldTransformHeart_.Initialize();
	worldTransformDiamond_.Initialize();
	worldTransformGoal_.Initialize();

	

	if (stagenum == Stages1) {
		Stage1Initialize();
		
	}
	if (stagenum == Stages2) {
		Stage2Initialize();
		
	}
	if (stagenum == Stages3) {
		Stage3Initialize();
		
	}
	if (stagenum == Stages4) {
		Stage4Initialize();

	}
	if (stagenum == Stages5) {
		Stage5Initialize();
		
	}

	for (int i = 0; i < 53; i++) {
		move[i] = (std::rand() % 3 / 10.0f)+0.2f;
	}
	shakeCount_ = 0;
}

void Stage::Update() {

	

	

	if (blockUp) {
		shake_ = true;
		Up += 0.05f;
		Down -= 0.05f;
		if (Up >= 0) {
			Up = 0;
		}
		if (Down <= -2.0f) {
			Down = -2.0f;
			shake_ = false;
		}
	}
	else {
		shake_ = true;
		Up -= 0.05f;
		Down += 0.05f;
		if (Up <= -2.0f) {
			Up = -2.0f;
		}
		if (Down >= 0) {
			Down = 0;
			shake_ = false;
		}
	}
	if (!countOver_) {
		for (int i = 0; i < 49; i++) {
			worldTransformUp_[i].translation_.y = Up;
			worldTransformDown_[i].translation_.y = Down;
		}
	}
	if (countOver_) {
		shakeCount_++;
		if (shakeCount_ < 15) {
			shake_ = true;
		}
		else {
			shake_ = false;

			for (int i = 0; i < 49; i++) {
				worldTransformNormal_[i].translation_.y -= move[i];
				worldTransformUp_[i].translation_.y -= move[i];
				worldTransformDown_[i].translation_.y -= move[i];
				move[i] += 0.015f;
			}
			worldTransformHeart_.translation_.y -= move[50];
			worldTransformDiamond_.translation_.y -= move[51];
			worldTransformGoal_.translation_.y -= move[52];
		}
	}
	
	for (int i = 0; i <49; i++) {
	   worldTransformNormal_[i].UpdateMatrix();
	   worldTransformUp_[i].UpdateMatrix();
	   worldTransformDown_[i].UpdateMatrix();
	}
	
	worldTransformHeart_.UpdateMatrix();
	worldTransformDiamond_.UpdateMatrix();
	worldTransformGoal_.UpdateMatrix();
	ImGui::Begin("Up");
	ImGui::Text("%f", Up);
	
	ImGui::End();

	ImGui::Begin("box");
	ImGui::DragFloat4("translation", &worldTransformNormal_[0].translation_.x, 0.01f);
	ImGui::DragFloat4("translation", &worldTransformNormal_[0].translation_.x, 0.01f);
	ImGui::End();
}

void Stage::Draw(const ViewProjection& viewprojection) {

	for (int i = 0; i < 49; i++) {
		modelNormal_->Draw(worldTransformNormal_[i], viewprojection);
		modelNormal_->Draw(worldTransformUp_[i], viewprojection);
		modelNormal_->Draw(worldTransformDown_[i], viewprojection);
	}
	modelHeart_->Draw(worldTransformHeart_, viewprojection);
	modelDiamond_->Draw(worldTransformDiamond_, viewprojection);
	modelGoal_->Draw(worldTransformGoal_, viewprojection);
}

void Stage::Stage1Initialize() {
	index = -1;
	//0 何もない 1床 2起伏壁_1 3起伏壁_2 4感圧版_1 5感圧版_2 6ゴール
	int map[7][7] = {
		{0,0,0,0,0,0,0},
		{0,1,1,1,1,4,0},
	    {0,1,1,1,1,1,0},
	    {0,1,1,2,3,3,0},
	    {0,1,1,2,1,1,0},
	    {0,5,1,2,1,6,0},
		{0,0,0,0,0,0,0},
	};
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			index += 1;
			if (map_[i][j] == 1) {

				worldTransformNormal_[index].translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			else {
				worldTransformNormal_[index].translation_ = { 4.0f ,-2.0f,-4.0f };
			}
			if (map_[i][j] == 2) {
				worldTransformUp_[index].translation_ = { 0.0f + j * 2,Up,0.0f - i * 2 };
			}
			else {
				worldTransformUp_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 3) {
				worldTransformDown_[index].translation_ = { 0.0f + j * 2,Down,0.0f - i * 2 };
			}
			else {
				worldTransformDown_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 4) {
				worldTransformDiamond_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 5) {
				worldTransformHeart_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 6) {
				worldTransformGoal_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
		}
	}


}


void Stage::Stage2Initialize() {
	index = -1;
	//0 何もない 1床 2起伏壁_1 3起伏壁_2 4感圧版_1 5感圧版_2 6ゴール
	int map[7][7] = {
		{0,0,0,0,0,0,0},
		{0,1,1,1,1,4,0},
		{0,1,1,1,1,1,0},
		{0,3,3,2,3,3,0},
		{0,1,1,2,1,1,0},
		{0,6,1,2,1,5,0},
		{0,0,0,0,0,0,0},
	};
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			index += 1;
			if (map_[i][j] == 1) {

				worldTransformNormal_[index].translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			else {
				worldTransformNormal_[index].translation_ = { 0.0f ,90.0f,0.0f };
			}
			if (map_[i][j] == 2) {
				worldTransformUp_[index].translation_ = { 0.0f + j * 2,Up,0.0f - i * 2 };
			}
			else {
				worldTransformUp_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 3) {
				worldTransformDown_[index].translation_ = { 0.0f + j * 2,Down,0.0f - i * 2 };
			}
			else {
				worldTransformDown_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 4) {
				worldTransformDiamond_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 5) {
				worldTransformHeart_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 6) {
				worldTransformGoal_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
		}
	}


}
void Stage::Stage3Initialize() {
	index = -1;
	//0 何もない 1床 2起伏壁_1 3起伏壁_2 4感圧版_1 5感圧版_2 6ゴール
	int map[7][7] = {
		{0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0},
		{0,1,1,1,3,5,0},
		{0,2,2,1,3,1,0},
		{0,4,3,3,1,0,0},
		{0,1,0,1,1,6,0},
		{0,0,0,0,0,0,0},
	};
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			index += 1;
			if (map_[i][j] == 1) {

				worldTransformNormal_[index].translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			else {
				worldTransformNormal_[index].translation_ = { 0.0f ,90.0f,0.0f };
			}
			if (map_[i][j] == 2) {
				worldTransformUp_[index].translation_ = { 0.0f + j * 2,Up,0.0f - i * 2 };
			}
			else {
				worldTransformUp_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 3) {
				worldTransformDown_[index].translation_ = { 0.0f + j * 2,Down,0.0f - i * 2 };
			}
			else {
				worldTransformDown_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 4) {
				worldTransformDiamond_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 5) {
				worldTransformHeart_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 6) {
				worldTransformGoal_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
		}
	}


}
void Stage::Stage4Initialize() {
	index = -1;
	//0 何もない 1床 2起伏壁_1 3起伏壁_2 4感圧版_1 5感圧版_2 6ゴール
	int map[7][7] = {
		{0,0,0,0,0,0,0},
		{0,1,3,1,1,2,0},
		{0,6,1,4,1,1,0},
		{0,1,0,1,1,0,0},
		{0,1,1,2,2,1,0},
		{0,1,3,1,5,1,0},
		{0,0,0,0,0,0,0},
	};
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			index += 1;
			if (map_[i][j] == 1) {

				worldTransformNormal_[index].translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			else {
				worldTransformNormal_[index].translation_ = { 0.0f ,90.0f,0.0f };
			}
			if (map_[i][j] == 2) {
				worldTransformUp_[index].translation_ = { 0.0f + j * 2,Up,0.0f - i * 2 };
			}
			else {
				worldTransformUp_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 3) {
				worldTransformDown_[index].translation_ = { 0.0f + j * 2,Down,0.0f - i * 2 };
			}
			else {
				worldTransformDown_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 4) {
				worldTransformDiamond_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 5) {
				worldTransformHeart_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 6) {
				worldTransformGoal_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
		}
	}


}
void Stage::Stage5Initialize() {
	index = -1;
	//0 何もない 1床 2起伏壁_1 3起伏壁_2 4感圧版_1 5感圧版_2 6ゴール
	int map[7][7] = {
		{0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0},
		{0,3,2,0,5,1,0},
		{0,1,4,1,0,1,0},
		{0,0,0,1,2,1,0},
		{0,6,1,3,1,1,0},
		{0,0,0,0,0,0,0},
	};
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			index += 1;
			if (map_[i][j] == 1) {

				worldTransformNormal_[index].translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			else {
				worldTransformNormal_[index].translation_ = { 0.0f ,90.0f,0.0f };
			}
			if (map_[i][j] == 2) {
				worldTransformUp_[index].translation_ = { 0.0f + j * 2,Up,0.0f - i * 2 };
			}
			else {
				worldTransformUp_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 3) {
				worldTransformDown_[index].translation_ = { 0.0f + j * 2,Down,0.0f - i * 2 };
			}
			else {
				worldTransformDown_[index].translation_ = { 100.0f ,0.0f,0.0f };
			}
			if (map_[i][j] == 4) {
				worldTransformDiamond_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 5) {
				worldTransformHeart_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
			if (map_[i][j] == 6) {
				worldTransformGoal_.translation_ = { 0.0f + j * 2,-2.0f,0.0f - i * 2 };
			}
		}
	}


}


bool Stage::SetSwitch(const bool up) {
	blockUp = up;
	return blockUp;
}

int Stage::GetMap(int i, int j) {
	int map;
	map = map_[i][j];
	return map;
}

Vector3 Stage::GetWorldPositionNormal(int i) {
	// ワールド座標を入れる関数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransformNormal_[i].matWorld_.m[3][0];
	worldPos.y = worldTransformNormal_[i].matWorld_.m[3][1];
	worldPos.z = worldTransformNormal_[i].matWorld_.m[3][2];
	

	return worldPos;
	
	
}

Vector3 Stage::GetWorldPositionUp(int i) {
	// ワールド座標を入れる関数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransformUp_[i].matWorld_.m[3][0];
	worldPos.y = worldTransformUp_[i].matWorld_.m[3][1];
	worldPos.z = worldTransformUp_[i].matWorld_.m[3][2];


	return worldPos;


}

void Stage::SetGoalModel(Model* model) {
	modelGoal_ = model;
}