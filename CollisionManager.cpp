#include"collisionManager.h"

#include<graphics.h>

const bool HitGroundEnabled = false;

CollisionManager* CollisionManager::manager = nullptr;
CollisionManager* CollisionManager::instance()
{
	if (manager == nullptr)
		manager = new CollisionManager();
	return manager;
}
CollisionManager::CollisionManager() = default;
CollisionManager::~CollisionManager() = default;
CollisionBox* CollisionManager::createBox()
{
	CollisionBox* box = new CollisionBox();
	collisionBoxList.push_back(box);
	return box;
}

void CollisionManager::destroyBox(CollisionBox* collisionBox)
{
	auto it = std::find(collisionBoxList.begin(), collisionBoxList.end(), collisionBox);
	if (it != collisionBoxList.end())
	{
		collisionBoxList.erase(it);
		delete collisionBox;
	}
}
//���Ż��汾
void CollisionManager::processCollide(){
	for (auto* collBoxSrc : collisionBoxList) {
		//�����ײ��û�����û���û��Ŀ���������
		if(!collBoxSrc->enabled||collBoxSrc->layerDst==CollisionLayer::None)
			continue;
		for(auto* collBoxDst : collisionBoxList)
		{
			//�����ײ��û�����û���û��Դ�����Դ���Ŀ�����ͬ����Դ���Ŀ��㲻ƥ��������
			//����voidmatrix���߼���:srcΪ�ܻ��� dstΪ������.����ײ��ֻ��SrcԴ��DstĿ��
			//�����ë����;��Ȼ������ײ�䶼����,����ֻ���ܻ���ײ��ᴥ��onCollide
			//�о�һ��ʺ
			if(!collBoxDst->enabled||collBoxSrc==collBoxDst||collBoxSrc->layerDst!=collBoxDst->layerSrc)
				continue;

			//������ײ����߼�
			bool isCollideX = abs(collBoxSrc->position.x - collBoxDst->position.x) < (collBoxSrc->size.x + collBoxDst->size.x) / 2;
			bool isCollideY = abs(collBoxSrc->position.y - collBoxDst->position.y) < (collBoxSrc->size.y + collBoxDst->size.y) / 2;

			if(isCollideX&&isCollideY)
			{
				if(collBoxDst->onCollide)
					collBoxDst->onCollide();
				if (collBoxDst->onFixCollide)
					collBoxDst->onFixCollide(collBoxSrc->layerDst);
			}
			
		}

	}
}
void CollisionManager::onDebugRender()
{
	for(auto* collBox : collisionBoxList)
	{
		setlinecolor(collBox->enabled? BLACK :RED);
		setlinestyle(PS_SOLID, 1);
		rectangle(
			collBox->position.x - collBox->size.x / 2,
			collBox->position.y - collBox->size.y / 2,
			collBox->position.x + collBox->size.x / 2,
			collBox->position.y + collBox->size.y / 2
		);
	}
}