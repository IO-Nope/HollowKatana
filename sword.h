#pragma once
#ifndef _SWORD_H_
#define _SWORD_H_

#include"animation.h"
#include"collisionBox.h"

//TO Do:让Sword集成Character实现一些逻辑 现在使用的是单独的
class Sword {
public:
	Sword(const Vector2& position, bool moveLeft);
	~Sword();

	void onUpdate(float dt);
	void onRender();
	
	bool checkValid() const
	{
		return this->isValid;
	}

private:
	const float SPEEDMOVE = 500.0f;
	//实现一个平滑的移动? 离得越远越慢？

private:
	Vector2 position;
	Vector2 velocity;

	Animation animation;
	bool isValid = true;
	CollisionBox* collisionBox = nullptr;
};



#endif // !_SWORD_H_