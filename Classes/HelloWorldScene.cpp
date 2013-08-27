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
	//CCDirector::sharedDirector()->getOpenGLView()->SetWin32KeyLayer(this);
	
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->setTouchEnabled(true);

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
	int a = 0;
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	int a = 0;
}

void HelloWorld::update( float ct )
{
	CSystem::GetSingletonPtr()->Update( this, ct );
}

