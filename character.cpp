#include"character.h"
#include"collisionManager.h"
Character::Character() {
	hitBox = CollisionManager::instance()->createBox();
	hurtBox = CollisionManager::instance()->createBox();

	timerInvulnerableStatus.setWaitTime(1.0f);
	timerInvulnerableStatus.setOneShot(true);
    timerInvulnerableStatus.setOnTimeOut([&]() {
			isInvulnerable = false;
		}
	);
	timerInvulnerableBlink.setWaitTime(0.075f);
	timerInvulnerableBlink.setOneShot(false);
	timerInvulnerableBlink.setOnTimeOut([&]() {
		isBlinkInvisible = !isBlinkInvisible;
		}
	);
}

Character::~Character()
{
	CollisionManager::instance()->destroyBox(hitBox);
	CollisionManager::instance()->destroyBox(hurtBox);
}

void Character::decreaseHp(int val=1)
{
	if (isInvulnerable) {
		return;
	}

	if (hp > 0) {
		hp -= val;
		makeInvulnerable();
	}
	onHurt();
}
void Character::onInput(const ExMessage& msg)
{
}
void Character::onUpdate(float dt)
{
	stateMachine.onUpdate(dt);

	if(hp<=0)
	{
		velocity.x= 0;

	}
	if (enableGravity) {
		velocity.y += GRAVITY * dt;
	}
	position +=( velocity * dt);
	//地板判定
	if(position.y>= FLOORY)
	{
		position.y = FLOORY;
		velocity.y = 0;
	}
	//左右边界判定
	if(position.x<0)
	{
		position.x = 0;
	}	
	if (position.x > getwidth()) {
		position.x = (float)getwidth();
	}
	
	hurtBox->setPosition(getLogicCenter());

	timerInvulnerableStatus.onUpdate(dt);

	if(isInvulnerable)
	{
		timerInvulnerableBlink.onUpdate(dt);
	}

	if(!currentAnimation)
	{
		return;
	}

	Animation& animation = (isFacingLeft) ? currentAnimation->left : currentAnimation->right;
	animation.onUpdate(dt);
	animation.setPositon(position);
}

void Character::onRender()
{
	if(!currentAnimation||isInvulnerable&&isBlinkInvisible)
	{
		return;
	}

	(isFacingLeft ? currentAnimation->left : currentAnimation->right).onRender();
}

void Character::onHurt()
{
}

void Character::switchState(const std::string& id)
{
	stateMachine.switchTo(id);
}

void Character::setAnimation(const std::string& id)
{
	currentAnimation = &animationPool[id];
	currentAnimation->left.reset();
	currentAnimation->right.reset();
}