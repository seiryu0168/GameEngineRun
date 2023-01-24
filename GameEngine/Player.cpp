#include "Player.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"EngineTime.h"
#include"Engine/Camera.h"
#include"Engine/SphereCollider.h"
#include"ImageManager.h"
#include"Stage1.h"
namespace
{
	static const XMVECTOR ROTATE_AXIS		= XMVectorSet(0, 0, 1, 0);
	static const float    INPUT_ATTENUATION = 0.2f;
	static const float	  ROLLING_SPEED		= 5.0f;
	static const float	  MAX_SPEED			= 5.0f;
	static const int	  MAX_GOD_TIME		= 40;
	static const int	  MAX_LIFE			= 5;
}
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),
	jump_(false),
	godMode_(false),
	recover_(false),
	jumpTime_(0),
	centerPos_(XMVectorSet(0,0,0,0)),
	hModel_(-1),
	hPictDamege_(-1),
	hPictDmegeFrash_(-1),
	hPictRecovery_(-1),
	rotate(0),
	vCamPos_(XMVectorSet(0, 5, -15, 0)),
	godTime_(0),
	speedRate(0),
	hp_(MAX_LIFE)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hPictDamege_ = ImageManager::Load("Assets\\DamegeTexture.png");
	assert(hPictDamege_ >= 0);
	hPictDmegeFrash_ = ImageManager::Load("Assets\\DamegeImage_2.png");
	assert(hPictDmegeFrash_ >= 0);
	hPictRecovery_ = ImageManager::Load("Assets\\RecoveryImage.png");
	assert(hPictRecovery_ >= 0);
	ImageManager::SetAlpha(hPictRecovery_, 0);
	ImageManager::SetAlpha(hPictDmegeFrash_, 0);
	ImageManager::SetAlpha(hPictDamege_, 0);
	SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider(pCollision);

	centerPos_ = XMLoadFloat3(&transform_.position_);
	RayCastData ray;
	ray.dir = { 0,-1,0 };
	ray.start = transform_.position_;
	int stage = ((Stage1*)FindObject("Stage1"))->GetModelHandle();
	ModelManager::RayCast(stage,ray);
	
	CENTER_VEC = XMVector3Normalize((ray.hitPos - centerPos_))*(ray.dist-1.0f);
	
	transform_.position_.z = 10;
}

void Player::Update()
{
	//ŽžŠÔŒo‰ß‚É‚æ‚Á‚ÄŠp‘¬“x‚ª•Ï‚í‚é
	speedRate = EngineTime::GetFrame() / 60.0f * 0.02f;
	speedRate = min(speedRate, MAX_SPEED);
	rotate = Input::GetLStick_X()*INPUT_ATTENUATION* speedRate;

	XMVECTOR qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, rotate);
	
	//ƒWƒƒƒ“ƒv
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A)&&jump_==false)
	{
		jump_ = true;
	}

	if (jump_ == true)
	{
		jumpTime_ += (M_PI/180.0f)*5.0f;
		if (jumpTime_ > M_PI)
		{
			jumpTime_ = 0;
			jump_ = false;
		}
	}
	centerPos_ = XMVector3Rotate(CENTER_VEC, qRotate);
	CENTER_VEC = centerPos_;
	centerPos_ *= (1 - (sin(jumpTime_) * 0.95));
	XMStoreFloat3(&transform_.position_, centerPos_);

	CameraControl();

	//–³“GŽžŠÔ‚ÌŒvŽZ
	if ((godMode_ == true||recover_==true) && godTime_ > 0)
	{
		ImageManager::SetAlpha(hPictDmegeFrash_, 255.0f * (godTime_ / 30.0f));
		ImageManager::SetAlpha(hPictRecovery_, 255.0f * (godTime_ / 30.0f));
		godTime_--;
	}
	else
	{
		godMode_ = false;
		recover_ = false;
	}

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
		hp_ = max(hp_, 0);
		ImageManager::SetAlpha(hPictDamege_, 255.0f * ((float)(MAX_LIFE-hp_) / (float)MAX_LIFE));
		ImageManager::SetAlpha(hPictDmegeFrash_, 255.0f);
		godMode_ = true;
		godTime_ = 30;
	}
	if (pTarget->GetTag() == "Recovery" && godMode_ == false)
	{
		hp_++;
		hp_ = min(hp_, MAX_LIFE);
		ImageManager::SetAlpha(hPictDamege_, 255.0f * ((float)(MAX_LIFE - hp_) / MAX_LIFE));
		ImageManager::SetAlpha(hPictRecovery_, 255.0f);
		recover_ = true;
		godTime_ = 30;
	}
}

void Player::CameraControl()
{
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMFLOAT3 target = XMFLOAT3(0, 0, 70);
	if(godMode_&&recover_==false)
	{ 
		target.x += rand() % 10 / 10.0f;
		target.y += rand() % 10 / 10.0f;
	}
	Camera::SetUpVector(-centerPos_);
	Camera::SetPosition(XMLoadFloat3(&transform_.position_));
	Camera::SetTarget(pos+XMLoadFloat3(&target));
}
