#include "bossHornetStateNodes.h"
#include "characterManager.h"
#include "bossHornet.h"
#pragma region BossHornetAimState

BossHornetAimState::BossHornetAimState()
{
	timer.setOneShot(true);
	timer.setWaitTime(0.5f);
	timer.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		bossHornet->setGravityEnable(true);
		bossHornet->switchState("dashInAir");
	});
}
void BossHornetAimState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("aim");
	bossHornet->setGravityEnable(false);
	bossHornet->setVelocity(Vector2(0, 0));
	timer.restart();
}
void BossHornetAimState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timer.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
}
#pragma endregion
#pragma region BossHornetDashInAirState
void BossHornetDashInAirState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	const Character* player = CharacterManager::instance()->getCharacter("player");
	if (!player)
	{
		return;
	}
	Vector2 direction = player->getPosition() - bossHornet->getPosition(); 
	direction.y = player->getFloorY()-bossHornet->getPosition().y;//防止黄蜂女卡墙边
	bossHornet->setAnimation("dashInAir");
	bossHornet->setVelocity(direction.normalize()* SPEED_DASH);
	bossHornet->setDashingInAir(true);
	bossHornet->setGravityEnable(false);
	bossHornet->onDash();

	playAudio(_T("hornetDash"), false);
}
void BossHornetDashInAirState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
	else if(bossHornet->isOnFloor())
	{
		bossHornet->switchState("idle");
	}
}

