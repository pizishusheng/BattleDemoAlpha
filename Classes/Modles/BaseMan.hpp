//
//  BaseMan.hpp
//  BattleDemo
//
//  Created by Tao on 16/7/19.
//
//

#ifndef BaseMan_hpp
#define BaseMan_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "editor-support/cocostudio/CCArmature.h"

using namespace cocostudio;
using namespace std;
typedef enum{
    ACTION_IDLE = 1,
    ACTION_WALK,
    ACTION_ATTACK,
    ACTION_SKILL,
    ACTION_SKILL2,
    ACTION_GET_HURT,
    ACTION_DIE,
} ActionState;

class BaseMan : public cocos2d::Node
{
public:
    BaseMan();
    ~BaseMan();
    
    static BaseMan* createWithFile(std::string filePath, string fileArmature);
    virtual void setPositionss(const cocos2d::Vec2 &position);
    void onEnter();
    void onExit();
    void update(float dt);
    void setActionState(ActionState state);
    Armature *getArmature();
    void checkAttackTarget(vector<BaseMan*> targetVector);
protected:
    virtual bool initWithFile(std::string filePath, string fileArmature);
    virtual void playAnimationByActionState(ActionState state);
    void actionWalk();
    void actionAttack();
    bool checkIsPengzhuang();
    void updatePosition();
protected:
    Armature *m_armature;
    ActionState m_state;
    unsigned int m_isPlayState;
    BaseMan* m_attackTarget;
private:
};

#endif /* BaseMan_hpp */
