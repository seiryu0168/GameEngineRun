#pragma once
#include"Engine/GameObject.h"
class Timer : public GameObject
{
private:
	int hPictNum_[20];
	int time_;
	int prevTime_;

public:
	Timer(GameObject* parent);
	~Timer();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

