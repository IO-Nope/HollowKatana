#include"sword.h"
#include"collisionManager.h"
#include"resourcesManager.h"



Sword::Sword(const Vector2& position, bool moveLeft) {
#pragma region ��������ʼ��
	animation.setInterval(0.1f);
	animation.setLoop(true);
	animation.setAnchorMode(Animation::AnchorMode::Centered);
	animation.addframe(ResourcesManager::instance()->findAtlas(moveLeft? "swordLeft" : "swordRight"));
#pragma endregion 
#pragma region ��ײ���ʼ��
	collisionBox = CollisionManager::instance()->createBox();
	collisionBox->setLayerSrc(CollisionLayer::None);
	collisionBox->setLayerDst(CollisionLayer::Player);
	collisionBox->setSize({ 192,10 });
#pragma endregion
	this->position = position;
	this->velocity = {moveLeft? -SPEEDMOVE : SPEEDMOVE ,0};
	//TO DO:ʵ��һ��ƽ�����ƶ�? ���ԽԶԽ����
}

Sword::~Sword() {
	CollisionManager::instance()->destroyBox(collisionBox);
}

void Sword::onUpdate(float dt) {
	position += velocity * dt;
	//TO DO:ƽ���ƶ���
	animation.setPositon(position);
	collisionBox->setPosition(position);

	animation.onUpdate(dt);
	//TO DO:����Ƿ���Ч ���Ǻ�����߼���ʱ��Ҫ��д��
	if (position.x <= -200 || position.x > getwidth()+200) {
		isValid = false;
	}
}

void Sword::onRender() {
	animation.onRender();
}