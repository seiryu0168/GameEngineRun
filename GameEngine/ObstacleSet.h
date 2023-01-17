#pragma once
#include"Engine/GameObject.h"
#include"PaternState.h"
class ObstacleSet : public GameObject
{
 private:
	 int setInterval_;
	 XMVECTOR vSet_;
	 PaternState<ObstacleSet>* pPattern_;
 public:
	 ObstacleSet(GameObject* parent);
	 ~ObstacleSet();
	 void Initialize() override;

	 void Update() override;

	 void Release() override;

	 void ChangeState(PaternState<ObstacleSet>* ptn);

	 XMVECTOR GetvSet() { return vSet_; }

	 class SetPattern1: public PaternState<ObstacleSet>
	 {
	 private:
		 int settingTime_;
	 public:
		 static SetPattern1* GetInstance()
		 {
			 static SetPattern1* ins = nullptr;
			 if (ins == nullptr)
			 {
				 ins = new SetPattern1;
			 }

			 return ins;
		 }

		 void Init(ObstacleSet& ptn);
		 void Update(ObstacleSet& ptn);
	 };

	 class SetPattern2 : public PaternState<ObstacleSet>
	 {
	 private:
		 int settingTime_;
	 public:
		 static SetPattern2* GetInstance()
		 {
			 static SetPattern2* ins = nullptr;
			 if (ins == nullptr)
			 {
				 ins = new SetPattern2;
			 }

			 return ins;
		 }

		 void Init(ObstacleSet& ptn);
		 void Update(ObstacleSet& ptn);
	 };
};
