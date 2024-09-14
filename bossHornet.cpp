#include "BossHornet.h"
#include"characterManager.h"
#include"resourcesManager.h"
#include"collisionManager.h"
#include"bossHornetStateNodes.h"
BossHornet::BossHornet()
{
	isFacingLeft = true;
	position = { 1050,200 };
	logicHeight = 100;
#pragma region 碰撞箱初始化
	hitBox->setSize({ 50, 80 });
	hurtBox->setSize({ 100,180 });

	hitBox->setLayerSrc(CollisionLayer::None);
	hitBox->setLayerDst(CollisionLayer::Player);

	hurtBox->setLayerSrc(CollisionLayer::Enemy);
	hurtBox->setLayerDst(CollisionLayer::None);

	hurtBox->setOnCollide([&]() {
		decreaseHp(1);
		});
#pragma endregion
#pragma region 空中丝线碰撞箱初始化
	collisionBoxSilk = CollisionManager::instance()->createBox();
	collisionBoxSilk->setLayerSrc(CollisionLayer::None);
	collisionBoxSilk->setLayerDst(CollisionLayer::Player);
	collisionBoxSilk->setSize({ 225,225 });
	collisionBoxSilk->setEnabled(false);
#pragma endregion
#pragma region 动画初始化
	{
#pragma region 自身动画初始化
#pragma region Aim
		{
			AnimationGroup& animationAim = animationPool["aim"];

			Animation& animationAimLeft = animationAim.left;
			animationAimLeft.setInterval(0.05f);
			animationAimLeft.setLoop(false);
			animationAimLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationAimLeft.addframe(ResourcesManager::instance()->findAtlas("hornetAimLeft"));

			Animation& animationAimRight = animationAim.right;
			animationAimRight.setInterval(0.05f);
			animationAimRight.setLoop(false);
			animationAimRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationAimRight.addframe(ResourcesManager::instance()->findAtlas("hornetAimRight"));
		}
#pragma endregion
#pragma region DashInAir
		{
			AnimationGroup& animationDashInAir = animationPool["dashInAir"];

			Animation& animationDashInAirLeft = animationDashInAir.left;
			animationDashInAirLeft.setInterval(0.05f);
			animationDashInAirLeft.setLoop(false);
			animationDashInAirLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationDashInAirLeft.addframe(ResourcesManager::instance()->findAtlas("hornetDashInAirLeft"));

			Animation& animationDashInAirRight = animationDashInAir.right;
			animationDashInAirRight.setInterval(0.05f);
			animationDashInAirRight.setLoop(false);
			animationDashInAirRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationDashInAirRight.addframe(ResourcesManager::instance()->findAtlas("hornetDashInAirRight"));
		}
#pragma endregion
#pragma region DashOnFloor
		{
			AnimationGroup& animationDashOnFloor = animationPool["dashOnFloor"];

			Animation& animationDashOnFloorLeft = animationDashOnFloor.left;
			animationDashOnFloorLeft.setInterval(0.05f);
			animationDashOnFloorLeft.setLoop(false);
			animationDashOnFloorLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationDashOnFloorLeft.addframe(ResourcesManager::instance()->findAtlas("hornetDashOnFloorLeft"));

			Animation& animationDashOnFloorRight = animationDashOnFloor.right;
			animationDashOnFloorRight.setInterval(0.05f);
			animationDashOnFloorRight.setLoop(false);
			animationDashOnFloorRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationDashOnFloorRight.addframe(ResourcesManager::instance()->findAtlas("hornetDashOnFloorRight"));
		}
#pragma endregion
#pragma region Fall
		{
			AnimationGroup& animationFall = animationPool["fall"];

			Animation& animationFallLeft = animationFall.left;
			animationFallLeft.setInterval(0.1f);
			animationFallLeft.setLoop(true);
			animationFallLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationFallLeft.addframe(ResourcesManager::instance()->findAtlas("hornetFallLeft"));

			Animation& animationFallRight = animationFall.right;
			animationFallRight.setInterval(0.1f);
			animationFallRight.setLoop(true);
			animationFallRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationFallRight.addframe(ResourcesManager::instance()->findAtlas("hornetFallRight"));
		}
#pragma endregion
#pragma region Idle
		{
			AnimationGroup& animationIdle = animationPool["idle"];

			Animation& animationIdleLeft = animationIdle.left;
			animationIdleLeft.setInterval(0.1f);
			animationIdleLeft.setLoop(true);
			animationIdleLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationIdleLeft.addframe(ResourcesManager::instance()->findAtlas("hornetIdleLeft"));

			Animation& animationIdleRight = animationIdle.right;
			animationIdleRight.setInterval(0.1f);
			animationIdleRight.setLoop(true);
			animationIdleRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationIdleRight.addframe(ResourcesManager::instance()->findAtlas("hornetIdleRight"));
		}
#pragma endregion
#pragma region Jump
		{
			AnimationGroup& animationJump = animationPool["jump"];

			Animation& animationJumpLeft = animationJump.left;
			animationJumpLeft.setInterval(0.1f);
			animationJumpLeft.setLoop(false);
			animationJumpLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationJumpLeft.addframe(ResourcesManager::instance()->findAtlas("hornetJumpLeft"));

			Animation& animationJumpRight = animationJump.right;
			animationJumpRight.setInterval(0.1f);
			animationJumpRight.setLoop(false);
			animationJumpRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationJumpRight.addframe(ResourcesManager::instance()->findAtlas("hornetJumpRight"));
		}
#pragma endregion
#pragma region Run
		{
			AnimationGroup& animationRun = animationPool["run"];

			Animation& animationRunLeft = animationRun.left;
			animationRunLeft.setInterval(0.05f);
			animationRunLeft.setLoop(true);
			animationRunLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationRunLeft.addframe(ResourcesManager::instance()->findAtlas("hornetRunLeft"));

			Animation& animationRunRight = animationRun.right;
			animationRunRight.setInterval(0.05f);
			animationRunRight.setLoop(true);
			animationRunRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationRunRight.addframe(ResourcesManager::instance()->findAtlas("hornetRunRight"));
		}
#pragma endregion
#pragma region Squat
		{
			AnimationGroup& animationSquat = animationPool["squat"];

			Animation& animationSquatLeft = animationSquat.left;
			animationSquatLeft.setInterval(0.05f);
			animationSquatLeft.setLoop(false);
			animationSquatLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationSquatLeft.addframe(ResourcesManager::instance()->findAtlas("hornetSquatLeft"));

			Animation& animationSquatRight = animationSquat.right;
			animationSquatRight.setInterval(0.05f);
			animationSquatRight.setLoop(false);
			animationSquatRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationSquatRight.addframe(ResourcesManager::instance()->findAtlas("hornetSquatRight"));
		}
#pragma endregion
#pragma region ThrowBarb
		{
			AnimationGroup& animationThrowBarb = animationPool["throwBarb"];

			Animation& animationThrowBarbLeft = animationThrowBarb.left;
			animationThrowBarbLeft.setInterval(0.1f);
			animationThrowBarbLeft.setLoop(true);
			animationThrowBarbLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationThrowBarbLeft.addframe(ResourcesManager::instance()->findAtlas("hornetThrowBarbLeft"));

			Animation& animationThrowBarbRight = animationThrowBarb.right;
			animationThrowBarbRight.setInterval(0.1f);
			animationThrowBarbRight.setLoop(true);
			animationThrowBarbRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationThrowBarbRight.addframe(ResourcesManager::instance()->findAtlas("hornetThrowBarbRight"));
		}
#pragma endregion
#pragma region ThrowSilk
		{
			AnimationGroup& animationThrowSilk = animationPool["throwSilk"];

			Animation& animationThrowSilkLeft = animationThrowSilk.left;
			animationThrowSilkLeft.setInterval(0.1f);
			animationThrowSilkLeft.setLoop(true);
			animationThrowSilkLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationThrowSilkLeft.addframe(ResourcesManager::instance()->findAtlas("hornetThrowSilkLeft"));

			Animation& animationThrowSilkRight = animationThrowSilk.right;
			animationThrowSilkRight.setInterval(0.1f);
			animationThrowSilkRight.setLoop(true);
			animationThrowSilkRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationThrowSilkRight.addframe(ResourcesManager::instance()->findAtlas("hornetThrowSilkRight"));
		}
#pragma endregion
#pragma region ThrowSword
		{
			AnimationGroup& animationThrowSword = animationPool["throwSword"];

			Animation& animationThrowSwordLeft = animationThrowSword.left;
			animationThrowSwordLeft.setInterval(0.05f);
			animationThrowSwordLeft.setLoop(false);
			animationThrowSwordLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationThrowSwordLeft.addframe(ResourcesManager::instance()->findAtlas("hornetThrowSwordLeft"));

			Animation& animationThrowSwordRight = animationThrowSword.right;
			animationThrowSwordRight.setInterval(0.05f);
			animationThrowSwordRight.setLoop(false);
			animationThrowSwordRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationThrowSwordRight.addframe(ResourcesManager::instance()->findAtlas("hornetThrowSwordRight"));
		}
#pragma endregion
#pragma endregion
#pragma region 生成物动画,特效初始化
#pragma region Silk
		{
			animationSilk.setInterval(0.1f);
			animationSilk.setLoop(true);
			animationSilk.setAnchorMode(Animation::AnchorMode::Centered);
			animationSilk.addframe(ResourcesManager::instance()->findAtlas("silk"));
		}
#pragma endregion
#pragma region  DashInAirVfx
		{
			Animation& animationDashInAirVfxLeft = animationDashInAirVfx.left;
			animationDashInAirVfxLeft.setInterval(0.1f);
			animationDashInAirVfxLeft.setLoop(false);
			animationDashInAirVfxLeft.setAnchorMode(Animation::AnchorMode::Centered);
			animationDashInAirVfxLeft.addframe(ResourcesManager::instance()->findAtlas("hornetVfxDashInAirLeft"));

			Animation& animationDashInAirVfxRight = animationDashInAirVfx.right;
			animationDashInAirVfxRight.setInterval(0.1f);
			animationDashInAirVfxRight.setLoop(false);
			animationDashInAirVfxRight.setAnchorMode(Animation::AnchorMode::Centered);
			animationDashInAirVfxRight.addframe(ResourcesManager::instance()->findAtlas("hornetVfxDashInAirRight"));
		}	
#pragma endregion
#pragma region DashOnFloorVfx
		{
			Animation& animationDashOnFloorVfxLeft = animationDashOnFloorVfx.left;
			animationDashOnFloorVfxLeft.setInterval(0.1f);
			animationDashOnFloorVfxLeft.setLoop(false);
			animationDashOnFloorVfxLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationDashOnFloorVfxLeft.addframe(ResourcesManager::instance()->findAtlas("hornetVfxDashOnFloorLeft"));

			Animation& animationDashOnFloorVfxRight = animationDashOnFloorVfx.right;
			animationDashOnFloorVfxRight.setInterval(0.1f);
			animationDashOnFloorVfxRight.setLoop(false);
			animationDashOnFloorVfxRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
			animationDashOnFloorVfxRight.addframe(ResourcesManager::instance()->findAtlas("hornetVfxDashOnFloorRight"));
		}
#pragma endregion
#pragma endregion
	}
#pragma endregion
#pragma region 状态机初始化
{
	stateMachine.registerState("aim", new BossHornetAimState());
	stateMachine.registerState("dashInAir", new BossHornetDashInAirState());
	stateMachine.registerState("dashOnFloor", new BossHornetDashOnFloorState());
	stateMachine.registerState("dead", new BossHornetDeadState());
	stateMachine.registerState("fall", new BossHornetFallState());
	stateMachine.registerState("idle", new BossHornetIdleState());
	stateMachine.registerState("jump", new BossHornetJumpState());
	stateMachine.registerState("run", new BossHornetRunState());
	stateMachine.registerState("squat", new BossHornetSquatState());
	stateMachine.registerState("throwBarb", new BossHornetThrowBarbState());
	stateMachine.registerState("throwSilk", new BossHornetThrowSilkState());
	stateMachine.registerState("throwSword", new BossHornetThrowSwordState());
	
	stateMachine.setEntry("idle");
}
#pragma endregion
}

