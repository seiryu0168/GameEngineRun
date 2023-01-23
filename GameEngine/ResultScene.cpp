#include "ResultScene.h"
#include"ImageManager.h"
#include"InterSceneData.h"
#include"EngineTime.h"


ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene"),
	hPict_(-1),
	time_(0),
	score_(0),
	rslt_(nullptr)
{
	for (int i = 0; i < 3; i++)
	{
		hPictScore_[i] = -1;
	}

}

ResultScene::~ResultScene()
{
	Release();
}

void ResultScene::Initialize()
{
	rslt_ = new Result();
	rslt_->Init();
	for (int i = 0; i < 3; i++)
	{
		hPictScore_[i] = ImageManager::Load("Assets\\Star.png");
		assert(hPictScore_ >= 0);
		ImageManager::SetRect(hPictScore_[i], 0, 512, 0, 0);
		ImageManager::SetImageSize(hPictScore_[i], XMFLOAT3(0.4f,0.4f,0.4f));
	}
	ImageManager::SetImagePos(hPictScore_[0], XMFLOAT3(-512, 0, 0));
	ImageManager::SetImagePos(hPictScore_[1], XMFLOAT3(0, 0, 0));
	ImageManager::SetImagePos(hPictScore_[2], XMFLOAT3(512, 0, 0));
	hPict_ = ImageManager::Load("Assets\\ResultImage.png");
	assert(hPict_ >= 0);
}

void ResultScene::Update()
{
	if (EngineTime::GetFrame() > 60 && time_ < 180-(180-InterSceneData::GetData("time")/10))
	{
		time_++;
		ImageManager::SetRect(hPictScore_[score_],0,512,0,((float)time_ - (float)(60*score_))/(60.0f/512.0f));
		if (time_ % 60 == 0)
		{
			score_++;
		}
	}

	if(EngineTime::GetFrame()>=40)
	{
		rslt_->Update(this);
	}


	
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
	SAFE_DELETE(rslt_);
}
