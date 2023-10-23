#include "gameScene.h"


GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();

	textureManager_ = Texturemanager::GetInstance();
	textureManager_->Initialize();
	collisionManager_ = make_unique<CollisionManager>();
	input_ = Input::GetInstance();
	Change_ = SceneChange::GetInstance();
	Change_->Initialize();
	int a= textureManager_->Load("Resource/tex.png");
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ = make_unique<Player>();
	player_->Initialize(playerModel_.get());

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	skyDomeModel_ .reset( Model::CreateModelFromObj("Resource","skyDome.obj"));
	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	enemy_ = make_unique<Enemy>();
	enemyBodyModel.reset(Model::CreateModelFromObj("Resource", "float_Body.obj"));
	enemyHeadModel.reset(Model::CreateModelFromObj("Resource", "float_head.obj"));
	enemyL_armModel.reset(Model::CreateModelFromObj("Resource", "float_L_arm.obj"));
	enemyR_armModel.reset(Model::CreateModelFromObj("Resource", "float_R_arm.obj"));
	std::vector<Model*>enemyModels = { enemyBodyModel.get(),enemyHeadModel.get(),enemyL_armModel.get(),enemyR_armModel.get() };
	enemy_->Initialize(enemyModels);
	BlockModel_.reset(Model::CreateModelFromObj("Resource", "glound.obj"));
	HeartModel_.reset(Model::CreateModelFromObj("Resource", "heart.obj"));
	DiamondModel_.reset(Model::CreateModelFromObj("Resource", "diamond.obj"));
	GoalModel_.reset(Model::CreateModelFromObj("Resource", "goal.obj"));
	HeartGoalModel_.reset(Model::CreateModelFromObj("Resource", "goalHeart.obj"));
	DiamondGoalModel_.reset(Model::CreateModelFromObj("Resource", "goalDiamond.obj"));
	stage_ = std::make_unique<Stage>();

	std::vector<Model*>BlockModels = { BlockModel_.get(),HeartModel_.get(),DiamondModel_.get(),GoalModel_.get()};
	stage_->Initialize(BlockModels);

	int map_[7][7];
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			map_[i][j] = stage_->GetMap(i, j);
		}
	}
	player_->SetMap(map_);
	
	GlovalVariables* globalVariables{};
	globalVariables = GlovalVariables::GetInstance();
	blendCount_ = 0;
	const char* groupName = "Player";
	GlovalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90.0f);
	ApplyGlobalVariables();
	count_ = 0;



	
}

void GameScene::Update()
{
	count_++;
	stage_->Update();
	player_->Update();
	enemy_->Update();
	if (player_->isGameover() == true) {
		Initialize();
	}
	//player_->SetBlockUp(stage_->GetBlockUp());
	stage_->SetSwitch(player_->GetSwitch());
	if (player_->GetHeart() && !player_->GetDiamond()) {
		stage_->SetGoalModel(HeartGoalModel_.get());

	}else if (!player_->GetHeart() && player_->GetDiamond()) {
		stage_->SetGoalModel(DiamondGoalModel_.get());

	}

	followCamera_->SetShake(stage_->GetShake());
	Change_->Update();
	viewProjection_.UpdateMatrix();
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();



	ImGui::Begin("Scene");

	ImGui::InputInt("blendCount", &blendCount_);
	ImGui::InputFloat3("rotate", &viewProjection_.rotation_.x);
	ImGui::InputInt("SceneNum", &sceneNum);
	if (sceneNum > 1) {
		sceneNum = 1;
	}
	ImGui::End();

	collisionManager_->ClearColliders();
	collisionManager_->AddCollider(player_.get());
	collisionManager_->AddCollider(enemy_.get());
	if (count_ >= 5) {
		collisionManager_->CheckAllCollision();
	}
}


void GameScene::Draw()
{
	//3D描画準備
	blueMoon_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	blueMoon_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D()
{
	skyDome_->Draw(viewProjection_);
	stage_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	
	enemy_->Draw(viewProjection_);
}

void GameScene::ApplyGlobalVariables()
{
	GlovalVariables* globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	
}

void GameScene::Draw2D() {
	blueMoon_->SetBlendMode(blendCount_);
	

}
void GameScene::Finalize()
{
	
	
	
}

/*/使ってない
void GameScene::CheckAllCollision() {
	// 判定対象AとBの座標
	Vector3 posA, posB[25];

	bool Up;

#pragma region 自キャラと地面の当たり判定
	// 自キャラ座標
	posA = player_->GetWorldPosition();
	Up = stage_->GetBlockUp();
	// 自キャラと敵弾全ての当たり判定
	for (int i = 0; i < 25; i++) {
		// 敵弾の座標
		posB[i] = stage_->GetWorldPositionNormal(i);

		// 距離
		float distance = (posB[i].x - posA.x) * (posB[i].x - posA.x) +
			(posB[i].y - posA.y) * (posB[i].y - posA.y) +
			(posB[i].z - posA.z) * (posB[i].z - posA.z);
		float R1 = 1.0f;
		float R2 = 1.0f;
		if (distance <= (R1 + R2) * (R1 + R2)) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			break;
			
		}
		else {
			player_->OutCollision();
		}
	}

#pragma endregion


}
*/

