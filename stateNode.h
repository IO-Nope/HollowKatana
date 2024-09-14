#pragma once
#ifndef _STATENODE_H_
#define _STATENODE_H_

class StateNode
{
public:
	StateNode()=default;
	~StateNode()=default;

	virtual void onEnter() {}
	virtual void onUpdate(float dt) {}
	virtual void onExit() {}
};


#endif // !_STATENODE_H_
