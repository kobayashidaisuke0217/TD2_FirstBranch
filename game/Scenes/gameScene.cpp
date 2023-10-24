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


	player_->Initialize(playerModel_.get(),  { 2.0f, 30.0f, -2.0f });

	numTexture_[0] = textureManager_->Load("Resource/number0.png");
	numTexture_[1] = textureManager_->Load("Resource/number1.png");
	numTexture_[2] = textureManager_->Load("Resource/number2.png");
	numTexture_[3] = textureManager_->Load("Resource/number3.png");
	numTexture_[4] = textureManager_->Load("Resource/number4.png");
	numTexture_[5] = textureManager_->Load("Resource/number5.png");
	numTexture_[6] = textureManager_->Load("Resource/number6.png");
	numTexture_[7] = textureManager_->Load("Resource/number7.png");
	numTexture_[8] = textureManager_->Load("Resource/number8.png");
	numTexture_[9] = textureManager_->Load("Resource/number9.png");

	for (int i = 0; i < 2; i++) {
		num_[i] = std::make_unique<Sprite>();
		num_[i]->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 100.0f,100.0f,0.0f,0.0f });
	}


	player_->Initialize(playerModel_.get(), { 2.0f, 30.0f, -2.0f });


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
	stage_->Initialize(BlockModels,Stagenum);

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

	efectmanager_ = EfectManager::GetInstance();
	efectmanager_->Initialize();

	//花火エフェクト用
	sterModel_.reset(Model::CreateModelFromObj("Resource", "star.obj"));
	hertModel_.reset(Model::CreateModelFromObj("Resource", "heartEfect.obj"));
	


	transform1_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1123.0f,20.0f,1.0f} };
	transform2_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1039.0f,20.0f,1.0f} };
	fireworksMove_ = false; 
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	material = { 1.0f,1.0f,1.0f,1.0f };
}

void GameScene::Update()
{
	Change_->Update();
	count_++;
	stage_->Update();
	player_->Update();
	enemy_->Update();
	skyDome_->Update();


	if (player_->GetWorldPosition().y >= 100.0f) {
		Change_->setmoveFlag();
	}
	if (Change_->getchangeFlag() == true) {
		sceneNum = STAGESELECT_SCENE;

	}
	if (player_->isGameover() == true||input_->PushKey(DIK_ESCAPE)) {
		Initialize();
	}
	//player_->SetBlockUp(stage_->GetBlockUp());
	stage_->SetSwitch(player_->GetSwitch() && !fireworksMove_);
	if (player_->GetHeart() && !player_->GetDiamond()) {
		stage_->SetGoalModel(HeartGoalModel_.get());
		fireworksModel_ = hertModel_.get();
		fireworksMove_ = true;

	}else if (!player_->GetHeart() && player_->GetDiamond() && !fireworksMove_) {
		stage_->SetGoalModel(DiamondGoalModel_.get());
		fireworksModel_ = sterModel_.get();
		fireworksMove_ = true;

	}

	
	//花火のエフェクト
	trueFireworks();

	followCamera_->SetShake(stage_->GetShake());
	
	viewProjection_.UpdateMatrix();
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

	

	
	efectmanager_->Update();
	collisionManager_->ClearColliders();
	collisionManager_->AddCollider(player_.get());
	collisionManager_->AddCollider(enemy_.get());
	if (count_ >= 5) {
		collisionManager_->CheckAllCollision();
	}
	ImGui::Begin("tex");
	ImGui::DragFloat3("1", &transform1_.translate.x, 0.1f);
	ImGui::DragFloat3("2", &transform2_.translate.x, 0.1f);
	ImGui::End();
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
	efectmanager_->Draw(viewProjection_);

	// 弾の描画
	for (Fireworks* firework : fireworks_) {
		firework->Draw(viewProjection_);
	}
}

void GameScene::ApplyGlobalVariables()
{
	GlovalVariables* globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	
}

void GameScene::Draw2D() {
	blueMoon_->SetBlendMode(blendCount_);
	//一桁目

	num_[0]->Draw(transform1_, SpriteuvTransform, material, numTexture_[player_->Getnum1()]);
	//二桁目
	num_[1]->Draw(transform2_, SpriteuvTransform, material, numTexture_[player_->Getnum2()]);
	Change_->Draw();
	
	
	
}

void GameScene::Finalize()
{
	
	
	
}

void GameScene::trueFireworks() {
	
	

	if (player_->GetGameClear()) {
		--changeTimer_;
		for (int i = 0; i < 10; ++i) {
			Vector3 velocity = { 0, 0, 0 };
			float numberX = (rand() % 11 - 5) / 5.0f;
			float numberY = (rand() % 11 - 5) / 5.0f;
			float numberZ = (rand() % 11 - 5) / 5.0f;
			velocity = { numberX, numberY, numberZ };
			// 弾を生成、初期化
			Fireworks* newFireworks = new Fireworks();
			newFireworks->Initialize(
				fireworksModel_, player_->GetWorldPosition(), {0.5f, 0.5f, 0.5f},
				velocity, velocity);

			fireworks_.push_back(newFireworks);
		}

		for (Fireworks* fireworks : fireworks_) {

			fireworks->Update();
		}

		if (changeTimer_ < -60) {
			
			fireworks_.remove_if([](Fireworks* fireworks) {
				delete fireworks;
				return true;
			});
		}
	}
}
