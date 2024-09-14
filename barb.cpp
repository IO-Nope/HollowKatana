#include "barb.h"
#include"collisionManager.h"
#include"resourcesManager.h"
#include"characterManager.h"

Barb::Barb()
{
	diffPeriod = rangeRand(0, 6);
#pragma region ������ʼ��

#pragma region �������Ŷ���
	animationLoose.setInterval(0.15f);
	animationLoose.setLoop(true);
	animationLoose.setAnchorMode(Animation::AnchorMode::Centered);
	animationLoose.addframe(ResourcesManager::instance()->findAtlas("barbLoose"));
#pragma endregion

#pragma region �������鶯��
	animationBreak.setInterval(0.1f);
	animationBreak.setLoop(false);
	animationBreak.setAnchorMode(Animation::AnchorMode::Centered);
	animationBreak.addframe(ResourcesManager::instance()->findAtlas("barbBreak"));
	animationBreak.setOnFinished([&]() {
		isValid = false;
		});

#pragma endregion
#pragma endregion
#pragma region ��ײ���ʼ��
	//TO DO: barb����ײ���ʼ�� ������Ҫ�б�����Ч����
	collisionBox = CollisionManager::instance()->createBox();
	collisionBox->setLayerSrc(CollisionLayer::Enemy);
	collisionBox->setLayerDst(CollisionLayer::Player);
	collisionBox->setSize({ 20,20 });
	collisionBox->setOnCollide([&]() {
		onBreak();
		}); 
#pragma endregion
#pragma region ��ʱ����ʼ��
	//barb��ת����̬�Ķ�ʱ��

#pragma region ����ת����̬
	timerIdle.setWaitTime((float)rangeRand(3,10));
	timerIdle.setOneShot(true);
	timerIdle.setOnTimeOut([&]() {
		if(stage == Stage::Idle)
		{
			//TO DO: ������֮���ʵ����д
			stage = Stage::Aim;
			timerAim.restart();
		}
		});

#pragma endregion

#pragma region ������̬��׼
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
	//���¶�ʱ��
	if(stage == Stage::Idle)
	{
		timerIdle.onUpdate(dt);
	}
	else if(stage == Stage::Aim)
	{
		timerAim.onUpdate(dt);
	}
	
	//�����ƶ��߼�
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

	//���¶����߼�
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