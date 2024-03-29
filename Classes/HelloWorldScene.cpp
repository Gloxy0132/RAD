/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Monster.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void HelloWorld::MakeMonster()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MonsterArray.pushBack(Sprite::create("Ork.png"));
	auto* animation2 = CCAnimation::create();
	MonsterArray.back()->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 7) * 3 + origin.y));
	MonsterArray.back()->setAnchorPoint(CCPoint(0.5, -2));
	this->addChild(MonsterArray.back(), 2);
	MonsterArray.back()->setScale(3, 3);
	animation2->setDelayPerUnit(0.2f);
	animation2->addSpriteFrameWithFileName("Ork_Move1.png");
	animation2->addSpriteFrameWithFileName("Ork.png");
	animation2->addSpriteFrameWithFileName("Ork_Move2.png");
	animation2->addSpriteFrameWithFileName("Ork.png"); 
	MonsterArray.back()->runAction(RepeatForever::create(CCAnimate::create(animation2)));
	MonsterArray.back()->runAction(RepeatForever::create(RotateBy::create(1, -40)));
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Map.png");
    if (sprite == nullptr)
    {
        problemLoading("'Map.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, (visibleSize.height/7)*3 + origin.y));
		sprite->setScale(7,7);
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	auto Char = Sprite::create("Char.png");
	Char->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 7) * 3 + origin.y));
	Char->setScale(5, 5);
	this->addChild(Char, 2);
	auto Weapon = Sprite::create("Weapon.png");
	Weapon->setAnchorPoint(CCPoint(0,0));
	Weapon->setPosition(Vec2(0,2));
	Char->addChild(Weapon, 1);
	auto* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrameWithFileName("Weapon_Attack1.png");
	animation->addSpriteFrameWithFileName("Weapon_Attack2.png");
	animation->addSpriteFrameWithFileName("Weapon.png");
	HelloWorld::MakeMonster();
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
