#include "TitleScene.h"
#include"ObjectSetter.h"
#include"Engine/Sprite.h"
#include"Engine/Sprite.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
	Instantiate<ObjectSetter>(this);
}

//�X�V
void TitleScene::Update()
{

	
}

void TitleScene::FixedUpdate()
{

}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}