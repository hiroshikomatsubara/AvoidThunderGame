//
//  CloudEnemy.cpp
//  Newci
//
//  Created by A13492 on 2014/07/17.
//
//

#include "Player.h"

Player::Player()
:mAnimationManager(NULL)
{
}

Player::~Player()
{
    CC_SAFE_RELEASE(mAnimationManager);
}

//ccbReaderからgetしたAnimationManagerの更新
void Player::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(this->mAnimationManager);
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(this->mAnimationManager);
}

void Player::walkLeft() {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("walkLeft", 0);
}

void Player::walkRight() {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("walkRight", 0);
}

void Player::dead() {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("dead", 0);
}