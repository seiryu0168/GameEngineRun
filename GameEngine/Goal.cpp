#include "Goal.h"
#include"Engine/Model.h"
#include"EngineTime.h"

Goal::Goal(GameObject* parent)
	:Obstacle(parent,"Goal"),
	hModel_(-1),
	speedRate_(1.0f)
{
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
	hModel_ = ModelManager::Load("Assets\\GoalTape.fbx");
}

void Goal::Update()
{
	speedRate_ = EngineTime::GetFrame() / 60.0f * 0.01f;
	float moveSpeed = 0.63f + SPEED * speedRate_;
	moveSpeed = min(moveSpeed, MAX_SPEED);
	transform_.position_.z -= moveSpeed;

	if (transform_.position_.z <= -1000.0f)
	{
		KillMe();
	}
}

void Goal::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void Goal::Release()
{
}