void BossHornetDashInAirState::onExit()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setGravityEnable(true);
	bossHornet->setDashingInAir(false);
}
#pragma endregion
#pragma region BossHornetDashOnFloorState
BossHornetDashOnFloorState::BossHornetDashOnFloorState()
{
	timer.setOneShot(true);
	timer.setWaitTime(0.5f);
	timer.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		bossHornet->setDashingOnFloor(false);
	});
}
void BossHornetDashOnFloorState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	const Character* player = CharacterManager::instance()->getCharacter("player");
	if (!player)
	{
		return;
	}
	Vector2 direction = player->getPosition() - bossHornet->getPosition();
	bossHornet->setAnimation("dashOnFloor");
	bossHornet->setVelocity(Vector2(bossHornet->getFacingLeft()? -SPEED_DASH : SPEED_DASH,0));
	bossHornet->setDashingOnFloor(true);
	bossHornet->onDash();
	timer.restart();

	playAudio(_T("hornetDash"), false);
}
void BossHornetDashOnFloorState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timer.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
	else if(!bossHornet->getDashingOnFloor())
	{
		bossHornet->switchState("idle");
	}
}
#pragma endregion
#pragma region BossHornetDeadState
void BossHornetDeadState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setVelocity(Vector2(0, 0));
	bossHornet->setAnimation("idle");
	bossHornet->getHitBox()->setEnabled(false);
	MessageBox(NULL, _T("很好,这样能行."), _T("挑战成功!"), MB_OK);
}
#pragma endregion
#pragma region BossHornetFallState
void BossHornetFallState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("fall");
}
void BossHornetFallState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
	else if(bossHornet->isOnFloor())
	{
		bossHornet->switchState("idle");
	}
}
#pragma endregion
#pragma region BossHornetIdleState
BossHornetIdleState::BossHornetIdleState()
{
	timer.setOneShot(true);
	//timer.setWaitTime(1.0f);
	timer.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");

		int randNum = rangeRand(0,9);
		if (bossHornet->getHp() > 5) {
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
				if (!bossHornet->isOnFloor()) {
					bossHornet->switchState("fall");
				}
				else
					bossHornet->switchState("jump");   //30%概率跳跃
				break;
			case 3:
			case 4:
				if (!bossHornet->isOnFloor()) {
					bossHornet->switchState("fall");
				}
				else
					bossHornet->switchState("run");   //20%概率跑动
				break;
			case 5:
			case 6:
			case 7:
				bossHornet->switchState("squat");   //30%概率
				break;
			case 8:
				bossHornet->switchState("throwSilk");   //10%概率
				break;
			case 9:
				bossHornet->switchState("throwSword");   //10%概率
				break;
			}
		}
		else {
			switch (randNum)
			{
			case 0:
			case 1:
				if (!bossHornet->isOnFloor()) {
					bossHornet->switchState("fall");
				}
				else
					bossHornet->switchState("jump");   //20%概率跳跃
				break;
			case 2:
				if (!bossHornet->isOnFloor()) {
					bossHornet->switchState("fall");
				}
				else
					bossHornet->switchState("run");   //10%概率跑动
				break;
			case 3:
				bossHornet->switchState("squat");   //10%概率
				break;
			case 4:
			case 5:
			case 6:
				bossHornet->switchState("throwSword");   //30%概率
				break;
			case 7:
				bossHornet->switchState("throwSilk");   //10%概率
				break;
			case 8:
			case 9:
				bossHornet->switchState("throwBarb");   //20%概率
				break;
			}
		}
	});
}
void BossHornetIdleState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("idle");
	bossHornet->setVelocity(Vector2(0, 0));
	float waitTime=rangeRand(0,2);
	if(bossHornet->getHp()<5)
	{
		waitTime = rangeRand(0, 1);
	}
	waitTime *= 0.25f;

	timer.setWaitTime(waitTime);
	timer.restart();
}
void BossHornetIdleState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timer.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
	else if (bossHornet->getVelocity().y>0)
	{
		bossHornet->switchState("fall");
	}
}
void BossHornetIdleState::onExit()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setFacingLeft(bossHornet->getPosition().x > CharacterManager::instance()->getCharacter("player")->getPosition().x);
}
#pragma endregion
#pragma region BossHornetJumpState
//TO DO:让黄蜂女定位玩家
void BossHornetJumpState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("jump");
	bossHornet->setVelocity(Vector2(0, -SPEED_JUMP));
	//bossHornet->setGravityEnable(true);
}
void BossHornetJumpState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	if (bossHornet->getHp() <= 0)
	{
		bossHornet->switchState("dead");
	}
	else if (bossHornet->getVelocity().y > 0)
	{
		int randNum = rangeRand(0, 9);
		if (bossHornet->getHp() > 5) {
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				bossHornet->switchState("aim");
				break;
			case 5:
			case 6:
			case 7:
				bossHornet->switchState("fall");
				break;
			case 8:
			case 9:
				bossHornet->switchState("throwSilk");
				break;
			}
		}
		else {
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				bossHornet->switchState("throwSilk");
				break;
			case 5:
			case 6:
			case 7:
				bossHornet->switchState("fall");
				break;
			case 8:
			case 9:
				bossHornet->switchState("aim");
				break;
			}

		}
	}
}
#pragma endregion
#pragma region BossHornetRunState
void BossHornetRunState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("run");

	playAudio(_T("hornetRun"), true);
}

