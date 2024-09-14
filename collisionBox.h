#pragma once
#ifndef _CLLISION_BOX_H_
#define _CLLISION_BOX_H_

#include"vector2.h"
#include"collisionLayer.h"
#include<functional>

class CollisionBox

{
	friend class CollisionManager;
	private:
		Vector2 size;
		Vector2 position;
		bool enabled = true;
		//TODO:��дһ�����Է�����ײ�Ķ����onCollide����
		std::function<void()> onCollide=nullptr;
		std::function<void(CollisionLayer)> onFixCollide=nullptr;
		//layerSrc�ܻ���
		CollisionLayer layerSrc = CollisionLayer::None;
		//layerDst������
		CollisionLayer layerDst = CollisionLayer::None;
		//TODO:���һ��onTrigger���� ���ڴ�����
	private:
		CollisionBox() = default;
		~CollisionBox() = default;
public:
	void setEnabled(bool flag) {
		this->enabled = flag;
	}
	void setLayerSrc(CollisionLayer layer) {
		this->layerSrc = layer;
	}
	void setLayerDst(CollisionLayer layer) {
		this->layerDst = layer;
	}
	void setOnCollide(std::function<void()> onCollide)
	{
		this->onCollide = onCollide;
	}
	void setSize(const Vector2& size) {
		this->size = size;
	}
	const Vector2& getSize() const {
		return this->size;
	}
	void setPosition(const Vector2& position) {
		this->position = position;
	}
	const Vector2& getPosition() const {
		return this->position;
	}
};




#endif // !_CLLISION_BOX_H_
