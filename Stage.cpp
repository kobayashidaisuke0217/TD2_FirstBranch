#include "Stageh.h"


void Stage::Initialize(Model* models) {
	input_ = Input::GetInstance();
	modelNormal_= models;
	for (int i = 0; i < 49; i++) {
		worldTransformNormal_[i].Initialize();
		worldTransformUp_[i].Initialize();
		worldTransformDown_[i].Initialize();
	}


	Stage1Initialize();
	stage1();
}

void Stage::Update() {

	

	

	if (blockUp) {
		Up += 0.1f;
		Down -= 0.1f;
		if (Up >= 0) {
			Up = 0;
		}
		if (Down <= -2.0f) {
			Down = -2.0f;
		}
	}
	else {
		Up -= 0.1f;
		Down += 0.1f;
		if (Up <= -2.0f) {
			Up = -2.0f;
		}
		if (Down >= 0) {
			Down = 0;
		}
	}
	for (int i = 0; i < 49; i++) {
		worldTransformUp_[i].translation_.y = Up;
		worldTransformDown_[i].translation_.y = Down;
	}
	
	for (int i = 0; i <49; i++) {
	   worldTransformNormal_[i].UpdateMatrix();
	   worldTransformUp_[i].UpdateMatrix();
	   worldTransformDown_[i].UpdateMatrix();
	}
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

		}
	}


}


void Stage::stage1() {
	
	
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
