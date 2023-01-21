#include"RootJob.h"
#include "SceneManager.h"
#include"../TestScene.h"
#include"../PlayScene.h"
#include"../ResultScene.h"
#include"../ImageManager.h"
#include"../TitleScene.h"
#include"../EngineTime.h"
#include"Model.h"


SceneManager::SceneManager(GameObject* parent) 
	: GameObject(parent, "SceneManager"),currentSceneID_(0),nextSceneID_(0)
{

}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		KillAllChildren();
		ModelManager::Release();
		ImageManager::AllRelease();
		EngineTime::ResetFrame();

		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE	: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY	: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		case SCENE_ID_TEST	: Instantiate<TestScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{

}

void SceneManager::Release()
{

}
void SceneManager::ChangeScene(int sceneID)
{
	nextSceneID_ = sceneID;
}
