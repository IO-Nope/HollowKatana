#include"sword.h"
#include"collisionManager.h"
#include"resourcesManager.h"



Sword::Sword(const Vector2& position, bool moveLeft) {
#pragma region 剑动画初始化
	animation.setInterval(0.1f);
	animation.setLoop(true);
	animation.setAnchorMode(Animation::AnchorMode::Centered);
	animation.addframe(ResourcesManager::instance()->findAtlas(moveLeft? "swordLeft" : "swordRight"));
#pragma endregion 
#pragma region 碰撞箱初始化
	collisionBox = CollisionManager::instance()->createBox();
	collisionBox->setLayerSrc(CollisionLayer::None);
	collisionBox->setLayerDst(CollisionLayer::Player);
	collisionBox->setSize({ 192,10 });
#pragma endregion
	this->position = position;
	this->velocity = {moveLeft? -SPEEDMOVE : SPEEDMOVE ,0};
	//TO DO:实现一个平滑的移动? 离得越远越慢？
}

Sword::~Sword() {
	CollisionManager::instance()->destroyBox(collisionBox);
}

void Sword::onUpdate(float dt) {
	position += velocity * dt;
	//TO DO:平滑移动！
	animation.setPositon(position);
	collisionBox->setPosition(position);

	animation.onUpdate(dt);
	//TO DO:检测是否有效 但是后面改逻辑的时候要重写！
	if (position.x <= -200 || position.x > getwidth()+200) {
		isValid = false;
	}
}

void Sword::onRender() {
	animation.onRender();
}