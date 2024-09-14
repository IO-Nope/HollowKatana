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
//非优化版本
void CollisionManager::processCollide(){
	for (auto* collBoxSrc : collisionBoxList) {
		//如果碰撞盒没有启用或者没有目标层则跳过
		if(!collBoxSrc->enabled||collBoxSrc->layerDst==CollisionLayer::None)
			continue;
		for(auto* collBoxDst : collisionBoxList)
		{
			//如果碰撞盒没有启用或者没有源层或者源层和目标层相同或者源层和目标层不匹配则跳过
			//这里voidmatrix的逻辑是:src为受击层 dst为攻击层.而碰撞箱只有Src源和Dst目标
			//这里的毛病是;虽然所有碰撞箱都会检测,但是只有受击碰撞箱会触发onCollide
			//感觉一坨屎
			if(!collBoxDst->enabled||collBoxSrc==collBoxDst||collBoxSrc->layerDst!=collBoxDst->layerSrc)
				continue;

			//矩形碰撞检测逻辑
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