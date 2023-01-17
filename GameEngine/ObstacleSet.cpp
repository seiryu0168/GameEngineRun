#include "ObstacleSet.h"
#include"Engine/Model.h"
#include"Stage1.h"
#include"NormalBlock.h"	
#include<iostream>
namespace
{
	static const XMVECTOR ROTATE_AXIS  = XMVectorSet(0, 0, 1, 0);
	static const XMFLOAT3 RAYCAST_DIR  = XMFLOAT3(0, -1, 0);
	static const int	  SET_INTERVAL = 30;
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
	transform_.position_.z = 20;
	ray.start = transform_.position_;
	ModelManager::RayCast(((Stage1*)FindObject("Stage1"))->GetModelHandle(),ray);

	vSet_ = XMVectorSet(0, -1, 0, 0) * (ray.dist-1.0f);
	ChangeState(SetPattern1::GetInstance());
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

void ObstacleSet::SetPattern1::Init(ObstacleSet& ptn)
{
	srand((unsigned int)time(NULL));
}

void ObstacleSet::SetPattern1::Update(ObstacleSet& ptn)
{
	settingTime_++;

	if (settingTime_==SET_INTERVAL)
	{

		XMVECTOR qRotate;
		XMVECTOR setVec;
		qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, (float)((float)(rand() % 315)/100.0f));
		setVec = XMVector3Rotate(ptn.GetvSet(), qRotate);
		GameObject* obj = ptn.Instantiate<NormalBlock>((GameObject*)(&ptn)->GetParent());
		XMFLOAT3 pos;
		XMFLOAT3 setterPos = ptn.GetPosition();
		XMStoreFloat3(&pos, setVec);
		XMStoreFloat3(&pos, XMLoadFloat3(&setterPos)+setVec);
		obj->SetPosition(pos);
		settingTime_ = 0;
	}
}

void ObstacleSet::SetPattern2::Init(ObstacleSet& ptn)
{
}

void ObstacleSet::SetPattern2::Update(ObstacleSet& ptn)
{
}
