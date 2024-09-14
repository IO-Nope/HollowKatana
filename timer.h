#pragma once
#ifndef _TIMER_H
#define _TIMER_H
#include<functional>
class Timer
{
private:
	float passTime = 0;
	float waitTime = 0;
	bool shotted = false;
	bool pause = false;
	bool oneShot = false;
	std::function<void()> onTimeOut;
public:
	Timer() = default;
	~Timer() = default;
	void restart()
	{
		passTime = 0;
		shotted = false;
	}

	void setWaitTime(float waitTime)
	{
		this->waitTime = waitTime;
	}
	
	void setOneShot(bool flag)
	{
		oneShot = flag;
	}

	void setOnTimeOut(std::function<void()> oTO)
	{
		this->onTimeOut = oTO;
	}
	void resume() {
		this->pause = true;
	}
	void onUpdate(float delta) {
		if(pause)
			return;
		passTime += delta;
		if(passTime >= waitTime)
		{
			bool canShot = (!oneShot ) || (oneShot&&!shotted);
			shotted = true;
			if (canShot && onTimeOut)
				onTimeOut();
			passTime -= waitTime;
		}
	}
};
#endif // !_TIMER_H