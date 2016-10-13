/*
 DragonBones latest support: http://www.cnblogs.com/relvin/p/5392591.html
*/
#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "EncryptManager.h"
#include "crypto-support/crypto_wrapper.h"

USING_NS_CC;

#define center_coord(__SZ__,__sz__,__achor__) ( ( (__SZ__) - (__sz__) + 2 * (__sz__) * (__achor__) ) * 0.5f )

static void centerNode(Node* pNode, const cocos2d::Size& parentSize)
{
	CC_ASSERT(pNode);

	cocos2d::Size size = pNode->getContentSize()/* * nodes_utility::getScale2D(pNode)*/;
	cocos2d::Point achor = Vec2::ZERO;
	if (!pNode->isIgnoreAnchorPointForPosition())
	{
		achor = pNode->getAnchorPoint();
	}
	pNode->setPosition(cocos2d::Vec2(center_coord(parentSize.width, size.width, achor.x),
		center_coord(parentSize.height, size.height, achor.y)));
}

static void centerNode(Node* pNode)
{
	Node* pNodeParent = pNode->getParent();
	if (pNodeParent != nullptr)
	{
		centerNode(pNode, pNodeParent->getContentSize());
	}
}

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

#if 0
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
#endif
	EncryptManager::getInstance()->setEncryptEnabled(true, "262381263");

    /////////////////////////////
    // 3. add your codes below...
	this->addChild(CSLoader::createNode("scene1.csb"));
	
#if 0
    // github.com/cocos2d/cocos2d-x issues: #16399 The latest Label calculate Size seems not correct with some .ttf font
    auto label = Label::createWithTTF("99999/99999", "fonts/arial.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height);

    // add the label as a child to this layer
    this->addChild(label, 1);

    // Draw the label border
    auto& labelContentSize = label->getContentSize();
    auto borderDraw = DrawNode::create();
    label->addChild(borderDraw);
    borderDraw->clear();
    borderDraw->setLineWidth(1);
    Vec2 vertices[4] =
    {
        Vec2::ZERO,
        Vec2(labelContentSize.width, 0),
        Vec2(labelContentSize.width, labelContentSize.height),
        Vec2(0, labelContentSize.height)
    };
    borderDraw->drawPoly(vertices, 4, true, Color4F::RED);
#endif

#if 0
    const auto dragonBonesData = _factory.loadDragonBonesData("SwordsMan/SwordsMan.json");
    _factory.loadTextureAtlasData("SwordsMan/texture.json");

    if (dragonBonesData)
    {
        const auto& armatureNames = dragonBonesData->getArmatureNames();
        const auto& armatureName = armatureNames[0];

        _armatureDisplay = _factory.buildArmatureDisplay(armatureName);

        _armatureDisplay->setPosition(480.f, 320.f);
        _armatureDisplay->setScale(1.0f);
        this->addChild(_armatureDisplay);

        _armatureDisplay->getAnimation().play("attack1");
    }
#endif
    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
