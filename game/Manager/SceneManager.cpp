#include "SceneManager.h"
#include"ImGuiManger.h"
SceneManager::SceneManager()
{
	
	
	
}
SceneManager::~SceneManager()
{
	imguiManager_->Finalize();
	audio_->xAudio2.Reset();
	audio_->SoundUnload(&audio_->soundDatas[0]);
	audio_->SoundUnload(&audio_->soundDatas[1]);
	audio_->SoundUnload(&audio_->soundDatas[2]);
	audio_->SoundUnload(&audio_->soundDatas[3]);
	audio_->SoundUnload(&audio_->soundDatas[4]);
	audio_->SoundUnload(&audio_->soundDatas[5]);
	audio_->SoundUnload(&audio_->soundDatas[6]);
	audio_->SoundUnload(&audio_->soundDatas[7]);
}
void SceneManager::Run() {
	Initialize();
	
	while (true) {
		
		// メッセージ処理
		if (winApp_->Procesmessage()) {
			break;
		}

        imguiManager_->Begin();

		
		
        input->Update();
		glovalVariables_->Update();
		directionallight_->Update();
		blueMoon_->BeginFrame();
		
		preSceneNum_ = sceneNum_;
		if (input->PressKey(DIK_RETURN) && input->PressKey(DIK_ESCAPE)) {
			
			sceneNum_ = TITLE_SCENE;
			
			//preSceneNum_ = TITLE_SCENE;
		}
		else {
			sceneNum_ = sceneArr_[sceneNum_]->GetSceneNum();
		}
		if (sceneNum_ != preSceneNum_) {
			sceneArr_[preSceneNum_]->Finalize();
			sceneArr_[sceneNum_]->Initialize();
			
		}
		sceneArr_[sceneNum_]->Update();
		
		
		
		sceneArr_[sceneNum_]->Draw();
		
		

#ifdef _DEBUG
		imguiManager_->End();

		imguiManager_->Draw();
#endif // _DEBUG

		blueMoon_->EndFrame();
	}
	CoUninitialize();
	blueMoon_->Finalize();
	sceneArr_[sceneNum_]->Finalize();
	
}

void SceneManager::Initialize()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	blueMoon_ = BlueMoon::GetInstance();
	blueMoon_->Initialize( 1280, 720);
	winApp_ = WinApp::GetInstance();
    input=Input::GetInstance();
	input->Initialize(winApp_);
	textureManager_ = Texturemanager::GetInstance();
	textureManager_->Initialize();
	imguiManager_ = ImGuiManger::GetInstance();
	imguiManager_->Initialize(winApp_, blueMoon_->GetDirectXCommon());
	glovalVariables_ = GlovalVariables::GetInstance();
	glovalVariables_->LoadFiles();
	directionallight_ = DirectionalLight::GetInstance();
	directionallight_->Initialize();
	sceneArr_[TITLE_SCENE] = std::make_unique <TitleScene>();
	sceneArr_[STAGESELECT_SCENE] = std::make_unique<StageSelectScene>();
	sceneArr_[GAME_SCENE] = std::make_unique <GameScene>();
	sceneNum_ = TITLE_SCENE;
	sceneArr_[sceneNum_]->Initialize();
	
	audio_ = Audio::GetInstance();
	audio_->Initialize();
	audio_->soundDatas[7] = audio_->SoundLoadWave("resource/Audio/BGM.wav");
	audio_->SoundPlayloop(audio_->xAudio2.Get(), audio_->soundDatas[7], 0.05f);
}


