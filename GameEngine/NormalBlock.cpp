#include "NormalBlock.h"

namespace
{
	static const float SPEED = 1.0f;
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
}

void NormalBlock::Update()
{
	transform_.position_.z -= SPEED*speedRate_;
}

void NormalBlock::Draw()
{
}

void NormalBlock::Release()
{
}
