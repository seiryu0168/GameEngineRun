#include "ImageManager.h"
#include"Engine/Sprite.h"

namespace ImageManager
{
	struct imageData
	{
		std::string fileName_;
		Sprite* pSprite_;
		RECT rect_;
		float alpha_;
		XMFLOAT4 changeColor_;
		Transform transform_;
		imageData()
		{
			fileName_ = "";
			pSprite_ = nullptr;
			alpha_ = 1.0f;
			changeColor_ = { 1,1,1,1 };
		}
	};

	std::vector<imageData*> imageList_;
}
int ImageManager::Load(std::string fileName,const Transform* transform)
{
	imageData* pImage = new imageData;
	pImage->fileName_ = fileName;

	//同じ名前のファイルがあったらそのアドレスを渡す
	for (int i = 0; i < imageList_.size(); i++)
	{
		if (imageList_[i]->fileName_ == fileName)
		{
			pImage->pSprite_ = imageList_[i]->pSprite_;
			break;
		}
	}

	//見つからなかったら
	if (pImage->pSprite_ == nullptr)
	{
		//新しくファイルを開く
		pImage->pSprite_ = new Sprite;
		if (FAILED(pImage->pSprite_->Load(fileName)))
		{
			//失敗したら消して-1を返す
			SAFE_DELETE(pImage->pSprite_);
			SAFE_DELETE(pImage);
			return -1;
		}
	}
	if (transform != nullptr)
	{
		pImage->transform_ = (Transform&)transform;
	}
	//リストに追加
	imageList_.push_back(pImage);

	int rtn = imageList_.size() - 1;
	
	//切り抜き範囲リセット
	ResetRect(rtn);

	return rtn;
	
}

void ImageManager::Draw(int imgHandle)
{
	imageList_[imgHandle]->pSprite_->Draw(imageList_[imgHandle]->transform_, imageList_[imgHandle]->rect_, imageList_[imgHandle]->alpha_, imageList_[imgHandle]->changeColor_);
}

void ImageManager::DrawSub()
{
	for (int i = imageList_.size()-1; i >-1 ; i--)
	{
		Draw(i);
	}
}

void ImageManager::ResetRect(int imgHandle)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return;
	}
	XMFLOAT3 size = imageList_[imgHandle]->pSprite_->GetSize();

	imageList_[imgHandle]->rect_.top = 0;
	imageList_[imgHandle]->rect_.bottom = (long)size.y;
	imageList_[imgHandle]->rect_.left = 0;
	imageList_[imgHandle]->rect_.right = (long)size.x;
}

void ImageManager::SetRect(int imgHandle, int top, int bottom, int left, int right)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return;
	}

	imageList_[imgHandle]->rect_.top    = top;
	imageList_[imgHandle]->rect_.bottom = bottom;
	imageList_[imgHandle]->rect_.left   = left;
	imageList_[imgHandle]->rect_.right  = right;
}

void ImageManager::SetAlpha(int imgHandle,float alpha)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return;
	}

	imageList_[imgHandle]->alpha_ = alpha/255.0f;
}

float ImageManager::GetAlpha(int imgHandle)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return 0;
	}
	return imageList_[imgHandle]->alpha_;
}

void ImageManager::SetImagePos(int imgHandle, XMFLOAT3 pos)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return;
	}
	pos.z = 0;
	pos.x = pos.x / Direct3D::GetScreenWidth();
	pos.y = pos.y / Direct3D::GetScreenHeight();
	imageList_[imgHandle]->transform_.position_ = pos;
}

void ImageManager::SetImageSize(int imgHandle, XMFLOAT3 size)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return;
	}

	size.z = 0;
	imageList_[imgHandle]->transform_.scale_ = size;
}

void ImageManager::SetTransform(int imgHandle, Transform& transform)
{
	if (imgHandle < 0 || imgHandle >= imageList_.size())
	{
		return;
	}

	imageList_[imgHandle]->transform_ = transform;
}

void ImageManager::ColorChange(int imgHandle,XMFLOAT4 color)
{
	imageList_[imgHandle]->changeColor_ = color;
}

XMFLOAT3 ImageManager::GetImageSize(int imgHandle)
{
	if (imgHandle < 0 || imageList_.size() < imgHandle)
	{
		return XMFLOAT3(-9999,-9999,-9999);
	}
	return imageList_[imgHandle]->pSprite_->GetSize();
}

void ImageManager::Release(int imgHandle)
{
	if (imgHandle < 0 || imgHandle > imageList_.size())
	{
		return;
	}

	bool isRef = false;
	//同じアドレスを参照してるやつが複数あるかどうか調べる
	for (int i = 0; i < imageList_.size(); i++)
	{
		if (imageList_[i] != nullptr && i != imgHandle && imageList_[imgHandle]->pSprite_ == imageList_[i]->pSprite_)
		{
			isRef = true;
			break;
		}
	}

	if (isRef == false)
	{
		SAFE_DELETE(imageList_[imgHandle]->pSprite_);
	}

	SAFE_DELETE(imageList_[imgHandle]);
}

void ImageManager::AllRelease()
{
	for (int i = 0; i < imageList_.size(); i++)
	{
		Release(i);
	}
	imageList_.clear();
}
