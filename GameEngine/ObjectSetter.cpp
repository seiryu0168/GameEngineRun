#include "ObjectSetter.h"
#include"Engine/Model.h"
#include"Player.h"
#include"Engine/Fbx.h"
#include"Timer.h"
#include"ObstacleSet.h"
#include"TitleUI.h"
#include"SetObject.h"
#include"Test.h"
#include"Stage1.h"

ObjectSetter::ObjectSetter(GameObject* parent)
{
}

ObjectSetter::~ObjectSetter()
{
}

void ObjectSetter::Initialize()
{
	std::string sceneName = GetParent()->GetObjectName();
	if (sceneName == "TitleScene")
	{
		Instantiate<TitleUI>(GetParent());
	}

	if (sceneName == "PlayScene")
	{
		Instantiate<Stage1>(GetParent());
		Instantiate<Player>(GetParent());
		Instantiate<ObstacleSet>(GetParent());
		Instantiate<Timer>(GetParent());
	}

}

void ObjectSetter::Update()
{

}

void ObjectSetter::Draw()
{
}

void ObjectSetter::Release()
{
}
