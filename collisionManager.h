#pragma once
#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H
#include"collisionBox.h"

#include<vector>

class CollisionManager {
public:
	static CollisionManager* instance();

	CollisionBox* createBox();
	void destroyBox(CollisionBox* collisionBox);
	/// <summary>
	/// To Do :需要重写 用于处理碰撞
	/// 1.多layer
	/// 2.多形状
	/// </summary>
	void processCollide();
	void onDebugRender();
private:
	static CollisionManager* manager;

	std::vector<CollisionBox*> collisionBoxList;

	private:
		CollisionManager();
		~CollisionManager();
};


#endif // !_COLLISION_MANAGER_H