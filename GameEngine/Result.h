#pragma once
#include"Engine/GameObject.h"
class Result// : public GameObject
{
private:
	int hPictRtnTitle_;
	int hPictReStart_;
	int inputInterval_;
	int buttonNum_;

public:
	Result();
	~Result();
	void Init();

	void Update(GameObject* parent);

	void Release();
};

