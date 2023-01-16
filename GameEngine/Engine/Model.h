#pragma once
#include<string>
#include"Fbx.h"
#include"Transform.h"
#include<vector>
namespace ModelManager
{
	int Load(std::string fileName);
	void SetTransform(int modelNum, Transform transform);
	void Draw(int modelNum, XMFLOAT2 uvScroll = {0,0});
	void DrawOutLine(int modelNum, XMFLOAT2 uvScroll = { 0,0 });
	void DrawToon(int modelNum, XMFLOAT2 uvScroll = { 0,0 });
	void RayCast(int modelNum, RayCastData& ray);
	void RayCast(RayCastData& ray);
	void SetModelNum(int modelNum);
	void SetShader(std::string shaderName);
	void DeleteModelNum(int modelNum);
	void Release();
};

