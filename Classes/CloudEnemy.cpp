//
//  CloudEnemy.cpp
//  Newci
//
//  Created by A13492 on 2014/07/17.
//
//

#include "CloudEnemy.h"

CloudEnemy::CloudEnemy()
:mAnimationManager(NULL)
{
}

CloudEnemy::~CloudEnemy()
{
    CC_SAFE_RELEASE(mAnimationManager);
}

//ccbReaderからgetしたAnimationManagerの更新
void CloudEnemy::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(this->mAnimationManager);
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(this->mAnimationManager);
}

void CloudEnemy::ready() {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("readyToAttack", 0);
}

void CloudEnemy::attack() {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("attack", 0);
}