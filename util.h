#pragma once
#ifndef _UTIL_H
#define _UTIL_H
#include <graphics.h>
#include <thread>
#pragma comment( lib, "WINMM.lib")
#pragma comment( lib, "MSIMG32.lib")

struct Rect{
	int x,y; //左上角坐标
	int w,h; //宽高
};
/// <summary>
/// 实现图片的矩形裁剪,参数分别为图片指针,目标矩形,源矩形
/// </summary>
/// <param name="img"></param>
/// <param name="rectDst"></param>
/// <param name="rectSrc"></param>
inline void putImageEx(IMAGE* img,const Rect* rectDst,const Rect* rectSrc = nullptr){
	static BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()),
		rectDst->x,rectDst->y,rectDst->w,rectDst->h,
		GetImageHDC(img),
		rectSrc ? rectSrc->x:0, rectSrc ? rectSrc->y : 0,
		rectSrc ? rectSrc->w : img->getwidth(), rectSrc ? rectSrc->h : img->getheight(),
		bf);
}
inline void loadAudio(LPCTSTR path, LPCTSTR id) {
	static TCHAR strCmd[512];
	_stprintf_s(strCmd, _T("open %s alias %s"), path, id);
	mciSendString(strCmd, NULL, 0, NULL);
}
inline void playAudio(LPCTSTR id,bool isLoop =false) {
	static TCHAR strCmd[512];
	_stprintf_s(strCmd, _T("play %s %s from 0 notify"), id, isLoop ? _T("repeat") : _T(""));
	mciSendString(strCmd, NULL, 0, NULL);
}
inline void stopAudio(LPCTSTR id) {
	static TCHAR strCmd[512];
	_stprintf_s(strCmd, _T("stop %s"), id);
	mciSendString(strCmd, NULL, 0, NULL);
}
inline int rangeRand(int min, int max) {
	return rand() % (max - min + 1) + min;
}
inline bool isFileExists(LPCTSTR path) {
	DWORD fileAttr = GetFileAttributes(path);
	return (fileAttr != INVALID_FILE_ATTRIBUTES && !(fileAttr & FILE_ATTRIBUTE_DIRECTORY));
}
#endif // !_UTIL_H
