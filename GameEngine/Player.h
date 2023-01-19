#pragma once
#include"Engine/GameObject.h"
class Player : public GameObject
{
private:
	float rotate;
	XMVECTOR vCamPos_;
	XMVECTOR centerPos_;
	int runTime_;
	float speedRate;
	int hModel_;

public:
	Player(GameObject* parent);
	~Player();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void CameraControl();

	float GetSpeedRate() { return speedRate; }
};