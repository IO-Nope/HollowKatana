#pragma once
#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_

#include"character.h"
#include<unordered_map>
class CharacterManager {
public:
	static CharacterManager* instance();

	Character* getCharacter(const std::string& name) {
		auto it = characterPool.find(name);
		if (it != characterPool.end()) {
			return it->second;
		}
		return nullptr;
	}
	void onInput(const ExMessage& msg);
	void onUpdate(float dt);
	void onRender();

private:
	static std::unordered_map<std::string, Character*> characterPool;
	static CharacterManager* manager;
	//Character* player = nullptr;
private:
	CharacterManager() ;
	~CharacterManager() ;

};

#endif // !_CHARACTER_MANAGER_H_