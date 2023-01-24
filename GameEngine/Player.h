#pragma once
#include"Engine/GameObject.h"
class Player : public GameObject
{
private:
	bool godMode_;
	bool recover_;
	bool jump_;
	float jumpTime_;
	int godTime_;
	int hModel_;
	int hPictDamege_;
	int hPictDmegeFrash_;
	int hPictRecovery_;
	int hp_;
	float speedRate;
	float rotate;
	XMVECTOR vCamPos_;
	XMVECTOR CENTER_VEC;
	XMVECTOR centerPos_;



public:
	Player(GameObject* parent);
	~Player();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	void CameraControl();
	
	int GetHP() { return hp_; }

	float GetSpeedRate() { return speedRate; }
};