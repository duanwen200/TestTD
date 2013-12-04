#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameWorldScene : public CCLayer
{
public:
	GameWorldScene(void);
	~GameWorldScene(void);

	virtual bool init();

	LAYER_CREATE_FUNC(GameWorldScene);

	static CCScene* scene();

	virtual void onEnter();
	virtual void onExit();

	// default implements are used to call script callback if exist
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);


	
	CCArray* towerBasicArray;
	void loadTowerBasic();
};

