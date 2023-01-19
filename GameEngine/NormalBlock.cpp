#include "NormalBlock.h"
#include"EngineTime.h"
#include"Engine/Model.h"

namespace
{
	static const float SPEED = 6.0f;
}
NormalBlock::NormalBlock(GameObject* parent)
	:GameObject(parent,"NormalBlock"),
	hModel_(-1),
	speedRate_(1.0f)
{
}

NormalBlock::~NormalBlock()
{
}

void NormalBlock::Initialize()
{
	hModel_ = ModelManager::Load("Assets\\BlueBall.fbx");
	assert(hModel_ >= 0);
}

void NormalBlock::Update()
{
	speedRate_ = EngineTime::GetFrame() / 60.0f * 0.01f;
	transform_.position_.z -= SPEED*speedRate_;
}

void NormalBlock::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void NormalBlock::Release()
{
}
