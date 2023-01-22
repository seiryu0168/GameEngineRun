#pragma once
#include<string>
namespace InterSceneData
{
	void AddData(std::string dataName,int iPara = NULL, float fPara = NULL, bool bPara=NULL);
	int GetData(std::string dataName);
	void DeleteData(std::string dataName);
}

