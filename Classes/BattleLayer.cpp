//
//  BattleLayer.cpp
//  BattleDemo
//
//  Created by Tao on 16/7/14.
//
//

#include "BattleLayer.hpp"
#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "Modles/BaseMan.hpp"
#include <stdio.h>
USING_NS_CC;

using namespace cocostudio;
using namespace std;

BattleLayer::BattleLayer()
{
}

BattleLayer::~BattleLayer()
{
    
}

BattleLayer* BattleLayer::create()
{
    BattleLayer *pRet = new BattleLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool BattleLayer::init()
{
    if (!Layer::init())
        return false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battlescene_grassland.plist");
    
    //auto bg = Sprite::createWithSpriteFrameName("battle_bg.png");
    auto bg = Sprite::create("battlescene_grassland.png");
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                         origin.y + visibleSize.height/2));
    this->addChild(bg, 0, 0);
    
    initHero();
    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_0(BattleLayer::changeHeroState, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void BattleLayer::initHero()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    string path = "hero/hero1001_output/hero1001";
    m_hero = BaseMan::createWithFile(path);
    m_hero->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(m_hero, 99);
}

void BattleLayer::changeHeroState()
{
    m_hero->setActionState(ACTION_WALK);
}