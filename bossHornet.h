#pragma once
#ifndef  _BOSSHORNET_H_
#define _BOSSHORNET_H_

#include"character.h"
#include"barb.h"
#include"sword.h"


class BossHornet : public Character {
	public:
	BossHornet();
	~BossHornet();


	void onUpdate(float dt) override;
	void onRender() override;

	void onHurt() override;

	void setFacingLeft(bool flag) {
		isFacingLeft = flag;
	}

	bool getFacingLeft() {
		return isFacingLeft;
	}

	void setDashingInAir(bool flag) {
		isDashingInAir = flag;
	}

	bool getDashingInAir() {
		return isDashingInAir;
	}

	void setDashingOnFloor(bool flag) {
		isDashingOnFloor = flag;
	}

	bool getDashingOnFloor() {
		return isDashingOnFloor;
	}

	void setThrowingSilk(bool flag) {
		isThrowingSilk = flag;
		collisionBoxSilk->setEnabled(flag);
	}

	bool getThrowingSilk() {
		return isThrowingSilk;
	}

	void throwBarb();
	void throwSword();

	void onDash();
	void onThrowSilk();

private:
	bool isThrowingSilk=false;
	bool isDashingInAir = false;
	bool isDashingOnFloor=false;

	Animation animationSilk;	AnimationGroup animationDashInAirVfx;
	AnimationGroup animationDashOnFloorVfx;
	Animation* currentDashAnimation = nullptr;

	std::vector<Barb*> barbs;
	std::vector<Sword*> swords;
	CollisionBox* collisionBoxSilk=nullptr;

};






#endif // ! _BOSSHORNET_H_
