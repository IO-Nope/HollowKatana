#include"player.h"

#include"resourcesManager.h"
#include"bulletTimeManager.h"
#include"playerStateNodes.h"
#include<cmath>

Player::Player()
{
#pragma region 一些属性初始化
	isFacingLeft = false;
	position = { 250,200 };
	logicHeight = 120;
#pragma endregion 
#pragma region 碰撞箱初始化
	hitBox->setSize({ 150,150 });
	hurtBox->setSize({ 40,80 });
	//下劈
	hitBox->setLayerSrc(CollisionLayer::None);
	hitBox->setOnCollide([&]() {
		if (getAttackDir() == AttackDir::Down) {
			this->addAttackSpeed();
		}
		});
	hitBox->setLayerDst(CollisionLayer::Enemy);
	hurtBox->setLayerSrc(CollisionLayer::Player);
	hurtBox->setLayerDst(CollisionLayer::None);

	hitBox->setEnabled(false);
	hurtBox->setOnCollide([&]() {
		decreaseHp(1);
		});
#pragma endregion 
#pragma region CD初始化
	timerRollCd.setWaitTime(CD_ROLL);
	timerRollCd.setOneShot(true);
	timerRollCd.setOnTimeOut([&]() {
		printf("roll cd comp\n");
		isRollCdComp = true;
		});

	//攻击处理
	timerAttackCd.setWaitTime(CD_ATTACK);
	timerAttackCd.setOneShot(true);
	timerAttackCd.setOnTimeOut([&]() {
		printf("attack cd comp\n");
		isAttackCdComp = true;
		});
#pragma endregion 
#pragma region 动画初始化
#pragma region 攻击动画
	{
		AnimationGroup& animationAttack = animationPool["attack"];
		//向左动画
		Animation& animationAttackLeft = animationAttack.left;
		animationAttackLeft.setInterval(0.05f);
		animationAttackLeft.setLoop(false);
		animationAttackLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationAttackLeft.addframe(ResourcesManager::instance()->findImage("playerAttackLeft"), 5);
		//向右动画
		Animation& animationAttackRight = animationAttack.right;
		animationAttackRight.setInterval(0.05f);
		animationAttackRight.setLoop(false);
		animationAttackRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationAttackRight.addframe(ResourcesManager::instance()->findImage("playerAttackRight"), 5);
	}
#pragma endregion
#pragma region 死亡动画
	{
		AnimationGroup& animationDead = animationPool["dead"];
		//向左动画
		Animation& animationDeadLeft = animationDead.left;
		animationDeadLeft.setInterval(0.05f);
		animationDeadLeft.setLoop(false);
		animationDeadLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationDeadLeft.addframe(ResourcesManager::instance()->findImage("playerDeadLeft"), 6);
		//向右动画
		Animation& animationDeadRight = animationDead.right;
		animationDeadRight.setInterval(0.05f);
		animationDeadRight.setLoop(false);
		animationDeadRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationDeadRight.addframe(ResourcesManager::instance()->findImage("playerDeadRight"), 6);
	}
#pragma endregion
#pragma region 掉落动画
	{
		AnimationGroup& animationFall = animationPool["fall"];
		//向左动画
		Animation& animationFallLeft = animationFall.left;
		animationFallLeft.setInterval(0.15f);
		animationFallLeft.setLoop(true);
		animationFallLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationFallLeft.addframe(ResourcesManager::instance()->findImage("playerFallLeft"), 5);
		//向右动画
		Animation& animationFallRight = animationFall.right;
		animationFallRight.setInterval(0.15f);
		animationFallRight.setLoop(true);
		animationFallRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationFallRight.addframe(ResourcesManager::instance()->findImage("playerFallRight"), 5);
	}
#pragma endregion
#pragma region 空闲动画
	{
		AnimationGroup& animationIdle = animationPool["idle"];
		//向左动画
		Animation& animationIdleLeft = animationIdle.left;
		animationIdleLeft.setInterval(0.15f);
		animationIdleLeft.setLoop(true);
		animationIdleLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationIdleLeft.addframe(ResourcesManager::instance()->findImage("playerIdleLeft"), 5);
		//向右动画
		Animation& animationIdleRight = animationIdle.right;
		animationIdleRight.setInterval(0.15f);
		animationIdleRight.setLoop(true);
		animationIdleRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationIdleRight.addframe(ResourcesManager::instance()->findImage("playerIdleRight"), 5);
	}
#pragma endregion
#pragma region 跳跃动画
	{
		AnimationGroup& animationJump = animationPool["jump"];
		//向左动画
		Animation& animationJumpLeft = animationJump.left;
		animationJumpLeft.setInterval(0.15f);
		animationJumpLeft.setLoop(false);
		animationJumpLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationJumpLeft.addframe(ResourcesManager::instance()->findImage("playerJumpLeft"), 5);
		//向右动画
		Animation& animationJumpRight = animationJump.right;
		animationJumpRight.setInterval(0.15f);
		animationJumpRight.setLoop(false);
		animationJumpRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationJumpRight.addframe(ResourcesManager::instance()->findImage("playerJumpRight"), 5);
	}
#pragma endregion
#pragma region 翻滚动画
	{
		AnimationGroup& animationRoll = animationPool["roll"];
		//向左动画
		Animation& animationRollLeft = animationRoll.left;
		animationRollLeft.setInterval(0.05f);
		animationRollLeft.setLoop(false);
		animationRollLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationRollLeft.addframe(ResourcesManager::instance()->findImage("playerRollLeft"), 7);
		//向右动画
		Animation& animationRollRight = animationRoll.right;
		animationRollRight.setInterval(0.05f);
		animationRollRight.setLoop(false);
		animationRollRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationRollRight.addframe(ResourcesManager::instance()->findImage("playerRollRight"), 7);
	}
#pragma endregion
#pragma region 跑动动画
	{
		AnimationGroup& animationRun = animationPool["run"];
		//向左动画
		Animation& animationRunLeft = animationRun.left;
		animationRunLeft.setInterval(0.075f);
		animationRunLeft.setLoop(true);
		animationRunLeft.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationRunLeft.addframe(ResourcesManager::instance()->findImage("playerRunLeft"), 10);
		//向右动画
		Animation& animationRunRight = animationRun.right;
		animationRunRight.setInterval(0.075f);
		animationRunRight.setLoop(true);
		animationRunRight.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationRunRight.addframe(ResourcesManager::instance()->findImage("playerRunRight"), 10);
	}
#pragma endregion
#pragma endregion
#pragma region 特效初始化
	{
		animationSlashUp.setInterval(0.07f);
		animationSlashUp.setLoop(false);
		animationSlashUp.setAnchorMode(Animation::AnchorMode::Centered);
		animationSlashUp.addframe(ResourcesManager::instance()->findImage("playerVfxAttackUp"), 5);

		animationSlashDown.setInterval(0.07f);
		animationSlashDown.setLoop(false);
		animationSlashDown.setAnchorMode(Animation::AnchorMode::Centered);
		animationSlashDown.addframe(ResourcesManager::instance()->findImage("playerVfxAttackDown"), 5);

		animationSlashLeft.setInterval(0.07f);
		animationSlashLeft.setLoop(false);
		animationSlashLeft.setAnchorMode(Animation::AnchorMode::Centered);
		animationSlashLeft.addframe(ResourcesManager::instance()->findImage("playerVfxAttackLeft"), 5);

		animationSlashRight.setInterval(0.07f);
		animationSlashRight.setLoop(false);
		animationSlashRight.setAnchorMode(Animation::AnchorMode::Centered);
		animationSlashRight.addframe(ResourcesManager::instance()->findImage("playerVfxAttackRight"), 5);

		animationJumpVfx.setInterval(0.1f);
		animationJumpVfx.setLoop(false);
		animationJumpVfx.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationJumpVfx.addframe(ResourcesManager::instance()->findImage("playerVfxJump"), 5);
		animationJumpVfx.setOnFinished([&]() {
			isJumpVfxVisible = false;
			});

		animationLandVfx.setInterval(0.1f);
		animationLandVfx.setLoop(false);
		animationLandVfx.setAnchorMode(Animation::AnchorMode::BottomCentered);
		animationLandVfx.addframe(ResourcesManager::instance()->findImage("playerVfxLand"), 5);
		animationLandVfx.setOnFinished([&]() {
			isLandVfxVisible = false;
			});
	}
#pragma endregion
#pragma region 状态机初始化
	{
		stateMachine.registerState("attack", new PlayerAttackState());
		stateMachine.registerState("dead", new PlayerDeadState());
		stateMachine.registerState("fall", new PlayerFallState());
		stateMachine.registerState("idle", new PlayerIdleState());
		stateMachine.registerState("jump", new PlayerJumpState());
		stateMachine.registerState("roll", new PlayerRollState());
		stateMachine.registerState("run", new PlayerRunState());

		stateMachine.setEntry("idle");

	}
#pragma endregion
}

