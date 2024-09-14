#pragma once
#ifndef _BULLET_TIME_MANAGER_H_
#define _BULLET_TIME_MANAGER_H_

class BulletTimeManager
{
public:
	enum class Status {
		Entering,
		Exiting
	};
public:
	static BulletTimeManager* Instance();

	void postProcess();
	void setStatus(Status status);

	float onUpdate(float dt);
private:
	static BulletTimeManager* manager;
private:
	float progress = 0;
	Status status = Status::Exiting;
	const float SPEED_PROCESS = 2.0f;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;
public:
	BulletTimeManager();
	~BulletTimeManager();

	float lerp(float start, float end, float t) {
				return start + t * (end - start);
	}
};



#endif // !_BULLET_TIME_MANAGER_H_
