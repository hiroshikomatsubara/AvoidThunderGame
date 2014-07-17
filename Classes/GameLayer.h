//
//  GameLayer.h
//  Newci
//
//  Created by A13492 on 2014/07/17.
//
//

#ifndef __Newci__GameLayer__
#define __Newci__GameLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CloudEnemy.h"
#include "Player.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameLayer : public CCLayer,
public CCBSelectorResolver, // selectorイベントを取得
public CCBMemberVariableAssigner // 変数を取得
{
    CCBAnimationManager *mAnimationManager_;
    
    Player* player_;
    CCArray* enemies_;
    CCNode* enemyContainer_;
    
    CCLabelTTF* deadLabel_;
    CCLabelTTF* pointLabel_;
    
    int deadNum_;
    int pointNum_;
    
    virtual void onEnter();
    virtual void enemyAttackTimer(float time);
    void generateEnemy();
    void checkHit(CCObject* pSender);
    
    //ccbの定義とc++の定義をリンク
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);// メソッド
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);//
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);// メンバ
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);// 変数

    void onTapLeft(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onTapRight(CCObject* pSender, CCControlEvent pCCControlEvent);
    
public:
    GameLayer();
    virtual ~GameLayer();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameLayer, create);
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
};

class GameLayerLoader : public cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameLayerLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameLayer);
};


#endif /* defined(__Newci__GameLayer__) */
