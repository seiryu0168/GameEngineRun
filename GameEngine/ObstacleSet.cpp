#include "ObstacleSet.h"
#include"Engine/Model.h"
#include"NormalBlock.h"	
#include<iostream>
namespace
{
	static const XMVECTOR ROTATE_AXIS = XMVectorSet(0, 0, 1, 0);
	static const XMFLOAT3 RAYCAST_DIR = XMFLOAT3(0, -1, 0);
}
ObstacleSet::ObstacleSet(GameObject* parent)
	:GameObject(parent,"ObstacleSet")
{

}

ObstacleSet::~ObstacleSet()
{
}

void ObstacleSet::Initialize()
{
	RayCastData ray;
	ray.dir = RAYCAST_DIR;
	transform_.position_.z += 10;
	ray.start = transform_.position_;
	ModelManager::RayCast(ray);

	vSet_ = XMVectorSet(0, 0, -1, 0) * (ray.dist-1.0f);
}

void ObstacleSet::Update()
{
	pPattern_->Update(*this);
}

void ObstacleSet::Release()
{
}

void ObstacleSet::ChangeState(PaternState<ObstacleSet>* ptn)
{
	if (pPattern_ != ptn)
	{
		pPattern_ = ptn;
		pPattern_->Init(*this);
	}
}

void ObstacleSet::SetPattern1::Init(SetPattern1& ptn)
{
	srand((unsigned int)time(NULL));
}

void ObstacleSet::SetPattern1::Update(SetPattern1& ptn)
{
	settingTime_++;

	if (settingTime_)
	{

		XMVECTOR qRotate;
		qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, rand() % 10);
		vSet_ = XMVector3Rotate(vSet_, qRotate);
		Instantiate<NormalBlock>(this);
	}
}

void ObstacleSet::SetPattern2::Init(SetPattern2& ptn)
{
}

void ObstacleSet::SetPattern2::Update(SetPattern2& ptn)
{
}
