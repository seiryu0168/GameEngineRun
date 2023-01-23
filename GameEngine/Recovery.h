#pragma once
#include"Obstacle.h"
class Recovery : public Obstacle
{
private:
	int hModel_;
	float speedRate_;

public:
	Recovery(GameObject* parent);
	~Recovery();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void OnCollision(GameObject* pTarget);
};

