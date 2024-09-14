#include"bulletTimeManager.h"

#include<graphics.h>

BulletTimeManager* BulletTimeManager::manager = nullptr;

BulletTimeManager::BulletTimeManager()=default;

BulletTimeManager::~BulletTimeManager()=default;

BulletTimeManager* BulletTimeManager::Instance()
{
	if (manager == nullptr)
	{
		manager = new BulletTimeManager();
	}
	return manager;
}

void BulletTimeManager::postProcess()
{
	DWORD* buffer = (DWORD*)GetImageBuffer();
	int w = getwidth();
	int h = getheight();

	for(int y = 0; y < h; y++)
	{
		for(int x = 0; x < w; x++)
		{
			DWORD color = buffer[y * w + x];
			DWORD r = (BYTE)(GetBValue(color)*lerp(1.0f,DST_COLOR_FACTOR,progress));
			DWORD g = (BYTE)(GetGValue(color)*lerp(1.0f,DST_COLOR_FACTOR,progress));
			DWORD b = (BYTE)(GetRValue(color)*lerp(1.0f,DST_COLOR_FACTOR,progress));

			buffer[y * w + x] = BGR(RGB(r, g, b)|(((DWORD)(BYTE)(255)))<<24);
		}
	}

}

void BulletTimeManager::setStatus(Status status)
{
	this->status = status;
}


float BulletTimeManager::onUpdate(float dt)
{
	float deltaProgress = SPEED_PROCESS * dt;
	progress += deltaProgress * (status == Status::Entering ? 1 : -1);

	if (progress < 0)
	{
		progress = 0;
	}
	if(progress > 1.0f)
	{
		progress = 1.0f;
	}
	return dt * lerp(1.0f, DST_DELTA_FACTOR, progress);
}
