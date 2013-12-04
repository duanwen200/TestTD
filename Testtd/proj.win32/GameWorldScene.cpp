#include "GameWorldScene.h"
#define  ZORDER_4_TOWER_BASE 11

GameWorldScene::GameWorldScene(void)
{
	towerBasicArray = CCArray::create();
	CC_SAFE_RETAIN(towerBasicArray);
}


GameWorldScene::~GameWorldScene(void)
{
	CC_SAFE_RELEASE_NULL(towerBasicArray);
}


CCScene* GameWorldScene::scene()
{
	CCScene* sc = CCScene::create();

	sc->addChild(GameWorldScene::create());
	return sc;
}

bool GameWorldScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}


	CCSprite* m_pBgSprite = CCSprite::create("res/bg.png");
	this->addChild(m_pBgSprite,-1);
	m_pBgSprite->setAnchorPoint(CCPointZero);

	loadTowerBasic();
	setTouchEnabled(true);
	return true;
}

 void  GameWorldScene::onEnter()
{
	CCLayer::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}
 void  GameWorldScene::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

// default implements are used to call script callback if exist
bool  GameWorldScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

	CCObject* obj = NULL;

	CCARRAY_FOREACH(towerBasicArray,obj)
	{
		CCSprite* base = (CCSprite*)obj;
		CCPoint touchPoint1 = pTouch->locationInView();
		CCPoint touchPoint = CCNode::convertTouchToNodeSpace(pTouch);
		if (CCRect::CCRectContainsPoint(base->boundingBox(),touchPoint))
		{
			if (!base->getUserData())
			{
				CCSprite* tower = CCSprite::create("res/tower.png");
				tower->setPosition(base->getPosition());

				this->addChild(tower,base->getZOrder() + 1);

				base->setUserData(tower);
				break;
			}
		}
		
		
	}
	return true;
}
void GameWorldScene::loadTowerBasic()
{
	CCArray* array = CCArray::createWithContentsOfFileThreadSafe("res/TowersPosition.plist");

	CCObject* obj = NULL;

	CCARRAY_FOREACH(array,obj)
	{
		CCDictionary* dic = (CCDictionary*)obj;

		 CCString* xStr = (CCString*)dic->valueForKey("x");
		 CCString* yStr = (CCString*)dic->valueForKey("y");

		float x = xStr->floatValue();
		float y = yStr->floatValue();
		
		CCPoint p = ccp(x,y);

		CCSprite* base = CCSprite::create("res/open_spot.png");
		this->addChild(base,ZORDER_4_TOWER_BASE);

		base->setPosition(p);

		towerBasicArray->addObject(base);
	}
}