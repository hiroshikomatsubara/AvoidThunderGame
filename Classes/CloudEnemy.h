//
//  CloudEnemy.h
//  Newci
//
//  Created by A13492 on 2014/07/17.
//
//

#ifndef __Newci__CloudEnemy__
#define __Newci__CloudEnemy__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CloudEnemy : public CCLayer
{
    CCBAnimationManager *mAnimationManager;
    
public:
    CloudEnemy();
    virtual ~CloudEnemy();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CloudEnemy, create);
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    void ready();
    void attack();
};

class CloudEnemyLoader : public cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CloudEnemyLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CloudEnemy);
};
#endif /* defined(__Newci__CloudEnemy__) */
