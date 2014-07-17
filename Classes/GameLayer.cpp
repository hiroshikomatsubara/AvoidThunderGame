//
//  GameLayer.cpp
//  Newci
//
//  Created by A13492 on 2014/07/17.
//
//

#include "GameLayer.h"
#include "CloudEnemy.h"
#define ENEMY_NUM 3
#define MOVE_D 100

GameLayer::GameLayer()
:mAnimationManager_(NULL)
,player_(NULL)
,deadLabel_(NULL)
,pointLabel_(NULL)
{
    enemies_ = CCArray::create();
    enemies_->retain();
    deadNum_ = 0;
    pointNum_ = 0;
}

GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE(mAnimationManager_);
    CC_SAFE_RELEASE(enemies_);
    CC_SAFE_RELEASE(player_);
    CC_SAFE_RELEASE(deadLabel_);
    CC_SAFE_RELEASE(pointLabel_);
}


void GameLayer::onEnter()
{
    CCLayer::onEnter();
    
    deadLabel_->setString(CCString::createWithFormat("Dead:0")->getCString());
    pointLabel_->setString(CCString::createWithFormat("Point:0")->getCString());

    // 敵の攻撃イベント
    this->schedule(schedule_selector(GameLayer::enemyAttackTimer), 2.0);
    
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("Player", PlayerLoader::loader());
    
    CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
    Player* node = (Player*)ccbReader->readNodeGraphFromFile("Player.ccbi");
    node->setAnimationManager(ccbReader->getAnimationManager());
    ccbReader->release();
    node->setPosition( ccp(500, 200) );
    this->addChild(node);
    player_ = node;
    
    generateEnemy();
}

void GameLayer::generateEnemy() {
    
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("CloudEnemy", CloudEnemyLoader::loader());
    
    // generate enemy
    enemyContainer_ = CCNode::create();
    this->addChild(enemyContainer_);
    
    enemies_->init();
    for (int i = 0; i < ENEMY_NUM; i++) {
        CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode* node = ccbReader->readNodeGraphFromFile("CloudEnemy.ccbi");
        ((CloudEnemy*)node)->setAnimationManager(ccbReader->getAnimationManager());
        ccbReader->release();
        node->setPosition( ccp(300 * i, 500) );
        enemyContainer_->addChild(node);
        this->enemies_->addObject((CloudEnemy*)node);
    }
}

#pragma mark - event

//移動
void GameLayer::onTapLeft(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    player_->walkRight();
    enemyContainer_->runAction(CCMoveBy::create(0.5, ccp(MOVE_D, 0)));
}

void GameLayer::onTapRight(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    player_->walkLeft();
    enemyContainer_->runAction(CCMoveBy::create(0.5, ccp(-MOVE_D, 0)));
    
}

void GameLayer::enemyAttackTimer(float time)
{
    CloudEnemy *enemy = (CloudEnemy*)this->enemies_->objectAtIndex(rand() % this->enemies_->count());
    enemy->ready();
    
    CCCallFuncN *func = CCCallFuncN::create(this, callfuncN_selector(GameLayer::checkHit));
    
    CCSequence *seq = CCSequence::create(CCDelayTime::create(0.9), func, NULL);//なぜかdelay長いとだめ
    enemy->runAction(seq);
}

// あたり判定
void GameLayer::checkHit(CCObject* pSender)
{
    CloudEnemy *enemy = (CloudEnemy*)pSender;
    enemy->attack();
    float enemyXPos = enemy->getPositionX() + enemyContainer_->getPositionX();
    if(fabs(enemyXPos - 500) < 100) {
        player_->dead();
        deadNum_++;
        deadLabel_->setString(CCString::createWithFormat("Dead:%d",deadNum_)->getCString());
    }
}

#pragma mark - Builder

//メソッドのリンク
SEL_MenuHandler GameLayer::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "leftTapped", GameLayer::onTapLeft);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "rightTapped", GameLayer::onTapRight);
    return NULL;
}

//謎
SEL_CCControlHandler GameLayer::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

//変数のリンク
bool GameLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "deadLabel", CCLabelTTF*, deadLabel_);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pointLabel", CCLabelTTF*, pointLabel_);
    return false;
}

bool GameLayer::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    return false;
}

//ccbReaderからgetしたAnimationManagerの更新
void GameLayer::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager_);
    mAnimationManager_ = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager_);
}

