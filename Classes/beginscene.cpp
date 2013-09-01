#include "beginscene.h"
#include "constdef.h"
#include "scenemgr.h"
#include "system.h"
#include "HelloWorldScene.h"
USING_NS_CC;


CCScene* CBegin::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CBegin *layer = CBegin::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
class CTest : public CCSprite{
public:
	void update(float dt){
		this->removeFromParentAndCleanup( true );
	}
};

// on "init" you need to initialize your instance
bool CBegin::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->setTouchEnabled( true );
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(CBegin::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label


	CCLabelTTF* pLabel = CCLabelTTF::create("Tower Defense", "Arial", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("enemy.plist");
//	CCSprite* pSprite = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("filename_1.png"));

// 	CCAnimation* animation = CCAnimation::create();
// 	for ( int i = 1; i < 19; i++ )
// 	{
// 		char szName[100] = {0};
// 		sprintf(szName, "filename_%d.png", i);
// 		animation->addSpriteFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName));
// 	}
// 
// 	pSprite->setPosition( ccp(200,200) );
// 	// should last 2.8 seconds. And there are 14 frames.
// 	animation->setDelayPerUnit(0.1);
// 	animation->setRestoreOriginalFrame(true);
// 
// 	CCAnimate* action = CCAnimate::create(animation);
// // 	CCCardinalSplineTo *action2;
// // 
// // 	CCCardinalSplineTo* reverse2 = (CCCardinalSplineTo*)action2->reverse();		
// 	pSprite->runAction( CCRepeatForever::create( action ) );

	//this->addChild( pSprite );
	return true;
}

US_TD
void CBegin::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pushScene( HelloWorld::scene() );
}

void CBegin::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	int a = 0;
}
