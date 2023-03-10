#include "NormalBlock.h"
//#include"EngineTime.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"

NormalBlock::NormalBlock(GameObject* parent)
	:Obstacle(parent,"NormalBlock"),
	hModel_(-1),
	speedRate_(1.0f)
{
}

NormalBlock::~NormalBlock()
{
}

void NormalBlock::Initialize()
{
	SetTag("Block");
	SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider(pCollision);	
	hModel_ = ModelManager::Load("Assets\\BlueBall.fbx");
	assert(hModel_ >= 0);
}

void NormalBlock::Update()
{
	speedRate_ = EngineTime::GetFrame() / 60.0f * 0.01f;
	float moveSpeed= DEFAULT_SPEED + SPEED * speedRate_;
	moveSpeed = min(moveSpeed, MAX_SPEED);
	transform_.position_.z -= moveSpeed;

	if (transform_.position_.z <= -1.0f)
	{
		KillMe();
	}
}

void NormalBlock::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void NormalBlock::Release()
{
}

void NormalBlock::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
	}
}