Player::~Player() = default;

void Player::onInput(const ExMessage& msg) {
	if(hp <= 0) return;
	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
			case 0x41: //A
			case VK_LEFT:
				isLeftKeyDown = true;
				break;
			case 0x44: //D
			case VK_RIGHT:
				isRightKeyDown = true;
				break;
			case 0x57: //W
			case 0x4B: //K
			case VK_UP:
			case VK_SPACE:
				isJumpKeyDown = true;
				break;
			case 0x53: //S
			case VK_DOWN:
				isRollKeyDown = true;
				break;
			case 0x4A: //J
				updateAttackDir();
				isFacingLeft = getAttackDir() == AttackDir::Left;
				isAttackKeyDown = true;
				break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode)
		{
			case 0x41: //A
			case VK_LEFT:
				isLeftKeyDown = false;
				break;
			case 0x44: //D
			case VK_RIGHT:
				isRightKeyDown = false;
				break;
			case 0x57: //W
			case 0x4B: //K
			case VK_UP:
			case VK_SPACE:
				isJumpKeyDown = false;
				break;
			case 0x53: //S
			case VK_DOWN:
				isRollKeyDown = false;
				break;
			case 0x4A: //J
				isAttackKeyDown = false;
				break;
		}
		break;
	case WM_LBUTTONDOWN:
		updateAttackDir(msg.x, msg.y);
		isFacingLeft = getAttackDir() == AttackDir::Left;
		isAttackKeyDown = true;
		//addAttackSpeed(msg.x, msg.y);
		break;
	case WM_LBUTTONUP:
		isAttackKeyDown = false;
		break;
	case WM_RBUTTONDOWN:
		playAudio(_T("bulletTime"), false);
		BulletTimeManager::Instance()->setStatus(BulletTimeManager::Status::Entering);
		break;
	case WM_RBUTTONUP:
		playAudio(_T("bulletTime"), false);
		BulletTimeManager::Instance()->setStatus(BulletTimeManager::Status::Exiting);
		break;
	}
}

