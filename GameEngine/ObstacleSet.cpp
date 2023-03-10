#include "ObstacleSet.h"
#include"Engine/Model.h"
#include"Engine/SceneManager.h"
#include"InterSceneData.h"
#include"ImageManager.h"
#include"Stage1.h"
#include"EngineTime.h"
#include"NormalBlock.h"
#include"Recovery.h"
#include"Goal.h"
#include"Engine/Input.h"
#include"Player.h"
#include<iostream>
namespace
{
	static const XMVECTOR ROTATE_AXIS  = XMVectorSet(0, 0, 1, 0);
	static const XMFLOAT3 RAYCAST_DIR  = XMFLOAT3(0, -1, 0);
	static const int	  SET_INTERVAL = 240;
	static const float    MAX_RUN_TIME = 30.0f;

}
ObstacleSet::ObstacleSet(GameObject* parent)
	:GameObject(parent,"ObstacleSet"),
	isSpawnGoal_(false)
{

}

ObstacleSet::~ObstacleSet()
{
}

void ObstacleSet::Initialize()
{
	pPlayer_ = (Player*)FindObject("Player");
	srand((unsigned int)time(NULL));
	RayCastData ray;
	ray.dir = RAYCAST_DIR;
	ray.start = transform_.position_;
	ModelManager::RayCast(((Stage1*)FindObject("Stage1"))->GetModelHandle(),ray);

	vSet_ = XMVector3Normalize((ray.hitPos-XMLoadFloat3(&transform_.position_))) * (ray.dist-1.0f);
	ChangeState(SetPattern1::GetInstance());

	NormalBlock* pNormal = nullptr;
	XMFLOAT3 initPos = {};
	XMFLOAT3 setPos = transform_.position_;
	setPos.z = 200;
	XMVECTOR qRotate = XMVectorSet(0, 0, 0, 0);

	//最初だけ20個障害物出しとく
	for (int i = 0; i < 20; i++)
	{
		pNormal = Instantiate<NormalBlock>(GetParent());
		qRotate= XMQuaternionRotationAxis(ROTATE_AXIS, (float)((float)(rand() % 630) / 100.0f));
		vSet_ = XMVector3Rotate(vSet_, qRotate);
		XMStoreFloat3(&initPos, XMLoadFloat3(&setPos) + vSet_);
		pNormal->SetPosition(initPos);
		setPos.z+=20;
	}
	transform_.position_.z = 600;
}

void ObstacleSet::Update()
{
	if (EngineTime::GetFrame() / 60.0f >= MAX_RUN_TIME - 4.0f&&isSpawnGoal_==false)
	{
		GameObject* obj = Instantiate<Goal>(GetParent());
		obj->SetPosition(GetPosition());
		ChangeState(SetPatternFake::GetInstance());
		isSpawnGoal_ = true;
	}
	if (EngineTime::GetFrame()/60.0f >= MAX_RUN_TIME|| pPlayer_->GetHP() == 0)
	{
		ChangeState(SetGoal::GetInstance());
	}

	pPattern_->Update(*this);
	
}

void ObstacleSet::Release()
{
}

void ObstacleSet::ChangeState(PaternState<ObstacleSet>* ptn)
{
	if (pPattern_ != ptn)
	{
		pPattern_ = ptn;
		pPattern_->Init(*this);
	}
}

void ObstacleSet::SetPattern1::Init(ObstacleSet& ptn)
{
	settingTime_ = 0;
}

void ObstacleSet::SetPattern1::Update(ObstacleSet& ptn)
{
	settingTime_++;

	if (settingTime_%30-EngineTime::GetFrame()/60==0)
	{
		XMVECTOR qRotate;
		XMVECTOR setVec;

	    //回転角(ラジアン)を求める
		float angle = (M_PI / 180.0f) * (rand()/360);
		qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, angle);
		setVec = XMVector3Rotate(ptn.GetvSet(), qRotate);
		GameObject* obj;

		//1/4で回復が出てくる
		if ((rand() % 3) == 1)
		{
			obj = ptn.Instantiate<Recovery>(ptn.GetParent());
			obj->SetRotateZ(angle*(180/M_PI));
		}
		//4/3で障害物が出る
		else
		{
			obj = ptn.Instantiate<NormalBlock>(ptn.GetParent());
		}

		//障害物の出る位置を設定
		XMFLOAT3 pos;
		XMFLOAT3 setterPos = ptn.GetPosition();
		XMStoreFloat3(&pos, setVec);
		XMStoreFloat3(&pos, XMLoadFloat3(&setterPos)+setVec);
		obj->SetPosition(pos);
	}
	if (settingTime_ == SET_INTERVAL)
	{
		ptn.ChangeState(SetPattern2::GetInstance());
	}
}

