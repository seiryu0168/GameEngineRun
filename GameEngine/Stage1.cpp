#include "Stage1.h"
#include"Engine/Model.h"
#include"EngineTime.h"
namespace
{
	static const float MAX_SCROLL_SPEED = 0.2f;
}
//�R���X�g���N�^
Stage1::Stage1(GameObject* parent)
	:GameObject(parent,"Stage1"),
	hModel_(-1),
	scrollSpeed_(0)
{

}

//�f�X�g���N�^
Stage1::~Stage1()
{

}

//������
void Stage1::Initialize()
{
	hModel_ = ModelManager::Load("Assets\\Feild1.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Stage1::Update() 
{
	scrollSpeed_ = min(0.04f+((float)EngineTime::GetFrame() / 60.0f) * 0.004f,MAX_SCROLL_SPEED);
}

void Stage1::FixedUpdate()
{

}

//�`��
void Stage1::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_, XMFLOAT2(0.1f,-scrollSpeed_));
}

//�J��
void Stage1::Release()
{

}