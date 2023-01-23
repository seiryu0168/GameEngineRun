#include "TitleUI.h"
#include"ImageManager.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"

namespace
{
	static const int MAX_BUTTON = 2;
	static const int INTERVAL   = 10;
}
TitleUI::TitleUI(GameObject* parent) :
	GameObject(parent, "TitleUI"),
	hPictBase_(-1),
	hPictPlay_(-1),
	hPictExit_(-1),
	buttonNum_(0),
	inputInterval_(INTERVAL)
{
}

TitleUI::~TitleUI()
{
}

void TitleUI::Initialize()
{
	hPictPlay_ = ImageManager::Load("Assets\\PlayImage.png");
	assert(hPictPlay_ >= 0);
	ImageManager::SetImagePos(hPictPlay_, XMFLOAT3(-800, -200, 0));

	hPictExit_ = ImageManager::Load("Assets\\ExitImage.png");
	assert(hPictExit_ >= 0);
	ImageManager::SetImagePos(hPictExit_, XMFLOAT3(800, -200, 0));
	hPictBase_ = ImageManager::Load("Assets\\TitleImage.png");
	assert(hPictBase_ >= 0);
}

void TitleUI::Update()
{
	inputInterval_++;
	if (inputInterval_ > INTERVAL)
	{
		if (Input::GetLStick_X() >= 0.7f)
		{
			buttonNum_++;
		}
		else if (Input::GetLStick_X() <= -0.7f)
		{
			buttonNum_--;
		}
		inputInterval_ = 0;
	}
	int num = abs(buttonNum_ % MAX_BUTTON);
	switch (num)
	{
	case 0:
		ImageManager::SetImageSize(hPictPlay_, XMFLOAT3(1.2f,1.2f,1.2f));
		ImageManager::ColorChange(hPictPlay_, XMFLOAT4(1.9f, 1.9f, 1.9f, 1.0f));

		ImageManager::SetImageSize(hPictExit_, XMFLOAT3(1, 1, 1));
		ImageManager::ColorChange(hPictExit_, XMFLOAT4(1, 1, 1,1));
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		{
			((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_PLAY);
		}
		break;
	case 1:
		ImageManager::SetImageSize(hPictExit_, XMFLOAT3(1.2f, 1.2f, 1.2f));
		ImageManager::ColorChange(hPictExit_, XMFLOAT4(1.9f, 1.9f, 1.9f, 1.0f));

		ImageManager::SetImageSize(hPictPlay_, XMFLOAT3(1, 1, 1));
		ImageManager::ColorChange(hPictPlay_, XMFLOAT4(1, 1, 1, 1));
		break;

	default:
		break;
	}
}

void TitleUI::Release()
{
}