void Player::onUpdate(float dt) {
	if (hp > 0 && !isRolling) {
		velocity.x = getMoveAxis() * SPEED_RUN;
	}

	if(getMoveAxis() != 0) {
		isFacingLeft = (getMoveAxis() < 0);
	}
	

	timerRollCd.onUpdate(dt);
	timerAttackCd.onUpdate(dt);

	animationJumpVfx.onUpdate(dt);
	animationLandVfx.onUpdate(dt);

	if(isAttacking) {
		currentSlashAnimation->setPositon(getLogicCenter());
		currentSlashAnimation->onUpdate(dt);
	}

	Character::onUpdate(dt);
}

void Player::onRender() {
	if (isJumpVfxVisible) {
		animationJumpVfx.onRender();
	}
	if (isLandVfxVisible) {
		animationLandVfx.onRender();
	}
	Character::onRender();

	if(isAttacking) {
		currentSlashAnimation->onRender();
	}
}
void Player::onHurt() {
	playAudio(_T("playerHurt"), false);
}
void Player::onJump() {
	//playAudio(_T("playerJump"), false);
	velocity.y = -SPEED_JUMP;
	isJumpVfxVisible = true;
	animationJumpVfx.setPositon(position);
	animationJumpVfx.reset();
}

void Player::onLand() {
	//playAudio(_T("playerLand"), false);
	isLandVfxVisible = true;
	animationLandVfx.setPositon(position);
	animationLandVfx.reset();
}

void Player::onRoll() {
	//playAudio(_T("playerRoll"), false);
	timerRollCd.restart();
	isRollCdComp = false;
	velocity.x = isFacingLeft ? -SPEED_ROLL : SPEED_ROLL;
}

void Player::onAttack() {
	timerAttackCd.restart();
	isAttackCdComp = false;
	switch (attackDir) {
		case Player::AttackDir::Up:
			currentSlashAnimation = &animationSlashUp;
			this->velocity.y = -SPEED_ATTACK;
			break;
		case Player::AttackDir::Down:
			currentSlashAnimation = &animationSlashDown;
			this->velocity.y = SPEED_ATTACK;
			break;
		case Player::AttackDir::Left:
			currentSlashAnimation = &animationSlashLeft;
			this->velocity.x -= SPEED_ATTACK;
			break;
		case Player::AttackDir::Right:
			currentSlashAnimation = &animationSlashRight;
			this->velocity.x += SPEED_ATTACK;
			break;
	}
	currentSlashAnimation->setPositon(getLogicCenter());
	currentSlashAnimation->reset();
}

/// <summary>
/// 利用鼠标输入更新方向
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Player::updateAttackDir(int x,int y) {
	static const float PI = 3.1415926f;
	static const float PI_4 = PI / 4;
	float angle = std::atan2(y-position.y, x - position.x);
	angle+=PI_4;
	if (angle <0)
	{
		angle -= (PI / 2);
	}
	printf("angle:%f\n", angle);
	printf("type:%d\n", (int)(angle / (PI / 2)));
	switch((int)(angle / (PI / 2))) {
		case 0:
			attackDir = AttackDir::Right;
			break;
		case -1:
			attackDir = AttackDir::Up;
			break;
		case 2:
		case -2:
			attackDir = AttackDir::Left;
			break;
		case 1:
			attackDir = AttackDir::Down;
			break;
	}
	if (attackDir == AttackDir::Down && this->isOnFloor()) {
		updateAttackDir();
	}
}
/// <summary>
/// 用移动方向更新攻击方向
/// </summary>
void Player::updateAttackDir()
{
	if (isJumpKeyDown) {
		attackDir = AttackDir::Up;
		return;
	}
	else if(isRollKeyDown&&!this->isOnFloor()){
		attackDir = AttackDir::Down;
		return;
	}
	else if(isLeftKeyDown){
		attackDir = AttackDir::Left;
		return;
	}
	else if (isRightKeyDown) {
		attackDir = AttackDir::Right;
		return;
	}
	if (isFacingLeft)
	{
		attackDir = AttackDir::Left;
		return;
	}
	else
	{
		attackDir = AttackDir::Right;
		return;
	}
}

void Player::addAttackSpeed() {
	this->velocity.y = -SPEED_ATTACK;
}

