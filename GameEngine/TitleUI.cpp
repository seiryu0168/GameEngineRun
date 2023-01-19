#include "TitleUI.h"
#include"ImageManager.h"
#include"Engine/Input.h"

namespace
{
	static const int MAX_BUTTON = 2;
}
TitleUI::TitleUI(GameObject* parent):
	GameObject(parent,"TitleUI"),
	hPictBase_(-1),
	hPictPlay_(-1),
	hPictExit_(-1),
	butttonNum_(0)
{
}

TitleUI::~TitleUI()
{
}

void TitleUI::Initialize()
{
	hPictBase_ = ImageManager::Load("Assets\\TitleImage.jpg");
	hPictPlay_ = ImageManager::Load("Assets\\PlayImage.jpg");
	hPictExit_ = ImageManager::Load("Assets\\ExitImage.jpg");
}

void TitleUI::Update()
{
	if (Input::GetLStick_X() >= 0.7f)
	{
		butttonNum_++;
	}
	else if (Input::GetLStick_X() <= -0.7f)
	{
		butttonNum_--;
	}
	switch (abs(butttonNum_ / MAX_BUTTON))
	{
	case 1:
		ImageManager::SetImageSize(hPictPlay_, { 1.2f,1.2f });
		break;
	}
}

void TitleUI::Release()
{
}
