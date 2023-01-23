#include "Timer.h"
#include"ImageManager.h"
#include"EngineTime.h"
Timer::Timer(GameObject* parent)
	:GameObject(parent,"Timer"),
	prevTime_(0)
{
	for (int i = 0; i < 20; i++)
	{
		hPictNum_[i] = -1;
	}
}

Timer::~Timer()
{
}

void Timer::Initialize()
{

	for (int i = 0; i < 20; i++)
	{
		hPictNum_[i] = ImageManager::Load("Assets\\TextImage.png");
		int offSet = (ImageManager::GetImageSize(hPictNum_[i]).x / 10.0f) * i;
		ImageManager::SetRect(hPictNum_[i], 0, 128, offSet % 512, 51);
		ImageManager::SetImagePos(hPictNum_[i], XMFLOAT3(0, 1900, 0));
	}
}

void Timer::Update()
{
	time_ = EngineTime::GetFrame() / 60;

	if (time_ < 31)
	{
		ImageManager::SetImagePos(hPictNum_[time_ % 10], XMFLOAT3(-1300, 900, 0));
		ImageManager::SetImagePos(hPictNum_[10 + (time_ / 10)], XMFLOAT3(-1400, 900, 0));
		if (EngineTime::GetFrame() % 60 == 0)
		{
			ImageManager::SetImagePos(hPictNum_[prevTime_ % 10], XMFLOAT3(0, 1900, 0));
			ImageManager::SetImagePos(hPictNum_[10 + (prevTime_ / 10)], XMFLOAT3(0, 1900, 0));
			prevTime_ = time_;
		}

	}

}

void Timer::Draw()
{
}

void Timer::Release()
{
}
