#pragma once
#ifndef _SWORD_H_
#define _SWORD_H_

#include"animation.h"
#include"collisionBox.h"

//TO Do:��Sword����Characterʵ��һЩ�߼� ����ʹ�õ��ǵ�����
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
	//ʵ��һ��ƽ�����ƶ�? ���ԽԶԽ����

private:
	Vector2 position;
	Vector2 velocity;

	Animation animation;
	bool isValid = true;
	CollisionBox* collisionBox = nullptr;
};



#endif // !_SWORD_H_