#pragma once
#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include"stateNode.h"

#include<string>
#include<graphics.h>
#include<unordered_map>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void onUpdate(float dt);

	void setEntry(const std::string& id);
	void switchTo(const std::string& id);
	void registerState(const std::string& id, StateNode* state);

private:
	bool needInit = true;
	StateNode* currentState = nullptr;
	std::unordered_map<std::string, StateNode*> statePool;

};


#endif // !_STATEMACHINE_H_