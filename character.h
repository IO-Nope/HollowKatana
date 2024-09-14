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
	Vector2 velocity; // 速度
	float logicHeight = 0;// 逻辑高度
	bool isFacingLeft = true;
	StateMachine stateMachine;
	bool isInvulnerable = false; // 无敌状态
	Timer timerInvulnerableBlink; // 无敌状态闪烁计时器
	Timer timerInvulnerableStatus; // 无敌状态持续时间计时器
	bool isBlinkInvisible = false; //当前是否处于闪烁不可见帧
	CollisionBox* hitBox = nullptr;//攻击碰撞盒
	CollisionBox* hurtBox = nullptr;//受伤碰撞盒
	AnimationGroup* currentAnimation=nullptr; //当前动画
	std::unordered_map<std::string, AnimationGroup> animationPool;//动画池

};

#endif // !_CHARACTER_H_