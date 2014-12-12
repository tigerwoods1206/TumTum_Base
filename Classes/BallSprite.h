//
//  BallSprite.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/11.
//
//

#ifndef __TumTum_Base__BallSprite__
#define __TumTum_Base__BallSprite__

#include "cocos2d.h"

using namespace cocos2d;

class BallSprite : public Sprite
{
public:
    virtual bool init();
    static BallSprite *createBallSprite(Node *parent ,const std::string& filename);
    static float getBallRadius();
    CREATE_FUNC(BallSprite);
    
    // 衝突状態の設定
    enum ballContactState {
        kNone         = 0,
        kFloorContact,
        kSecondContact
    };
    ballContactState getBallContState();
    void setBallContState(ballContactState);
    
    // タッチ判定
    void setCenter(Vec2 pos);
    bool isInCircle(Vec2 pos, Node *parent);
  
    enum deleteState {
        kNoDelete = 0,
        kPreDelete,
        kDelete
    };
    deleteState getDeleteState();
    void setDeleteState(deleteState state);
    
    //ボール種類判定
    enum ballType {
        kRed = 0,
        kBrue,
        kPurple,
        kYellow
    };
    ballType getBallType();
    void setBallType(ballType state);
    
    //ボールハイライト判定
    enum ballHilightType {
        kNoTouch = 0,
        kFirstTouch,
        kTouch,
        kAdjacent, //touchしたボールに隣接するボール
        kChain//ハイライトされるボール全部
    };
    ballHilightType getBallHilightType();
    void setBallHilightType(ballHilightType state);
    
protected:
    ballContactState _ballContactState;
    deleteState      _deleteState;
    ballType         _ballType;
    ballHilightType  _ballHilightType;
    Vec2             _centerPos;
};

#endif /* defined(__TumTum_Base__BallSprite__) */
