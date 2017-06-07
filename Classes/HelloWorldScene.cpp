#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BattleScene.hpp"

USING_NS_CC;

struct func{
    int i;
    func(int i_) : i(i_){};
    
    void operator() ()
    {
        for (unsigned j=0; j< 100000;++j)
        {
            i = j;
            printf("func=====%d\n", i);
        }
    }
};

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    
}


