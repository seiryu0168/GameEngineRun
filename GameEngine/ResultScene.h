#pragma once
#include"Engine/GameObject.h"
class ResultScene : public GameObject
{
private:

public:
	ResultScene(GameObject* parent);
	~ResultScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

