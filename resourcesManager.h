#pragma once
#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include"atlas.h"

#include<unordered_map>
#include<string>
#include<graphics.h>
#include<vector>

class ResourcesManager
{
public:
	static ResourcesManager* instance();

	void load();
	void loadAuto();
	Atlas* findAtlas(const std::string& id) const;
	IMAGE* findImage(const std::string& id) const;

private:
	static ResourcesManager* manager;

	std::unordered_map<std::string, Atlas*> atlasPool;
	std::unordered_map<std::string, IMAGE*> imagePool;

private:
	ResourcesManager();
	~ResourcesManager();

	void flipImage(IMAGE* srcImage ,IMAGE* dstImage,int numH = 1);
	void flipImage(const std::string& srcId,const std::string& dstId, int numH = 1);
	void flipAtlas(const std::string& srcId,const std::string& dstId);
};








#endif // !_RESOURCEMANAGER_H