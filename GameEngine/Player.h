#pragma once
#include"Engine/GameObject.h"
class Player : public GameObject
{
private:
	bool godMode_;
	bool boost_;
	int godTime_;
	int hModel_;
	int hp_;
	float speedRate;
	float rotate;
	XMVECTOR vCamPos_;
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

	float GetSpeedRate() { return speedRate; }
};