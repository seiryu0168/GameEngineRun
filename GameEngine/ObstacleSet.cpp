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
	srand((unsigned int)time(NULL));
	RayCastData ray;
	ray.dir = RAYCAST_DIR;
	ray.start = transform_.position_;
	ModelManager::RayCast(((Stage1*)FindObject("Stage1"))->GetModelHandle(),ray);

	vSet_ = XMVector3Normalize((ray.hitPos-XMLoadFloat3(&transform_.position_))) * (ray.dist-1.0f);
	ChangeState(SetPattern1::GetInstance());

	NormalBlock* pNormal = nullptr;
	XMFLOAT3 initPos = {};
	XMFLOAT3 setPos = transform_.position_;
	setPos.z = 30;
	XMVECTOR qRotate = XMVectorSet(0, 0, 0, 0);
	for (int i = 0; i < 20; i++)
	{
		pNormal = Instantiate<NormalBlock>(GetParent());
		qRotate= XMQuaternionRotationAxis(ROTATE_AXIS, (float)((float)(rand() % 630) / 100.0f));
		vSet_ = XMVector3Rotate(vSet_, qRotate);
		XMStoreFloat3(&initPos, XMLoadFloat3(&setPos) + vSet_);
		pNormal->SetPosition(initPos);
		setPos.z+=20;
	}
	transform_.position_.z = 600;
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
	
}

void ObstacleSet::SetPattern1::Update(ObstacleSet& ptn)
{
	settingTime_++;

	if (settingTime_==SET_INTERVAL)
	{
		XMVECTOR qRotate;
		XMVECTOR setVec;
		qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, (float)((float)(rand() % 630)/100.0f));
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