void BossHornetRunState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	const Vector2& playerPos = CharacterManager::instance()->getCharacter("player")->getPosition();
	const Vector2& bossPos = bossHornet->getPosition();
	bossHornet->setVelocity({ bossPos.x < playerPos.x ? SPEED_RUN : -SPEED_RUN, 0 });

	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
	else if(abs(playerPos.x - bossPos.x) < MIN_DIS)
	{
		int randNum = rangeRand(0, 3);
		if(bossHornet->getHp()>5)
		{
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
				bossHornet->switchState("squat");
				break;
			case 3:
				bossHornet->switchState("throwSilk");
				break;
			}
		}
		else
		{
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
				bossHornet->switchState("squat");
				break;
			case 3:
				bossHornet->switchState("throwSword");
				break;
			}
		}
	stopAudio(_T("hornetRun"));
	}
}
void BossHornetRunState::onExit()
{

	BossHornet * bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setVelocity(Vector2(0, 0));
}
#pragma endregion
#pragma region BossHornetSquatState
BossHornetSquatState::BossHornetSquatState()
{
	timer.setOneShot(true);
	timer.setWaitTime(0.5f);
	timer.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		bossHornet->switchState("dashOnFloor");
	});
}
void BossHornetSquatState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("squat");
	bossHornet->setFacingLeft(bossHornet->getPosition().x > CharacterManager::instance()->getCharacter("player")->getPosition().x);
	timer.restart();
}
void BossHornetSquatState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timer.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
}
#pragma endregion
#pragma region BossHornetThrowBarbState
BossHornetThrowBarbState::BossHornetThrowBarbState()
{
	timer.setOneShot(true);
	timer.setWaitTime(0.8f);
	timer.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		bossHornet->throwBarb();
		bossHornet->switchState("idle");
	});
}
void BossHornetThrowBarbState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("throwBarb");
	timer.restart();
	playAudio(_T("hornetThrowBarbs"), false);
}
void BossHornetThrowBarbState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timer.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
}
#pragma endregion
#pragma region BossHornetThrowSlikState
BossHornetThrowSilkState::BossHornetThrowSilkState()
{
	timer.setOneShot(true);
	timer.setWaitTime(0.9f);
	timer.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		bossHornet->setGravityEnable(true);
		bossHornet->setThrowingSilk(false);
		if(!bossHornet->isOnFloor()&&bossHornet->getHp()>5&&rangeRand(0,100)<25)
		{
			bossHornet->switchState("aim");
		}
		else if(!bossHornet->isOnFloor())
		{
			bossHornet->switchState("fall");
		}
		else
		{
			bossHornet->switchState("idle");
		}
	});
}
void BossHornetThrowSilkState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("throwSilk");
	bossHornet->setGravityEnable(false);
	bossHornet->setVelocity(Vector2(0, 0));
	bossHornet->setThrowingSilk(true);
	timer.restart();
	playAudio(_T("hornetThrowSilk"), false);
}
void BossHornetThrowSilkState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timer.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
}
#pragma endregion
#pragma region BossHornetThrowSwordState
//TO DO:让飞剑回来的时候才切换状态
BossHornetThrowSwordState::BossHornetThrowSwordState()
{
	timerThrow.setOneShot(true);
	timerThrow.setWaitTime(0.65f);
	timerThrow.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		bossHornet->throwSword();
		playAudio(_T("hornetThrowSword"), false);
	});
	timerSwitch.setOneShot(true);
	timerSwitch.setWaitTime(1.0f);
	timerSwitch.setOnTimeOut([&]() {
		BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
		
		int randNum = rangeRand(0, 9);
		if (bossHornet->getHp() > 5) {
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				bossHornet->switchState("squat");
				break;
			case 5:
			case 6:
			case 7:
				bossHornet->switchState("jump");
				break;
			case 8:
			case 9:
				bossHornet->switchState("idle");
				break;
			}
		}
		else {
			switch (randNum)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				bossHornet->switchState("jump");
				break;
			case 5:
			case 6:
			case 7:
				bossHornet->switchState("throwSilk");
				break;
			case 8:
			case 9:
				bossHornet->switchState("idle");
				break;
			}
		}
	});
}
void BossHornetThrowSwordState::onEnter()
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	bossHornet->setAnimation("throwSword");
	bossHornet->setVelocity(Vector2(0, 0));
	timerThrow.restart();
	timerSwitch.restart();
}
void BossHornetThrowSwordState::onUpdate(float dt)
{
	BossHornet* bossHornet = (BossHornet*)CharacterManager::instance()->getCharacter("bossHornet");
	timerThrow.onUpdate(dt);
	timerSwitch.onUpdate(dt);
	if(bossHornet->getHp()<=0)
	{
		bossHornet->switchState("dead");
	}
}
#pragma endregion