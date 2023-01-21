#include "ResultScene.h"
#include"ImageManager.h"


ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene"),
	hPictScore_(-1),
	hPictStar_(-1),
	hPictScoreBarBase_(-1),
	hPictScoreBar_(-1),
	time_(0)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	hPictScore_ = ImageManager::Load("Assets\\ResultImage.jpg");
	Transform t = GetParent()->GetTransform();
	hPictScoreBar_ = ImageManager::Load("Assets\\ScoreBarBaseTest.png");
	//hPictScoreBarBase_ = ImageManager::Load("Assets\\ScoreBarFrame.png");
}

void ResultScene::Update()
{
	time_++;
	ImageManager::SetRect(hPictScoreBar_, 0, 200, 0, time_);
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
