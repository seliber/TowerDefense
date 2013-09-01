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
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->setTouchEnabled(true);
	CSystem::GetSingletonPtr()->Launch( "map1\\" );
	CSystem::GetSingletonPtr()->Start( "1", this );
	

	return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint location = touch->getLocation();

	ITDObject* ptr = ITDGod::GetSingletonPtr()->Create( "Tower", this, "Tower" );

	if ( ptr )
	{    
		ptr->setPosition( location );
		ptr->setAI( IAiMgr::GetSingletonPtr()->GetAi( "Acttack" ) );
		ptr->scheduleUpdateWithPriority( 2 ); 
	}	
}


