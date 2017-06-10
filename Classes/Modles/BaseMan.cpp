//
//  BaseMan.cpp
//  BattleDemo
//
//  Created by Tao on 16/7/19.
//
//

#include "BaseMan.hpp"
#include "editor-support/cocostudio/CCArmatureDataManager.h"

using namespace cocos2d;

BaseMan::BaseMan()
:m_state(ACTION_IDLE),
m_isPlayState(1),
m_attackTarget(nullptr)
{
}

BaseMan::~BaseMan()
{
    log("BaseMan constructor");
}

BaseMan* BaseMan::createWithFile(std::string filePath, string fileArmature)
{
    BaseMan *pRet = new BaseMan();
    if (pRet && pRet->initWithFile(filePath, fileArmature)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BaseMan::initWithFile(std::string filePath, string fileArmature)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo(filePath+".png", filePath+".plist", filePath+".xml");
    m_armature = Armature::create(fileArmature);
    m_armature->getAnimation()->setSpeedScale(0.7f);
    this->addChild(m_armature);
    this->setContentSize(m_armature->getContentSize());
    return true;
}

void BaseMan::setPositionss(const cocos2d::Vec2 &position)
{
    if (m_armature == nullptr)
        return;
    setPosition(position);
    //m_armature->setPosition(position);
}

void BaseMan::setActionState(ActionState state)
{
    m_state = state;
}

Armature* BaseMan::getArmature()
{
    return m_armature == nullptr? nullptr : m_armature;
}

void BaseMan::playAnimationByActionState(ActionState state)
{
    if (m_armature == nullptr && m_armature->getAnimation() == nullptr)
        return;
    
    if (state == m_isPlayState)
        return;
    
    switch (state) {
        case ACTION_IDLE:
        {
            m_armature->getAnimation()->play("idle", -1, 1);
            m_isPlayState = state;
        }
            break;
        case ACTION_WALK:
        {
            m_armature->getAnimation()->play("walk", -1, 1);
            actionWalk();
            m_isPlayState = state;
        }
            break;
        case ACTION_ATTACK:
        {
            m_armature->getAnimation()->play("attack");
            m_state = ACTION_IDLE;
            m_isPlayState = ACTION_IDLE;
        }
            break;
        case ACTION_SKILL:
        {
            m_armature->getAnimation()->play("skill");
            m_state = ACTION_IDLE;
            m_isPlayState = ACTION_IDLE;
        }
            break;
        case ACTION_GET_HURT:
        {
            m_armature->getAnimation()->play("gethurt");
            m_state = ACTION_IDLE;
            m_isPlayState = ACTION_IDLE;
        }
            break;
        default:
            break;
    }
}

void BaseMan::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}

void BaseMan::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}

void BaseMan::update(float dt)
{
    playAnimationByActionState(m_state);
}

void BaseMan::actionWalk()
{
    if (m_attackTarget == nullptr)
        return;
    
    auto move = MoveTo::create(3.0f, Vec2(m_attackTarget->getPositionX(), m_attackTarget->getPositionY()));
    auto callback = CallFunc::create([&](){
        m_state = ACTION_ATTACK;
    });
    this->runAction(Sequence::create(move, callback,NULL));
}

void BaseMan::updatePosition()
{
    if (checkIsPengzhuang()) {
        this->stopAllActions();
        m_state =ACTION_ATTACK;
    }
}

void BaseMan::actionAttack()
{
    
}

void BaseMan::checkAttackTarget(vector<BaseMan *> targetVector)
{
    if (m_attackTarget != nullptr) 
        return;
    
    float min_distance = -1;
    BaseMan *temp_target = nullptr;
    for (auto target: targetVector)
    {
        float x = abs(target->getPositionX() - this->getPositionX());
        float y = abs(target->getPositionY() - this->getPositionY());
        float powx = pow(x, 2);
        float powy = pow(y, 2);
        float distance = sqrt(powx + powy);
        
        if (min_distance == -1){
            min_distance = distance;
            temp_target = target;
            continue;
        }
        
        if (distance < min_distance)
        {
            min_distance = distance;
            temp_target = target;
        }
    }
    m_attackTarget = temp_target;
}

bool BaseMan::checkIsPengzhuang()
{
    if (m_attackTarget == nullptr)
        return false;
    
    Rect rect1 = m_attackTarget->getBoundingBox();
    Rect rect2 = this->getBoundingBox();
    float lx = max(rect1.getMinX() , rect2.getMinX() );
    float ly = max(rect1.getMinY() , rect2.getMinY() );
    
    float rx = min(rect1.getMaxX() , rect2.getMaxX() );
    float ry = min(rect1.getMaxY() , rect2.getMaxY() );
    
    //判断是否能构成小矩形
    if( lx > rx || ly > ry )
        return false; //矩形不相交
    else
        return true;  //发生碰撞
}
