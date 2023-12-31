#pragma once
enum  Scene {
	TITLE_SCENE,
	STAGESELECT_SCENE,
	GAME_SCENE,
};
enum  Stages {
	St1,
	St2,
	St3,
	St4,
	St5,
};
class Iscene
{
public:
	virtual ~Iscene() {};
	virtual void Initialize()=0;

	virtual void Update()=0;

	virtual void Draw()=0;

	virtual void Finalize() = 0;
	 int GetSceneNum() { return sceneNum; }

protected:
	static int Stagenum;
	static int sceneNum;
};

