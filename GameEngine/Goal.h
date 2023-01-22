#pragma once
#include"Obstacle.h"
class Goal : public Obstacle
{
private:
	int hModel_;
	float speedRate_;
public:
	Goal(GameObject* parent);
	~Goal();
	void Initialize() override;

	void Update() override;
		
	void Draw() override;

	void Release() override;
		
		
};

