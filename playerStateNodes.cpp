#include"playerStateNodes.h"
#include"player.h"
#include"characterManager.h"
#pragma region AttackState
PlayerAttackState::PlayerAttackState() {
	timer.setWaitTime(0.3f);
	timer.setOneShot(true);
	timer.setOnTimeOut([&]() {
		Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
		player->setAttacking(false);
		}
	);
}
void PlayerAttackState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("attack");

	player->getHitBox()->setEnabled(true);
	player->setAttacking(true);
	updateHitBoxPosition();

	player->onAttack();
	timer.restart();

	switch (rangeRand(0,2))
	{
		case 0:
			playAudio(_T("playerAttack1"),false);
			break;
		case 1:
			playAudio(_T("playerAttack2"), false);
			break;
		case 2:
			playAudio(_T("playerAttack3"), false);
			break;
	}
}
void PlayerAttackState::onUpdate(float dt) {
	timer.onUpdate(dt);
	updateHitBoxPosition();
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");

	if(player->getHp()<=0)
	{
		player->switchState("dead");
		return;
	}
	if (!player->getAttacking()) 
	{
		if(player->getVelocity().y>0)
		{
			player->switchState("fall");
		}
		else if(player->getMoveAxis() ==0)
		{
			player->switchState("idle");
		}
		else if(player->isOnFloor()&&player->getMoveAxis()!=0)
		{
			player->switchState("run");
		}
	}
}
void PlayerAttackState::onExit() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->getHitBox()->setEnabled(false);
	player->setAttacking(false);
}

void PlayerAttackState::updateHitBoxPosition() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	Vector2 posCenter = player->getLogicCenter();
	CollisionBox* hitBox = player->getHitBox();
	const Vector2& sizeHitBox =hitBox->getSize();
	Vector2 posHitBox;
	switch (player->getAttackDir()) {
		case Player::AttackDir::Left:
			posHitBox = {posCenter.x- sizeHitBox.x / 2, posCenter.y};
			break;
		case Player::AttackDir::Right:
			posHitBox = { posCenter.x+ sizeHitBox.x/2, posCenter.y };
			break;
		case Player::AttackDir::Up:
			posHitBox = { posCenter.x, posCenter.y - sizeHitBox.y / 2 };
			break;
		case Player::AttackDir::Down:
			posHitBox = { posCenter.x, posCenter.y + sizeHitBox.y / 2 };
			break;
	}
	hitBox->setPosition(posHitBox);
}
#pragma endregion
#pragma region DeadState
PlayerDeadState::PlayerDeadState() {
	timer.setWaitTime(2.0f);
	timer.setOneShot(true);
	timer.setOnTimeOut([&]() {
		MessageBox(GetHWnd(), _T("不对...、n这样不行"), _T("Game Over"), MB_OK);
		//TODO:Restart
		exit(0);
		}
	);
}
void PlayerDeadState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("dead");
	playAudio(_T("playerDead"), false);
}
void PlayerDeadState::onUpdate(float dt) {
	timer.onUpdate(dt);
}
void PlayerDeadState::onExit() {
	
}
#pragma endregion
#pragma region FallState
void PlayerFallState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("fall");
}

void PlayerFallState::onUpdate(float dt) {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	
	if(player->getHp()<=0)
	{
		player->switchState("dead");
		return;
	}
	if (player->isOnFloor())
	{
		player->switchState("idle");
		player->onLand();

		playAudio(_T("playerLand"), false);
	}
	else if (player->canAttack()) {
		player->switchState("attack");
	}
	
}
#pragma endregion
#pragma region IdleState
void PlayerIdleState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("idle");
}
void PlayerIdleState::onUpdate(float dt) {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	if(player->getHp()<=0)
	{
		player->switchState("dead");
		return;
	}
	if(player->canAttack()){
		player->switchState("attack");
	}
	else if (player->getVelocity().y > 0) {
		player->switchState("fall");
	}
	else if (player->canJump()) {
		player->switchState("jump");
	}
	else if (player->canRoll()) {
		player->switchState("roll");
	}
	else if(player -> isOnFloor()&&player->getMoveAxis() != 0) {
		player->switchState("run");
	}
}
#pragma endregion
#pragma region JumpState
void PlayerJumpState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("jump");
	player->onJump();

	playAudio(_T("playerJump"), false);

}

void PlayerJumpState::onUpdate(float dt) {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	if(player->getHp()<=0)
	{
		player->switchState("dead");
		return;
	}
	if (player->getVelocity().y >= 0) {
		player->switchState("fall");
	}
	else if(player->canAttack()){
		player->switchState("attack");
	}
}
void PlayerJumpState::onExit() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->onLand();
}
#pragma endregion
#pragma region RollState
PlayerRollState::PlayerRollState() {
	timer.setWaitTime(0.35f);
	timer.setOneShot(true);
	timer.setOnTimeOut([&]() {
		Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
		player->setRolling(false);
		}
	);
}
void PlayerRollState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("roll");
	player->getHurtBox()->setEnabled(false);
	player->setRolling(true);
	player->onRoll();
	timer.restart();

	playAudio(_T("playerRoll"), false);
}

void PlayerRollState::onUpdate(float dt) {
	timer.onUpdate(dt);
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	if(player->getHp()<=0)
	{
		player->switchState("dead");
		return;
	}
	if(!player->getRolling())
	{
		if(player->getVelocity().y>0)
		{
			player->switchState("fall");
		}
		else if (player->isOnFloor() && player->getMoveAxis() != 0)
		{
			player->switchState("run");
		}
		else if(player->canJump())
		{
			player->switchState("jump");
		}
		else if(player->getMoveAxis() ==0)
		{
			player->switchState("idle");
		}
		
	}
}
void PlayerRollState::onExit() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->getHurtBox()->setEnabled(true);
	player->setRolling(false);
}
#pragma endregion
#pragma region RunState
void PlayerRunState::onEnter() {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	player->setAnimation("run");

	playAudio(_T("playerRun"), true);
}

void PlayerRunState::onUpdate(float dt) {
	Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	if(player->getHp()<=0)
	{
		player->switchState("dead");
		return;
	}
	if(player->getMoveAxis()== 0)
	{
		player->switchState("idle");
	}
	else if(player->canAttack())
	{
		player->switchState("attack");
	}
	else if(player->canJump())
	{
		player->switchState("jump");
	}
	else if(player->canRoll())
	{
		player->switchState("roll");
	}
}

void PlayerRunState::onExit() {
	//Player* player = (Player*)CharacterManager::instance()->getCharacter("player");
	stopAudio(_T("playerRun"));
}
#pragma endregion
#pragma region MoreState...

#pragma endregion