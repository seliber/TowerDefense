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
CCSprite* p;
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

	p = CCSprite::create("2.png");
	this->addChild(p);

	CCRepeatForever* pAction = CCRepeatForever::create( CCSequence::create( CCMoveTo::create(5,ccp(200,200)), CCMoveTo::create(5,ccp(0,0)),NULL ) ) ;

	pAction->setTag( 0 );
	p->runAction( pAction );


	return true;
}

US_TD
void CBegin::menuCloseCallback(CCObject* pSender)
{
	CCSpeed* action = CCSpeed::create( (CCRepeatForever*)p->getActionByTag(0), 5 );

	p->runAction( action );

	//CCDirector::sharedDirector()->pushScene( HelloWorld::scene() );
}

void CBegin::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	int a = 0;
}
