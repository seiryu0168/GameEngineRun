#include "InterSceneData.h"
#include"Engine/SAFE_DELETE_RELEASE.h"
#include<list>
namespace InterSceneData
{
	struct Data
	{
		std::string dataName_;
		int iData_;
		float fData_;
		bool bData_;

	};
	std::list<Data*> dataList_;
	
	void AddData(std::string dataName,int iPara, float fPara, bool bPara)
	{
		for (auto itr = dataList_.begin(); itr != dataList_.end(); itr++)
		{
			if ((*itr)->dataName_ == dataName)
			{
				return;
			}
		}
		bool isAllDataNull = true;
		Data* pData = new Data;
		pData->dataName_ = dataName;
		if (iPara != NULL)
		{
			pData->iData_ = iPara;
			isAllDataNull = false;
		}
		if (fPara != NULL)
		{
			pData->fData_ = fPara;
			isAllDataNull = false;
		}
		if (bPara != NULL)
		{
			pData->bData_ = bPara;
			isAllDataNull = false;
		}

		if (isAllDataNull == false)
		{
			dataList_.push_back(pData);
		}
	}

	int GetData(std::string dataName)
	{
		for (auto itr = dataList_.begin(); itr != dataList_.end(); itr++)
		{
			if ((*itr)->dataName_ == dataName)
			{
				return (*itr)->iData_;
			}
		}
		return NULL;
	}

	void DeleteData(std::string dataName)
	{
		for (auto itr = dataList_.begin(); itr != dataList_.end(); itr++)
		{
			if ((*itr)->dataName_ == dataName)
			{
				SAFE_DELETE(*itr);
				itr = dataList_.erase(itr);
				return;

			}
		}
	}

}
