#pragma once
#include"Engine/GameObject.h"
template<class C>
class PaternState
{
public:
	GameObject* pSetter_;
	virtual ~PaternState() {};
	virtual void Init(C& pattern) {};
	virtual void Update(C& pattern) {};
};