#pragma once
#include"Engine/GameObject.h"
#include"PaternState.h"

class Player;
class ObstacleSet : public GameObject
{
 private:
	 int setInterval_;
	 XMVECTOR vSet_;
	 PaternState<ObstacleSet>* pPattern_;
	 bool isSpawnGoal_;
	 Player* pPlayer_;
 public:
	 ObstacleSet(GameObject* parent);
	 ~ObstacleSet();
	 void Initialize() override;

	 void Update() override;

	 void Release() override;

	 void ChangeState(PaternState<ObstacleSet>* ptn);

	 XMVECTOR GetvSet() { return vSet_; }

	 void SetGoal();

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

	 class SetPattern3 : public PaternState<ObstacleSet>
	 {
	 private:
		 int settingTime_;
	 public:
		 static SetPattern3* GetInstance()
		 {
			 static SetPattern3* ins = nullptr;
			 if (ins == nullptr)
			 {
				 ins = new SetPattern3;
			 }

			 return ins;
		 }

		 void Init(ObstacleSet& ptn);
		 void Update(ObstacleSet& ptn);

	 };


	 class SetPatternFake : public PaternState<ObstacleSet>
	 {
	 private:
	 public:
		 static SetPatternFake* GetInstance()
		 {
			 static SetPatternFake* ins = nullptr;
			 if (ins == nullptr)
			 {
				 ins = new SetPatternFake;
			 }

			 return ins;
		 }

		 void Init(ObstacleSet& ptn);
		 void Update(ObstacleSet& ptn);

	 };

	 class SetGoal : public PaternState<ObstacleSet>
	 {
	 private:
		 int afterTime_;
		 int settingTime_;
		 int hPictBlack_;
	 public:
		 static SetGoal* GetInstance()
		 {
			 static SetGoal* ins = nullptr;
			 if (ins == nullptr)
			 {
				 ins = new SetGoal;
			 }

			 return ins;
		 }

		 void Init(ObstacleSet& ptn);
		 void Update(ObstacleSet& ptn);
	 };
};

