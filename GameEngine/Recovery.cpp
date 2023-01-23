#include "Recovery.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
Recovery::Recovery(GameObject* parent)
	:Obstacle(parent, "Recovery"),
	hModel_(-1),
	speedRate_(1.0f)
{
}

Recovery::~Recovery()
{
}

void Recovery::Initialize()
{
	SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
	AddCollider(pCollision);
	SetTag("Recovery");
	hModel_ = ModelManager::Load("Assets\\Recovery.fbx");
	assert(hModel_ >= 0);
}

void Recovery::Update()
{
	speedRate_ = EngineTime::GetFrame() / 60.0f * 0.01f;
	float moveSpeed = DEFAULT_SPEED + SPEED * speedRate_;
	moveSpeed = min(moveSpeed, MAX_SPEED);
	transform_.position_.z -= moveSpeed;

	if (transform_.position_.z <= -1.0f)
	{
		KillMe();
	}
}

void Recovery::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void Recovery::Release()
{
}

void Recovery::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
	}
}
