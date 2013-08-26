#include "HelloWorldScene.h"
#include "system.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
	
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer,1,1);

    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	this->setTouchEnabled(true);
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->schedule( schedule_selector(HelloWorld::update), 1);

	ITDObject* ptr = ITDGod::GetSingletonPtr()->Create( "Tower", "Tower" );

	this->addChild( ptr );

	if ( ptr )
	{
		ptr->setPosition( ccp(350, 250) );
	}

	CSystem::GetSingletonPtr()->Launch( "map.tmx", this );
	return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void HelloWorld::menuCloseCallbackUp(CCObject* pSender)
{
}

void HelloWorld::menuCloseCallbackDown(CCObject* pSender)
{
}

void HelloWorld::menuCloseCallbackLeft(CCObject* pSender)
{
}

void HelloWorld::menuCloseCallbackRigt(CCObject* pSender)
{
}

void HelloWorld::update( float ct )
{
	CSystem::GetSingletonPtr()->Update( this, ct );
}

