#pragma once

namespace EngineTime
{
//public:
//	EngineTime();
//	~EngineTime();
	void Initialize();
	unsigned long GetTime();
	float GetDeltaTime();
	float GetTimeScale();
	unsigned long GetFrame();
	void SetTimeScale(float scale);
	void SetTime();
	void Update();
	void ResetFrame();
};
