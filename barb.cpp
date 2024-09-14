#include "barb.h"
#include"collisionManager.h"
#include"resourcesManager.h"
#include"characterManager.h"

Barb::Barb()
{
	diffPeriod = rangeRand(0, 6);
#pragma region 动画初始化

#pragma region 刺球缩放动画
	animationLoose.setInterval(0.15f);
	animationLoose.setLoop(true);
	animationLoose.setAnchorMode(Animation::AnchorMode::Centered);
	animationLoose.addframe(ResourcesManager::instance()->findAtlas("barbLoose"));
#pragma endregion

#pragma region 刺球破碎动画
	animationBreak.setInterval(0.1f);
	animationBreak.setLoop(false);
	animationBreak.setAnchorMode(Animation::AnchorMode::Centered);
	animationBreak.addframe(ResourcesManager::instance()->findAtlas("barbBreak"));
	animationBreak.setOnFinished([&]() {
		isValid = false;
		});

#pragma endregion
#pragma endregion
#pragma region 碰撞箱初始化
	//TO DO: barb的碰撞箱初始化 但是需要有被击退效果！
	collisionBox = CollisionManager::instance()->createBox();
	collisionBox->setLayerSrc(CollisionLayer::Enemy);
	collisionBox->setLayerDst(CollisionLayer::Player);
	collisionBox->setSize({ 20,20 });
	collisionBox->setOnCollide([&]() {
		onBreak();
		}); 
#pragma endregion
#pragma region 定时器初始化
	//barb的转变形态的定时器

#pragma region 刺球转变形态
	timerIdle.setWaitTime((float)rangeRand(3,10));
	timerIdle.setOneShot(true);
	timerIdle.setOnTimeOut([&]() {
		if(stage == Stage::Idle)
		{
			//TO DO: 被击中之后的实现重写
			stage = Stage::Aim;
			timerAim.restart();
		}
		});

#pragma endregion

#pragma region 刺球形态瞄准
	timerAim.setWaitTime(0.75f);
	timerAim.setOneShot(true);
	timerAim.setOnTimeOut([&]() {
		if(stage == Stage::Aim)
		{
			stage = Stage::Dash;
			const Vector2& posPlayer = CharacterManager::instance()->getCharacter("player")->getPosition();
			velocity = (posPlayer - currentPosition).normalize()* SPEEDDASH;
		}
		});

#pragma endregion
#pragma endregion
}

Barb::~Barb()
{
	CollisionManager::instance()->destroyBox(collisionBox);
}

void Barb::onUpdate(float dt)
{
	//更新定时器
	if(stage == Stage::Idle)
	{
		timerIdle.onUpdate(dt);
	}
	else if(stage == Stage::Aim)
	{
		timerAim.onUpdate(dt);
	}
	
	//更新移动逻辑
	totalDeltaTime += dt;
	switch (stage) {
	case Barb::Stage::Idle:
		currentPosition.y = basePosition.y + sin(totalDeltaTime * 2+diffPeriod) * 30;
		break;
	case Barb::Stage::Aim:
		currentPosition.x= basePosition.x + rangeRand(-10, 10);
		break;
	case Barb::Stage::Dash:
		currentPosition += velocity * dt;
		if(currentPosition.y >= CharacterManager::instance()->getCharacter("player")->getFloorY())
		{
			onBreak();
		}
		if(currentPosition.x < -200 || currentPosition.x > getwidth()+200||currentPosition.y< -200)
		{
			isValid = false;
		}
		break;	
	}
	collisionBox->setPosition(currentPosition);

	//更新动画逻辑
	currentAnimation = (stage == Stage::Break ? &animationBreak : &animationLoose);
	currentAnimation->setPositon(currentPosition);
	currentAnimation->onUpdate(dt);

}

void Barb::onRender()
{
	currentAnimation->onRender();
}

void Barb::onBreak()
{
	if (stage == Stage::Break)return;
	stage = Stage::Break;
	collisionBox->setEnabled(false);

	playAudio(_T("barbBreak"),false);
	
}