#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"character.h"
#include"vector2.h"

class Player : public Character
{
public:
	enum class AttackDir {
		Up,Down,Left,Right
	};

private:
	Timer timerRollCd;
	bool isRolling = false;
	bool isRollCdComp = true;

	Timer timerAttackCd;
	bool isAttacking = false;
	bool isAttackCdComp = true;

	bool isLeftKeyDown = false;
	bool isRightKeyDown = false;
	bool isJumpKeyDown = false;
	bool isRollKeyDown = false;
	bool isAttackKeyDown = false;


	Animation animationSlashUp;
	Animation animationSlashDown;
	Animation animationSlashLeft;
	Animation animationSlashRight;
	AttackDir attackDir = AttackDir::Right;
	Animation* currentSlashAnimation = nullptr;

	bool isJumpVfxVisible = false;
	Animation animationJumpVfx;

	bool isLandVfxVisible = false;
	Animation animationLandVfx;

private:
	const float CD_ROLL = 1.0f;
	const float CD_ATTACK = 0.5f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 780.0f;
	const float SPEED_ROLL = 800.0f;
	const float SPEED_ATTACK =500.0f;

public:
	Player();
	~Player();

	void onInput(const ExMessage& msg) override;
	void onUpdate(float dt) override;
	void onRender() override;

	void onHurt() override;

	void setRolling(bool flag) {
		isRolling = flag;
	}
	bool getRolling() {
		return isRolling;
	}
	/// <summary>
	/// 不考虑是否在地面上
	/// </summary>
	/// <returns></returns>
	bool canRoll() {
		return isRollCdComp&&!isRolling&&isRollKeyDown && isOnFloor();
	}

	void setAttacking(bool flag) {
		isAttacking = flag;
	}

	bool getAttacking() {
		return isAttacking;
	}
	bool canAttack() {
		return isAttackCdComp&&!isAttacking&&isAttackKeyDown;
	}

	bool canJump() {
		return isJumpKeyDown && isOnFloor();
	}
	/// <summary>
	/// 1为右，-1为左 ,0为不动
	/// </summary>
	/// <returns></returns>
	int getMoveAxis() {
		return isRightKeyDown - isLeftKeyDown;
	}
	AttackDir getAttackDir() {

		return attackDir;
	}
	//角色速度 特效播放
	void onJump();
	void onRoll();
	void onAttack();
	void onLand();
	void addAttackSpeed();
private:
	void updateAttackDir(int x,int y);
	void updateAttackDir();
};




#endif // !_PLAYER_H_