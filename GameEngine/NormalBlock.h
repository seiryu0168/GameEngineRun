#pragma once
#include"Engine/GameObject.h"
class NormalBlock : public GameObject
{
private:
	int hModel_;
	float speedRate_;
public:
	NormalBlock(GameObject* parent);
	~NormalBlock();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void OnCollision(GameObject* pTarget) override;
	
	void SetSpeed(float speed) { speedRate_ = speed; }
};

