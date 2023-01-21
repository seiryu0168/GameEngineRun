#pragma once
#include"Engine/GameObject.h"
class ResultScene : public GameObject
{
private:
	int hPictScore_;
	int hPictStar_;
	int hPictScoreBarBase_;
	int hPictScoreBar_;
	int time_;
public:
	ResultScene(GameObject* parent);
	~ResultScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

