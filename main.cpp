#include<graphics.h>
#include<chrono>
#include<thread>
#include<string>
#include<iostream>

#include"resourcesManager.h"
#include"util.h"
#include"collisionManager.h"
#include"characterManager.h"
#include"bulletTimeManager.h"


static void drawBackground() {
	static IMAGE* background = ResourcesManager::instance()->findImage("background");
	static Rect rectDust = {
		(getwidth() - background->getwidth()) / 2,
		(getheight() - background->getheight()) / 2,
		background->getwidth(),
		background->getheight()
	};
	putImageEx(background, &rectDust);
}
static void drawRemainHp() {
	static IMAGE* uiHp = ResourcesManager::instance()->findImage("uiHeart");
	Rect rectDst = { 0,10,uiHp->getwidth(),uiHp->getheight() };
	for (int i = 0; i < CharacterManager::instance()->getCharacter("player")->getHp(); i++) {
		rectDst.x = 10 + i * 40;
		putImageEx(uiHp, &rectDst);
		} 
	}
int debugMain();
int main(int argc,char** argv) {
	using namespace std::chrono;
	//����ͼ��
	HWND hwnd = initgraph(1280,720,  EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("HollowKatana"));
#pragma region ��ʼ����Դ
	try {
		ResourcesManager::instance()->load();
	}
	catch (LPCTSTR id){
		//��Դ����ʧ��
		TCHAR errMsg[256];
		_stprintf_s(errMsg, _T("��Դ����ʧ��:%s"), id);
		MessageBox(hwnd, errMsg, _T("��Դ����ʧ��"), MB_OK|MB_ICONERROR);
		return -1;
	
	}
	catch (std::string msg) {
		//��Դ����ʧ��
		std::wstring wmsg(msg.begin(), msg.end());
		TCHAR errMsg[256];
		_stprintf_s(errMsg, _T("��Դ����ʧ��:%s"), wmsg.c_str());
		MessageBox(hwnd, _T("��Դ����ʧ��,������Ϣ:"), errMsg, MB_OK | MB_ICONERROR);
		return -1;
	}
	catch (std::wstring msg) {
		//��Դ����ʧ��
		MessageBox(hwnd, _T("��Դ����ʧ��,������Ϣ:"), msg.c_str(), MB_OK | MB_ICONERROR);
		
	}
#pragma endregion
	playAudio(_T("bgm"), true);
	//��ʱ����
	const nanoseconds frameDuration(1000000000 / 90);
	steady_clock::time_point lastTick = steady_clock::now();
	
	/*debugMain();
	return 0;*/

	ExMessage msg;
	bool isQuit = false;
	setbkcolor(RGB(0, 0, 0));
	BeginBatchDraw();
	//��ѭ��
	int fpscont = 0;
	Timer fpsTimer = Timer();
	fpsTimer.setOneShot(false);
	fpsTimer.setWaitTime(1.0f);
	fpsTimer.setOnTimeOut([&]() {
		TCHAR fps[256];
		_stprintf_s(fps, _T("FPS:%d"), fpscont);
		SetWindowText(hwnd, fps);
		fpscont = 0;
	});

	while(!isQuit) {
		while (peekmessage(&msg)){
			CharacterManager::instance()->onInput(msg);
		}
		steady_clock::time_point frameStart = steady_clock::now();
		duration<float> deltaTime = duration<float>(frameStart - lastTick);

		float scaledDt = BulletTimeManager::Instance()->onUpdate(deltaTime.count());
		CharacterManager::instance()->onUpdate(scaledDt);
		CollisionManager::instance()->processCollide();

		fpscont++;
		fpsTimer.onUpdate(deltaTime.count());

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		drawBackground();
		CharacterManager::instance()->onRender();
		CollisionManager::instance()->onDebugRender();
		drawRemainHp();
		FlushBatchDraw();
		
		lastTick = frameStart;
		
		nanoseconds sleepDuration = frameDuration - (steady_clock::now() - frameStart);
		if (sleepDuration > 0ns) {
			std::this_thread::sleep_for(sleepDuration);
		}

	}

	EndBatchDraw();

	return 0;
}

int debugMain() {
	using namespace std::chrono;
	std::string cmd;
	std::cin >> cmd;
	while(cmd!="exit") {
		std::wstring wcmd(cmd.begin(), cmd.end());
		steady_clock::time_point frameStart = steady_clock::now();
		playAudio(wcmd.c_str(), false);
		printf("������Ƶ:%s\n", cmd.c_str());
		duration<float> deltaTime = duration<float>(steady_clock::now() - frameStart);
		printf("������Ƶ��ʱ:%f\n", deltaTime.count());
		std::cin >> cmd;
	}
	return 0;
}