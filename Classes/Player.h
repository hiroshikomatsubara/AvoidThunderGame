//
//  CloudEnemy.h
//  Newci
//
//  Created by A13492 on 2014/07/17.
//
//

#ifndef __Newci__Player__
#define __Newci__Player__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Player : public CCLayer
{
    CCBAnimationManager *mAnimationManager;
    
public:
    Player();
    virtual ~Player();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Player, create);
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    void walkLeft();
    void walkRight();
    void dead();
};

class PlayerLoader : public cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Player);
};
#endif /* defined(__Newci__Player__) */
