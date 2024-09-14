
#include<string>

#include"resourcesManager.h"
/// <summary>
/// 图片信息
/// </summary>
struct ImageResInfo
{
	std::string id;
	LPCTSTR path;
};
/// <summary>
/// 图集信息
/// </summary>
struct AtlasResInfo
{
	std::string id;
	LPCTSTR path;
	int numFrame = 0;
};
ResourcesManager* ResourcesManager::manager = nullptr;
ResourcesManager* ResourcesManager::instance()
{
	if (manager == nullptr)
		manager = new ResourcesManager();
	return manager;
}
ResourcesManager::ResourcesManager() = default;
ResourcesManager::~ResourcesManager() = default;
/// <summary>
/// 要加载的图片信息,名称-路径
/// </summary>
static const std::vector<ImageResInfo> imageInfoList =
{
	{"background",_T(R"(resources\background.png)")},
	{"uiHeart",_T(R"(resources\ui_heart.png)")},
	
	{"playerAttackRight",_T(R"(resources\player\attack.png)")},
	{"playerDeadRight",_T(R"(resources\player\dead.png)")},
	{"playerFallRight",_T(R"(resources\player\fall.png)")},
	{"playerIdleRight",_T(R"(resources\player\Idle.png)")},
	{"playerJumpRight",_T(R"(resources\player\jump.png)")},
	{"playerRunRight",_T(R"(resources\player\run.png)")},
	{"playerRollRight",_T(R"(resources\player\roll.png)")},

	{"playerVfxAttackDown",_T(R"(resources\player\vfx_attack_down.png)")},
	{"playerVfxAttackLeft",_T(R"(resources\player\vfx_attack_left.png)")},
	{"playerVfxAttackRight",_T(R"(resources\player\vfx_attack_right.png)")},
	{"playerVfxAttackUp",_T(R"(resources\player\vfx_attack_up.png)")},
	{"playerVfxJump",_T(R"(resources\player\vfx_jump.png)")},
	{"playerVfxLand",_T(R"(resources\player\vfx_land.png)")},
};
/// <summary>
/// 要加载的图集信息,名称-路径-帧数
/// </summary>
static const std::vector<AtlasResInfo> atlasInfoList =
{
	{"barbBreak",_T(R"(resources\hornet\barb_break\%d.png)"),3},
	{"barbLoose",_T(R"(resources\hornet\barb_loose\%d.png)"),5},
	{"silk",_T(R"(resources\hornet\silk\%d.png)"),	9},
	{"swordLeft",_T(R"(resources\hornet\sword\%d.png)"),3},
	
	{"hornetAimLeft",_T(R"(resources\hornet\aim\%d.png)"),9},
	{"hornetDashInAirLeft",_T(R"(resources\hornet\dash_in_air\%d.png)"),2},
	{"hornetDashOnFloorLeft",_T(R"(resources\hornet\dash_on_floor\%d.png)"),2},
	{"hornetFallLeft",_T(R"(resources\hornet\fall\%d.png)"),4},
	{"hornetIdleLeft",_T(R"(resources\hornet\idle\%d.png)"),6},
	{"hornetJumpLeft",_T(R"(resources\hornet\jump\%d.png)"),8},
	{"hornetRunLeft",_T(R"(resources\hornet\run\%d.png)"),8},
	{"hornetSquatLeft",_T(R"(resources\hornet\squat\%d.png)"),10},
	{"hornetThrowBarbLeft",_T(R"(resources\hornet\throw_barb\%d.png)"),8},
	{"hornetThrowSilkLeft",_T(R"(resources\hornet\throw_silk\%d.png)"),17},
	{"hornetThrowSwordLeft",_T(R"(resources\hornet\throw_sword\%d.png)"),16},

	{"hornetVfxDashInAirLeft",_T(R"(resources\hornet\vfx_dash_in_air\%d.png)"),5},
	{"hornetVfxDashOnFloorLeft",_T(R"(resources\hornet\vfx_dash_on_floor\%d.png)"),6},
};


static inline bool checkImageValid(IMAGE* image)
{
	return GetImageBuffer(image); //这里使用了更有语义的写法 实际上return空指针的时候也自动变成false了
}

