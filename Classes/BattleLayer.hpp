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
private:
    bool init() override;
    void initHero();
    void changeHeroState();
private:
    BaseMan *m_hero;
};

#endif /* BattleLayer_hpp */
