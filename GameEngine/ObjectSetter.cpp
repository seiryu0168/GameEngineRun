#include "ObjectSetter.h"
#include"Engine/Model.h"
#include"Player.h"
#include"Engine/Fbx.h"
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
	Instantiate<Stage1>(GetParent());
	Instantiate<Player>(GetParent());
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
