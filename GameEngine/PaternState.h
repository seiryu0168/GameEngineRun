#pragma once
template<class C>
class PaternState
{
public:
	virtual ~PaternState() {};
	virtual void Init(C& pattern) {};
	virtual void Update(C& pattern) {};
};

