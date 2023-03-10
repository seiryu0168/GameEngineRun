#pragma once
#include"Engine/Direct3D.h"
#include"Engine/Transform.h"
#include<vector>
#include<string>

namespace ImageManager
{
	/// <summary>
	/// 画像ロード
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>画像番号</returns>
	int Load(std::string fileName,const Transform* transform = nullptr);
	
	/// <summary>
	/// 画像描画
	/// </summary>
	/// <param name="imageHandle">画像番号</param>
	void Draw(int imgHandle);
	void DrawSub();
	
	/// <summary>
	/// 画像の切り抜き範囲リセット
	/// </summary>
	/// <param name="imageHandle">画像番号</param>
	void ResetRect(int imgHandle);
	
	/// <summary>
	/// 画像の切り抜き範囲設定
	/// </summary>
	/// <param name="imageHandle">画像番号</param>
	/// <param name="top">上</param>
	/// <param name="bottom">下</param>
	/// <param name="left">左</param>
	/// <param name="right">右</param>
	void SetRect(int imgHandle,int top,int bottom,int left,int right);
	
	/// <summary>
	/// アルファ値の設定
	/// </summary>
	/// <param name="imghandle">画像番号</param>
	/// <param name="alpha">アルファ値</param>
	void  SetAlpha(int imghandle,float alpha);
	
	/// <summary>
	/// アルファ値取得
	/// </summary>
	/// <param name="imgHandle">画像番号</param>
	/// <returns>アルファ値</returns>
	float GetAlpha(int imgHandle);

	/// <summary>
	/// 画像の位置設定
	/// </summary>
	/// <param name="imgHandle">画像番号</param>
	/// <param name="pos">画像の位置</param>
	void  SetImagePos(int imgHandle,XMFLOAT3 pos);

	/// <summary>
	/// 画像サイズ設定
	/// </summary>
	/// <param name="imgHandle">画像番号</param>
	/// <param name="size">サイズ</param>
	void  SetImageSize(int imgHandle, XMFLOAT3 size);

	/// <summary>
	/// Transgorm設定
	/// </summary>
	/// <param name="transform">Transform</param>
	void SetTransform(int imgHandle,Transform& transform);

	/// <summary>
	/// 色を変える
	/// </summary>
	/// <param name="color">RGBAの値</param>
	void ColorChange(int imgHandle,XMFLOAT4 color);

	XMFLOAT3 GetImageSize(int imgHandle);

	void Release(int imgHandle);
	void AllRelease();
};

