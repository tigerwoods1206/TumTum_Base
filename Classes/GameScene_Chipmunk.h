//
//  GameScene_Chipmunk.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/10.
//
//

#ifndef __TumTum_Base__GameScene_Chipmunk__
#define __TumTum_Base__GameScene_Chipmunk__

#include "cocos2d.h"
#include "BallSprite.h"

using namespace cocos2d;

class GameScene_Chipmunk : public Scene
{
public:
    virtual bool init();
    static Scene *createGameScene_Chipmunk();
    CREATE_FUNC(GameScene_Chipmunk);
    
    GameScene_Chipmunk();
    ~GameScene_Chipmunk();
    
    BallSprite *createSprite(Vec2 &pos);

    
    void update(float dt);
    
    //touch
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
private:
    //衝突検知
    enum spriteType {
        kNone  = 0,
        kFloor,
        kBall
    };
    bool onContactBegin(PhysicsContact& contact);
    //std::function<void(PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);

    //ボール充填
private:
    //ボールが満杯になった事を検知
    bool isFullBoll(BallSprite *ball);
    //ボール満タン
    void fillBoll();
    //消された分のボールを補充
    void refillBoll();
    std::vector<Vec2> _delballPos;
    
    //ボールが壁に接触している事を検知
    void isContactWall(Rect box);
    
    // in isContactWall
    Rect _floor, _leftwall, _rightwall, _ceil;
    
    //隣接ボールハイライト
    void setHilightAdjacent();
    void srchAdjacent(BallSprite* first);
    
    //ボール削除
private:
    void delTouchedBalls();
    std::vector<BallSprite*> _bollArray;
};

#endif /* defined(__TumTum_Base__GameScene_Chipmunk__) */
