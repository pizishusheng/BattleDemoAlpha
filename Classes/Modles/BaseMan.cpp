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
m_isPlayState(1)
{
}

BaseMan::~BaseMan()
{
    
}

BaseMan* BaseMan::createWithFile(std::string fileName)
{
    BaseMan *pRet = new BaseMan();
    if (pRet && pRet->initWithFile(fileName)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BaseMan::initWithFile(std::string fileName)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo(fileName+".png", fileName+".plist", fileName+".xml");
    m_armature = Armature::create( "hero1001");
    
    m_armature->getAnimation()->setSpeedScale(0.7f);
    this->addChild(m_armature);
    return true;
}

void BaseMan::setPosition(const cocos2d::Vec2 &position)
{
    if (m_armature == nullptr)
        return;
    
    m_armature->setPosition(position);
}

void BaseMan::setActionState(ActionState state)
{
    m_state = state;
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
    auto move = MoveTo::create(5.0f, Vec2(0,0));
    m_armature->runAction(move);
}

void BaseMan::actionAttack()
{
    
}

void BaseMan::checkAttackTarget(vector<BaseMan *> targetVector)
{
    if (m_attackTarget != nullptr) {
        return;
    }
    
    float distance = 0;
    for (auto target: targetVector)
    {
        float temp = sqrt(pow(abs(target->getPositionX() - this->getPositionX()), abs(target->getPositionY() - this->getPositionY())));
        
        if (temp < distance)
        {
            distance = temp;
            m_attackTarget = target;
        }
    }
}
