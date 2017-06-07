//
//  BattleLayer.hpp
//  BattleDemo
//
//  Created by Tao on 16/7/14.
//
//

#ifndef BattleLayer_hpp
#define BattleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Modles/BaseMan.hpp"

class BattleLayer: public cocos2d::Layer
{
public:
    BattleLayer();
    ~BattleLayer();
    
    static BattleLayer* create();
    void initSector();
private:
    bool init() override;
    void initHero();
    void initEnemy();
    void changeHeroState();
private:
    BaseMan *m_hero;
    std::vector<BaseMan*> m_enemyVector;
};

#endif /* BattleLayer_hpp */
