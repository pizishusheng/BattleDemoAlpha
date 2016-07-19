//
//  BattleScene.hpp
//  BattleDemo
//
//  Created by Tao on 16/7/12.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleScene :public cocos2d::Scene
{
public:
    BattleScene();
    ~BattleScene();
    
    static BattleScene* create();
    bool init() override;
    
private:
    
};

#endif /* BattleScene_hpp */
