#pragma once
#ifndef _PLAYER_STATE_NODES_H_
#define _PLAYER_STATE_NODES_H_

#include"timer.h"
#include"stateMachine.h"

class PlayerAttackState : public StateNode {
public:
	PlayerAttackState();
	~PlayerAttackState()=default;

	void onEnter() override;
	void onUpdate(float dt) override;
	void onExit() override;

private:
	Timer timer;

private:
	void updateHitBoxPosition();
};
class PlayerDeadState : public StateNode {
public:
	PlayerDeadState();
	~PlayerDeadState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;
	void onExit() override;

private:
	Timer timer;
};
class PlayerFallState : public StateNode {
public:
	PlayerFallState()=default;
	~PlayerFallState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;

};
class PlayerIdleState : public StateNode {
public:
	PlayerIdleState()=default;
	~PlayerIdleState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;
};
class PlayerJumpState : public StateNode {
public:
	PlayerJumpState()=default;
	~PlayerJumpState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;
	void onExit() override;

private:
	Timer timer;


};
class PlayerRollState : public StateNode {
public:
	PlayerRollState();
	~PlayerRollState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;
	void onExit() override;

private:
	Timer timer;
};
class PlayerRunState : public StateNode {
public:
	PlayerRunState()=default;
	~PlayerRunState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;
	void onExit() override;
};
#endif // !_PLAYER_STATE_NODES_H_