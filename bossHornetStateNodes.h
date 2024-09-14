#pragma once
#ifndef  _BOSS_HORNETSTATENODES_H_
#define _BOSS_HORNETSTATENODES_H_
#include"timer.h"
#include"stateNode.h"
class BossHornetAimState : public StateNode {
public:
	BossHornetAimState();
	~BossHornetAimState()=default;

	void onEnter() override;
	void onUpdate(float dt) override;

private:
	Timer timer;
};
class BossHornetDashInAirState : public StateNode {
public:
	BossHornetDashInAirState()=default;
	~BossHornetDashInAirState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;
	void onExit() override;
private:
	const float SPEED_DASH = 1500.0f;
};
class BossHornetDashOnFloorState : public StateNode {
public:
	BossHornetDashOnFloorState();
	~BossHornetDashOnFloorState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;

private:
	const float SPEED_DASH = 1000.0f;
private:
	Timer timer;
};
class BossHornetIdleState : public StateNode {
	public:
		BossHornetIdleState();
		~BossHornetIdleState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
		void onExit() override;
	private:
		Timer timer;
};
class BossHornetRunState : public StateNode {
	public:
		BossHornetRunState() = default;
		~BossHornetRunState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
		void onExit() override;
	private:
		const float MIN_DIS =350.0f;
		const float SPEED_RUN = 200.0f;
};
class BossHornetSquatState : public StateNode {
	public:
		BossHornetSquatState() ;
		~BossHornetSquatState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
private:
			Timer timer;
};
class BossHornetDashState : public StateNode {

};
class BossHornetThrowSilkState : public StateNode {
	public:
		BossHornetThrowSilkState() ;
		~BossHornetThrowSilkState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
		public:
			Timer timer;
};
class BossHornetThrowBarbState : public StateNode {
public:
	BossHornetThrowBarbState();
	~BossHornetThrowBarbState() = default;

	void onEnter() override;
	void onUpdate(float dt) override;

private:
	Timer timer;
};
class BossHornetThrowSwordState : public StateNode {
	public:
		BossHornetThrowSwordState();
		~BossHornetThrowSwordState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
private:
	Timer timerThrow;
	Timer timerSwitch;
};
//Ӳֱ״̬ʵ��
//class BossHornetHurtState : public StateNode {
//
//};
class BossHornetDeadState : public StateNode {
public :
	BossHornetDeadState()=default;
	~BossHornetDeadState() = default;

	void onEnter() override;
};
class BossHornetFallState : public StateNode {
	public:
		BossHornetFallState() = default;
		~BossHornetFallState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
};
class BossHornetJumpState : public StateNode {
	public:
		BossHornetJumpState() = default;
		~BossHornetJumpState() = default;

		void onEnter() override;
		void onUpdate(float dt) override;
private:
	const float SPEED_JUMP = 1000.0f;
};




#endif // ! _BOSS_HORNETSTATENODES_H_
