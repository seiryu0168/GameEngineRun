#include "Result.h"
#include"Engine/SceneManager.h"
#include"ImageManager.h"
#include"Engine/Input.h"

namespace
{
	static const int INTERVAL   = 30;
	static const int MAX_BUTTON = 2;
}
Result::Result()
	:hPict_(-1),
	 hPictRtnTitle_(-1),
	 hPictReStart_(-1),
	 inputInterval_(0),
	 buttonNum_(0)
{
}

Result::~Result()
{
}

void Result::Init()
{
	hPictRtnTitle_ = ImageManager::Load("Assets\\ReturnTitle.png");
	assert(hPictRtnTitle_ >= 0);
	
	hPictReStart_ = ImageManager::Load("Assets\\ReStart.png");
	assert(hPictReStart_ >= 0);

	hPict_ = ImageManager::Load("Assets\\ResultImage.png");
	assert(hPict_ >= 0);

	ImageManager::SetImagePos(hPictRtnTitle_, XMFLOAT3(-800, -500, 0));
	ImageManager::SetImagePos(hPictReStart_, XMFLOAT3(800, -500, 0));
}

void Result::Update(GameObject* parent)
{
	//入力の間隔を広くする
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
		//タイトルシーンボタン
		ImageManager::SetImageSize(hPictRtnTitle_, XMFLOAT3(1.2f, 1.2f, 1.2f));
		ImageManager::ColorChange(hPictRtnTitle_, XMFLOAT4(1.9f, 1.9f, 1.9f, 1.0f));

		ImageManager::SetImageSize(hPictReStart_, XMFLOAT3(1, 1, 1));
		ImageManager::ColorChange(hPictReStart_, XMFLOAT4(1, 1, 1, 1));

		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		{
			((SceneManager*)parent->FindObject("SceneManager"))->ChangeScene(SCENE_ID_TITLE);
		}
		break;
	case 1:
		//リトライボタン
		ImageManager::SetImageSize(hPictReStart_, XMFLOAT3(1.2f, 1.2f, 1.2f));
		ImageManager::ColorChange(hPictReStart_, XMFLOAT4(1.9f, 1.9f, 1.9f, 1.0f));

		ImageManager::SetImageSize(hPictRtnTitle_, XMFLOAT3(1, 1, 1));
		ImageManager::ColorChange(hPictRtnTitle_, XMFLOAT4(1, 1, 1, 1));
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		{
			((SceneManager*)parent->FindObject("SceneManager"))->ChangeScene(SCENE_ID_PLAY);
		}
		break;

	default:
		break;
	}
}

void Result::Release()
{
}