BossHornet::~BossHornet()
{
	CollisionManager::instance()->destroyBox(collisionBoxSilk);
}

void BossHornet::onUpdate(float dt)
{
	if (velocity.x >= 0.0001f) {
		isFacingLeft = (velocity.x < 0);
	}

	Character::onUpdate(dt);

	hitBox->setPosition(getLogicCenter());

	if(isThrowingSilk)
	{
		collisionBoxSilk->setPosition(getLogicCenter());
		animationSilk.setPositon(getLogicCenter());
		animationSilk.onUpdate(dt);
	}

	if (isDashingInAir||isDashingOnFloor) {
		currentDashAnimation->setPositon(isDashingInAir ? getLogicCenter(): position);
		currentDashAnimation->onUpdate(dt);
	}
	//子对象更新
	for(Barb* barb : barbs)
	{
		barb->onUpdate(dt);
	}
	for(Sword* sword : swords)
	{
		sword->onUpdate(dt);
	}

	//失效子对象移除
	barbs.erase(std::remove_if(barbs.begin(), barbs.end(), 
		[](Barb* barb) 
		{
		bool canRemove = !barb->checkValid();
		if (canRemove) {
			delete barb;
		}
		return canRemove;
		}),
		barbs.end());

	swords.erase(std::remove_if(swords.begin(), swords.end(),
		[](Sword* sword)
		{
			bool canRemove = !sword->checkValid();
			if (canRemove) {
				delete sword;
			}
			return canRemove;
			}),
		swords.end());

}

