#pragma once
#ifndef _ATLAS_H
#define _ATLAS_H
#include"util.h"
#include<vector>
#include<graphics.h>

class Atlas
{
private:
	std::vector<IMAGE> imageList;
public:
	Atlas() = default;
	~Atlas() = default;

	void load(LPCTSTR pathTemp, int num) {
		imageList.clear();
		imageList.resize(num);
		TCHAR pathFile[256];
		for(int i = 1; i <= num;i++){
			_stprintf_s(pathFile, pathTemp, i);
			if(!isFileExists(pathFile))
				throw pathFile;
			loadimage(&imageList[i-1], pathFile);
			//printf("load image: %ws size: %d %d", pathFile, imageList[i-1].getheight(), imageList[i-1].getwidth());
		}
	}
	void clear() {
		imageList.clear();
	}
	int getSize() {
		return imageList.size();
	}
	IMAGE& operator[](int index) {
		if (index < 0 || index >= imageList.size())
			throw "index out of range";
		return imageList[index];
	}
	IMAGE* getImage(int index) {
		if (index < 0 || index >= imageList.size())
			return nullptr;
		//printf("index:%d\n", index);
		//printf("size:%d %d\n", imageList[index].getheight(),imageList[index].getwidth());
		return &imageList[index];
	}
	void addImage(IMAGE image) {
		imageList.push_back(image);
	}
};

#endif // !_ATLAS_H