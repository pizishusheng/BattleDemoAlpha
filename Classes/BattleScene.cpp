//
//  BattleScene.cpp
//  BattleDemo
//
//  Created by Tao on 16/7/12.
//
//

#include "BattleScene.hpp"
#include "BattleLayer.hpp"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

BattleScene* BattleScene::create()
{
    BattleScene* pRet = new BattleScene();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool BattleScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto layer = BattleLayer::create();
    this->addChild(layer, 0, 0);
    
    return true;
}