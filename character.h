#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include"stateMachine.h"
#include"animation.h"
#include"collisionBox.h"
#include"vector2.h"

#include<graphics.h>
#include<string>
#include<unordered_map>

class Character {
public:
	Character();
	~Character();
	void decreaseHp(int val);
	int getFloorY() const {
		return FLOORY;
	}
	int getHp() const{
		return hp;
	}
	void setPosition(const Vector2& position) {
		this->position = position;
	}
	Vector2 getPosition() const {
		return position;
	}

	void setVelocity(const Vector2& velocity) {
		this->velocity = velocity;
	}
	Vector2 getVelocity() const {
		return velocity;
	}
	Vector2 getLogicCenter() const {
		return Vector2(position.x, position.y - logicHeight/2);
	}
	void setGravityEnable(bool flag) {
		enableGravity = flag;
	}
	CollisionBox* getHitBox() {
		return hitBox;
	}
	CollisionBox* getHurtBox() {
		return hurtBox;
	}

	bool isOnFloor() {
		return position.y >= FLOORY;
	}
	void makeInvulnerable() {
		isInvulnerable= true;
		timerInvulnerableStatus.restart();
	}

	virtual void onInput(const ExMessage& msg);
	virtual void onUpdate(float dt);
	virtual void onRender() ;

	virtual void onHurt();

	void switchState(const std::string& id);
	void setAnimation(const std::string& id);

protected:
	struct AnimationGroup {
		Animation left;
		Animation right;
	};
protected:
	const float FLOORY = 620;
	const float GRAVITY = 980*2;

protected:
	int hp = 10;
	bool enableGravity = true;
	Vector2 position;
	Vector2 velocity; // �ٶ�
	float logicHeight = 0;// �߼��߶�
	bool isFacingLeft = true;
	StateMachine stateMachine;
	bool isInvulnerable = false; // �޵�״̬
	Timer timerInvulnerableBlink; // �޵�״̬��˸��ʱ��
	Timer timerInvulnerableStatus; // �޵�״̬����ʱ���ʱ��
	bool isBlinkInvisible = false; //��ǰ�Ƿ�����˸���ɼ�֡
	CollisionBox* hitBox = nullptr;//������ײ��
	CollisionBox* hurtBox = nullptr;//������ײ��
	AnimationGroup* currentAnimation=nullptr; //��ǰ����
	std::unordered_map<std::string, AnimationGroup> animationPool;//������

};

#endif // !_CHARACTER_H_