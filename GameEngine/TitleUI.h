#pragma once
#include"Engine/GameObject.h"
class TitleUI : public GameObject
{
private:
	int hPictBase_;
	int hPictPlay_;
	int hPictExit_;
	int inputInterval_;
	int butttonNum_;
public:
	TitleUI(GameObject* parent);
	~TitleUI();

	void Initialize() override;

	void Update() override;

	void Release() override;


};

