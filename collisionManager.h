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
	/// To Do :��Ҫ��д ���ڴ�����ײ
	/// 1.��layer
	/// 2.����״
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