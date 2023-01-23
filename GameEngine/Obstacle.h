#pragma once
#include"Engine/GameObject.h"
#include"EngineTime.h"
class Obstacle : public GameObject
{

public :
	const float DEFAULT_SPEED;
	const float SPEED;
	const float MAX_SPEED;
	Obstacle(GameObject* parent, std::string name);
	~Obstacle();

	virtual void Initialize() =0;

	virtual void Update() {};

	virtual void Draw() {};

	virtual void Release() =0;

};

