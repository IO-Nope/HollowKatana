#pragma once
#ifndef _BARB_H_
#define _BARB_H_

#include"animation.h"
#include"collisionBox.h"

class Barb {
public:
	Barb();
	~Barb();

	void onUpdate(float dt);
	void onRender();

	void setPosition(const Vector2& position) {
		this->basePosition = position;
		this->currentPosition = position;
	};

	bool checkValid() const {
		return this->isValid;
	}
private:
	enum class Stage {
		Idle,
		Aim,
		Dash,
		Break
	};

private:
	const float SPEEDDASH = 1500.0f;

private:
	Timer timerIdle;
	Timer timerAim;
	int diffPeriod = 0;
	bool isValid = true;
	float totalDeltaTime = 0;

	Vector2 velocity;
	Vector2 basePosition;
	Vector2 currentPosition;

	Animation animationLoose;
	Animation animationBreak;
	Animation* currentAnimation = nullptr;

	Stage stage = Stage::Idle;
	CollisionBox* collisionBox = nullptr;

private:
	void onBreak();
};

#endif // !_BARB_H_