void ResourcesManager::load() 
{
	//加载图片
	for (const auto& info : imageInfoList) {
		IMAGE* tempImage = new IMAGE();
		loadimage(tempImage, info.path);
		if(!checkImageValid(tempImage))
		{
			delete tempImage;
			throw info.path;
		}
		else {
			ResourcesManager::imagePool[info.id] = tempImage;
			//printf("load image %s\n size: %d %d", info.id.c_str(), tempImage->getheight(),tempImage->getwidth());
		}
	}
	//加载图集
	for (const auto& info : atlasInfoList) {
		Atlas* tempAtlas = new Atlas();
		tempAtlas->load(info.path, info.numFrame);
		for(int i = 0; i < tempAtlas->getSize(); i++)
		{
			if(!checkImageValid(tempAtlas->getImage(i)))
			{
				delete tempAtlas;
				throw info.path;
			}
		}
		ResourcesManager::atlasPool[info.id] = tempAtlas;
		//printf("load atlas %s\n", info.id.c_str());
	}
#pragma region 翻转资源
	flipImage("playerAttackRight", "playerAttackLeft",5);
	flipImage("playerDeadRight", "playerDeadLeft",6);
	flipImage("playerFallRight", "playerFallLeft",5);
	flipImage("playerIdleRight", "playerIdleLeft",5);
	flipImage("playerRunRight", "playerRunLeft",10);
	flipImage("playerRollRight", "playerRollLeft",7);
	flipImage("playerJumpRight", "playerJumpLeft", 5);

	flipAtlas("swordLeft", "swordRight");
	flipAtlas("hornetAimLeft", "hornetAimRight");
	flipAtlas("hornetDashInAirLeft", "hornetDashInAirRight");
	flipAtlas("hornetDashOnFloorLeft", "hornetDashOnFloorRight");
	flipAtlas("hornetFallLeft", "hornetFallRight");
	flipAtlas("hornetIdleLeft", "hornetIdleRight");
	flipAtlas("hornetJumpLeft", "hornetJumpRight");
	flipAtlas("hornetRunLeft", "hornetRunRight");
	flipAtlas("hornetSquatLeft", "hornetSquatRight");
	flipAtlas("hornetThrowBarbLeft", "hornetThrowBarbRight");
	flipAtlas("hornetThrowSilkLeft", "hornetThrowSilkRight");
	flipAtlas("hornetThrowSwordLeft", "hornetThrowSwordRight");

	flipAtlas("hornetVfxDashInAirLeft", "hornetVfxDashInAirRight");
	flipAtlas("hornetVfxDashOnFloorLeft", "hornetVfxDashOnFloorRight");
#pragma endregion
#pragma region 音频资源

	loadAudio(_T(R"(resources\audio\bgm.mp3)"), _T("bgm"));
	loadAudio(_T(R"(resources\audio\barb_break.mp3)"), _T("barbBreak"));
	loadAudio(_T(R"(resources\audio\bullet_time.mp3)"), _T("bulletTime"));

	loadAudio(_T(R"(resources\audio\hornet_dash.mp3)"), _T("hornetDash"));
	loadAudio(_T(R"(resources\audio\hornet_run.mp3)"), _T("hornetRun"));
	loadAudio(_T(R"(resources\audio\hornet_hurt_1.mp3)"), _T("hornetHurt1"));
	loadAudio(_T(R"(resources\audio\hornet_hurt_2.mp3)"), _T("hornetHurt2"));
	loadAudio(_T(R"(resources\audio\hornet_hurt_3.mp3)"), _T("horneturt3"));
	loadAudio(_T(R"(resources\audio\throw_barbs.mp3)"), _T("hornetThrowBarbs"));
	loadAudio(_T(R"(resources\audio\throw_silk.mp3)"), _T("hornetThrowSilk"));
	loadAudio(_T(R"(resources\audio\throw_sword.mp3)"), _T("hornetThrowSword"));

	loadAudio(_T(R"(resources\audio\player_attack_1.mp3)"), _T("playerAttack1"));
	loadAudio(_T(R"(resources\audio\player_attack_2.mp3)"), _T("playerAttack2"));
	loadAudio(_T(R"(resources\audio\player_attack_3.mp3)"), _T("playerAttack3"));
	loadAudio(_T(R"(resources\audio\player_dead.mp3)"), _T("playerDead"));
	loadAudio(_T(R"(resources\audio\player_hurt.mp3)"), _T("playerHurt"));
	loadAudio(_T(R"(resources\audio\player_jump.mp3)"), _T("playerJump"));
	loadAudio(_T(R"(resources\audio\player_land.mp3)"), _T("playerLand"));
	loadAudio(_T(R"(resources\audio\player_roll.mp3)"), _T("playerRoll"));
	loadAudio(_T(R"(resources\audio\player_run.mp3)"), _T("playerRun"));

#pragma endregion
}
void ResourcesManager::loadAuto() {

}
Atlas* ResourcesManager::findAtlas(const std::string& id) const {
	const auto iter = ResourcesManager::atlasPool.find(id);
	if (iter == ResourcesManager::atlasPool.end())
		return nullptr;
	return iter->second;
}
IMAGE* ResourcesManager::findImage(const std::string& id) const {
	const auto iter = ResourcesManager::imagePool.find(id);
	if (iter == ResourcesManager::imagePool.end())
		if (iter->first!=id)
		{
			printf("find image %s failed\n", id.c_str());
			return nullptr;
		}
	return iter->second;
}
void ResourcesManager::flipImage(IMAGE* srcImage, IMAGE* dstImage, int numH) {
	int w = srcImage->getwidth();
	int h = srcImage->getheight();
	int wFrame = w / numH;
	Resize(dstImage, w, h);
	DWORD* srcBuffer = GetImageBuffer(srcImage);
	DWORD* dstBuffer = GetImageBuffer(dstImage);
	for (int i = 0; i < numH; i++) {
		int xleft = i * wFrame;
		int xright = (i + 1) * wFrame - 1;
		for (int y = 0; y < h; y++) {
			for (int x = xleft; x <= xright; x++) {
				int idxSrc = y * w + x;
				int idxDst = y * w + xright - (x - xleft);
				dstBuffer[idxDst] = srcBuffer[idxSrc];
			}
		}
	}
}
void ResourcesManager::flipImage(const std::string& srcId, const std::string& dstId, int numH) {
	IMAGE* srcImage = findImage(srcId);
	if (srcImage == nullptr)
		throw srcId;
	IMAGE* dstImage = new IMAGE();

	flipImage(srcImage, dstImage, numH);

	imagePool[dstId] = dstImage;
}
void ResourcesManager::flipAtlas(const std::string& srcId, const std::string& dstId) {
	Atlas* srcAtlas = findAtlas(srcId);
	if (srcAtlas == nullptr)
		throw srcId;
	Atlas* dstAtlas = new Atlas();
	for(int i = 0; i < srcAtlas->getSize(); i++)
	{
		IMAGE* srcImage = srcAtlas->getImage(i);
		IMAGE dstImage;
		flipImage(srcImage, &dstImage);
		dstAtlas->addImage(dstImage);
	}
	atlasPool[dstId] = dstAtlas;

}