#include "Player.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Stage1.h"
namespace
{
	static const XMVECTOR ROTATE_AXIS		= XMVectorSet(0, 0, 1, 0);
	static const float    INPUT_ATTENUATION = 0.2f;
	static const float	  ROLLING_SPEED		= 5.0f;
}
Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),
	centerPos_(XMVectorSet(0,0,0,0)),
	hModel_(-1),
	rotate(0),
	vCamPos_(XMVectorSet(0, 5, -15, 0))
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	centerPos_ = XMLoadFloat3(&transform_.position_);
	transform_.position_.z = 10;
	RayCastData ray;
	ray.dir = { 0,-1,0 };
	ray.start = transform_.position_;
	int stage = ((Stage1*)FindObject("Stage1"))->GetModelHandle();
	ModelManager::RayCast(stage,ray);
	
	XMStoreFloat3(&transform_.position_, ray.hitPos);
	transform_.position_.y += 1.0f;
	hModel_ = ModelManager::Load("Assets\\BlueBall.fbx");
	centerPos_ = XMLoadFloat3(&transform_.position_) - centerPos_;
	assert(hModel_ >= 0);
}

void Player::Update()
{

	rotate = Input::GetLStick_X()*INPUT_ATTENUATION;
	XMVECTOR qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, rotate);
	vCamPos_= XMVector3Rotate(vCamPos_, qRotate);
	centerPos_ = XMVector3Rotate(centerPos_, qRotate);
	XMStoreFloat3(&transform_.position_, centerPos_);
	transform_.rotate_.x += 4.0f;
	
	CameraControl();

}

void Player::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void Player::Release()
{
}

void Player::CameraControl()
{
	
	XMFLOAT3 pos = { 0,5,-10 };
	XMVECTOR target = XMVectorSet(0, 0, 5, 0);
	Camera::SetUpVector(-centerPos_);
	Camera::SetPosition(centerPos_+vCamPos_);
	Camera::SetTarget(XMLoadFloat3(&transform_.position_)+target);
}
