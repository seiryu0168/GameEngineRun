#pragma once
#include"Engine/GameObject.h"
#include"Result.h"
class ResultScene : public GameObject
{
private:
	int hPict_;
	int hPictScore_[3];
	int time_;
	Result* rslt_;
	short score_;
public:
	ResultScene(GameObject* parent);
	~ResultScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