void ObstacleSet::SetPattern2::Init(ObstacleSet& ptn)
{
	settingTime_ = 0;
}

void ObstacleSet::SetPattern2::Update(ObstacleSet& ptn)
{
	settingTime_++;
	if (settingTime_ %90-EngineTime::GetFrame()/30 == 0)
	{
		XMVECTOR qRotate;
		XMVECTOR setVec;
		
		//回転オフセットを設定
		float firstRotate = (M_PI/180.0f)*(rand()%360);
		
		//階段状に障害物を置く
		for (int i = 0; i < 5; i++)
		{
			//オフセットを基準に45度ずつ角度を変化させる
			qRotate= XMQuaternionRotationAxis(ROTATE_AXIS, firstRotate+(M_PI/180.0f)*45.0f*i);
			setVec = XMVector3Rotate(ptn.GetvSet(), qRotate);
			
			//障害物設置
			GameObject* obj = ptn.Instantiate<NormalBlock>(ptn.GetParent());
			XMFLOAT3 pos;
			XMFLOAT3 setterPos = ptn.GetPosition();
			XMStoreFloat3(&pos, setVec);
			XMStoreFloat3(&pos, XMLoadFloat3(&setterPos) + setVec);

			//位置を変える
			pos.z += 10 * i;
			obj->SetPosition(pos);
		}
	}

	if (settingTime_ == SET_INTERVAL)
	{
		ptn.ChangeState(SetPattern3::GetInstance());
	}
}

void ObstacleSet::SetGoal::Init(ObstacleSet& ptn)
{
	//ゲーム終了時点の時間を保存
	InterSceneData::AddData("time", (int)EngineTime::GetFrame());
	
	//各初期化
	settingTime_ = 0;
	afterTime_ = 0;
	
	//画像ロード,アルファ値セット
	hPictBlack_ = ImageManager::Load("Assets\\BlackOut.png");
	ImageManager::SetAlpha(hPictBlack_,0);
}

void ObstacleSet::SetGoal::Update(ObstacleSet& ptn)
{
	//画面を暗くしていく
	settingTime_++;	
	ImageManager::SetAlpha(hPictBlack_,255.0f*((float)settingTime_/150.0f));
	
	//シーン遷移
	if (settingTime_ >= 150)
	{
		((SceneManager*)ptn.FindObject("SceneManager"))->ChangeScene(SCENE_ID_RESULT);
	}
}

void ObstacleSet::SetPatternFake::Init(ObstacleSet& ptn)
{
}

void ObstacleSet::SetPatternFake::Update(ObstacleSet& ptn)
{
}

void ObstacleSet::SetPattern3::Init(ObstacleSet& ptn)
{
	settingTime_ = 0;
}

void ObstacleSet::SetPattern3::Update(ObstacleSet& ptn)
{
	//時間の補正をかけつつ50フレームごとに障害物を設置
	settingTime_++;
	if (settingTime_ % 50-EngineTime::GetFrame()/60 == 0)
	{
		XMVECTOR qRotate;
		XMVECTOR setVec;

		//回転のオフセットを設定
		float firstRotate = (M_PI/180.0f)*(rand() % 360);
		for (int i = 0; i < 4; i++)
		{
			//回転クオータニオンを求める(ランダム)
			qRotate = XMQuaternionRotationAxis(ROTATE_AXIS, firstRotate+((float)M_PI/180*90.0f*i));
			setVec = XMVector3Rotate(ptn.GetvSet(), qRotate);
			
			//障害物設置
			GameObject* obj = ptn.Instantiate<NormalBlock>(ptn.GetParent());
			XMFLOAT3 pos;
			XMFLOAT3 setterPos = ptn.GetPosition();
			XMStoreFloat3(&pos, setVec);
			XMStoreFloat3(&pos, XMLoadFloat3(&setterPos) + setVec);
			obj->SetPosition(pos);

			obj = ptn.Instantiate<NormalBlock>(ptn.GetParent());
			setterPos = ptn.GetPosition();
			XMStoreFloat3(&pos, XMLoadFloat3(&setterPos) + setVec*0.5f);
			obj->SetPosition(pos);
		}
	}

	//240フレームたったらステータスを変える
	if (settingTime_ == SET_INTERVAL)
	{

		ptn.ChangeState(SetPattern1::GetInstance());
	}
}
