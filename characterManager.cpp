#include"player.h"
#include"characterManager.h"
#include"bulletTimeManager.h"
#include"bossHornet.h"

CharacterManager* CharacterManager::manager = nullptr;
std::unordered_map<std::string, Character*> CharacterManager::characterPool;
CharacterManager* CharacterManager::instance(){
	if (manager == nullptr) {
		manager = new CharacterManager();

	}
	return manager;
}
void CharacterManager::onInput(const ExMessage& msg) {
	auto* player = CharacterManager::instance()->getCharacter("player");
	if(!player)
	{
		printf("player not found\n");
		return;
	}
	player->onInput(msg);
}
void CharacterManager::onUpdate(float dt) {
	auto* player = CharacterManager::instance()->getCharacter("player");
	auto* bossHornet = CharacterManager::instance()->getCharacter("bossHornet");
	if (!player)
	{
		printf("player not found\n");
		return;
	}
	if(!bossHornet)
	{
		printf("bossHornet not found\n");
		return;
	}
	player->onUpdate(dt);
	bossHornet->onUpdate(dt);
}
void CharacterManager::onRender() {
	auto* player = CharacterManager::instance()->getCharacter("player");
	auto* bossHornet = CharacterManager::instance()->getCharacter("bossHornet");
	if (!player)
	{
		printf("player not found\n");
		return;
	}
	if (!bossHornet)
	{
		printf("bossHornet not found\n");
		return;
	}
	bossHornet->onRender();
	BulletTimeManager::Instance()->postProcess();
	player->onRender();

}
CharacterManager::CharacterManager() {
	Character* player = new Player();
	Character* bossHornet = new BossHornet();
	characterPool["player"] = player;
	characterPool["bossHornet"] = bossHornet;
}
CharacterManager::~CharacterManager() {
	for (auto& it : characterPool) {
		delete it.second;
	}
	characterPool.clear();
}