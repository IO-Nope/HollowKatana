#include"stateMachine.h"
StateMachine::StateMachine()=default;
StateMachine::~StateMachine()=default;

void StateMachine::onUpdate(float dt)
{
	if (!currentState)return;
	if (needInit)
	{
		currentState->onEnter();
		needInit = false;
	}
	currentState->onUpdate(dt);
}

void StateMachine::setEntry(const std::string& id)
{
	if (statePool.find(id) == statePool.end()) {
		printf("onEntry state not found:%s",id.c_str());
		return;
	}
	currentState = statePool[id];
	//needInit = true;
}

void StateMachine::switchTo(const std::string& id)
{
	if (statePool.find(id) == statePool.end()) {
		printf("swtichTo state not found:%s",id.c_str());
		return;
	}
	if (currentState)currentState->onExit();
	currentState = statePool[id];
	if(currentState)currentState->onEnter();
	//needInit = true;
}
void StateMachine::registerState(const std::string& id, StateNode* state)
{
	if (statePool.find(id) != statePool.end()) {
		printf("registerState state already exist:%s",id.c_str());
		return;
	}
	statePool[id] = state;
}