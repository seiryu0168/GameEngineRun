#include "Player.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"EngineTime.h"
#include"Engine/Camera.h"
#include"Engine/SphereCollider.h"
#include"Stage1.h"
namespace
{
	static const XMVECTOR ROTATE_AXIS		= XMVectorSet(0, 0, 1, 0);
	static const float    INPUT_ATTENUATION = 0.2f;
	static const float	  ROLLING_SPEED		= 5.0f;
	static const float	  MAX_SPEED			= 5.0f;
	static const int	  MAX_GOD_TIME		= 40;
}
Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),
	centerPos_(XMVectorSet(0,0,0,0)),
	hModel_(-1),
	rotate(0),
	vCamPos_(XMVectorSet(0, 5, -15, 0)),
	godTime_(0),
	speedRate(0),
	hp_(2)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider(pCollision);

	centerPos_ = XMLoadFloat3(&transform_.position_);
	RayCastData ray;
	ray.dir = { 0,-1,0 };
	ray.start = transform_.position_;
	int stage = ((Stage1*)FindObject("Stage1"))->GetModelHandle();
	ModelManager::RayCast(stage,ray);
	
	centerPos_ = XMVector3Normalize((ray.hitPos - centerPos_))*(ray.dist-1.0f);
	transform_.position_.z = 10;
}

void Player::Update()
{
	speedRate = EngineTime::GetFrame() / 60.0f * 0.01f;
	speedRate = min(speedRate, MAX_SPEED);
	rotate = Input::GetLStick_X()*INPUT_ATTENUATION* speedRate;
	XMVECTOR qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, rotate);
	vCamPos_= XMVector3Rotate(vCamPos_, qRotate);
	centerPos_ = XMVector3Rotate(centerPos_, qRotate);
	XMStoreFloat3(&transform_.position_, centerPos_);
	transform_.rotate_.x += 4.0f;
	
	CameraControl();
	if (godMode_ == true && godTime_ < 30)
	{
		godTime_++;
	}
	else
		godMode_ = false;

}

void Player::Draw()
{
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetTag() == "Block"&&godMode_==false)
	{
		hp_--;
		godMode_ = true;
		godTime_ = 0;
	}
	if (pTarget->GetTag() == "Restore")
	{
		hp_++;
	}
}

void Player::CameraControl()
{
	
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR target = XMVectorSet(0, 0, 70, 0);
	Camera::SetUpVector(-centerPos_);
	Camera::SetPosition(centerPos_);// +vCamPos_);
	Camera::SetTarget(pos+target);
}