void BossHornet::onRender()
{
	for(Barb* barb : barbs)
	{
		barb->onRender();
	}
	for(Sword* sword : swords)
	{
		sword->onRender();
	}

	Character::onRender();

	if(isThrowingSilk)
	{
		animationSilk.onRender();
	}

	if (isDashingInAir || isDashingOnFloor) {
		currentDashAnimation->onRender();
	}
}

void BossHornet::onHurt()
{
	switch (rangeRand(0, 2))
	{
	case 0:
		playAudio(_T("hornetHurt1"), false);
		break;
	case 1:
		playAudio(_T("hornetHurt2"), false);
		break;
	case 2:
		playAudio(_T("hornetHurt3"), false);
		break;
	}

}

void BossHornet::throwBarb()
{
	int numNewBarb = rangeRand(3,6);
	if(barbs.size() >=10)
	{
		numNewBarb = 1;
	}
	int widthGarid = getwidth()/ (numNewBarb );
	for (int i = 0; i < numNewBarb; i++)
	{
		Barb* newBarb = new Barb();
		int randX = rangeRand(i * widthGarid, (i + 1) * widthGarid);
		int randY = rangeRand(250,500);
		newBarb->setPosition({ (float)randX,(float)randY});
		barbs.push_back(newBarb);
	}
}

void BossHornet::throwSword() {
	Sword* newSword = new Sword(getLogicCenter(), isFacingLeft);
	swords.push_back(newSword);
}

void BossHornet::onDash()
{
	if (isDashingInAir) {
		currentDashAnimation = velocity.x < 0 ? &animationDashInAirVfx.left : &animationDashInAirVfx.right;
	}
	else if (isDashingOnFloor) {
		currentDashAnimation = velocity.x < 0 ? &animationDashOnFloorVfx.left : &animationDashOnFloorVfx.right;
	}
	currentDashAnimation->reset();
}

void BossHornet::onThrowSilk()
{
	animationSilk.reset();
}