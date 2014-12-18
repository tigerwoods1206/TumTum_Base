//
//  BallPoolLayer.cpp
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/17.
//
//

#include "BallPoolLayer.h"

BallPoolLayer *BallPoolLayer::createBallPoolLayer()
{
    auto pInstance = BallPoolLayer::create();
    return pInstance;
}

bool BallPoolLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    return true;
}

void BallPoolLayer::update()
{
    
}

void BallPoolLayer::addBallArray()
{
    
}

void BallPoolLayer::delTouchedBalls()
{
    
}

void BallPoolLayer::srchAllAdjacent(BallSprite* cur_ball)
{
    Vec2  centerpos = cur_ball->getPosition();
    float radius    = cur_ball->getBallRadius() * 1.05;
    float dist;
    for (BallSprite* ball : _bollArray) {
        Vec2 cur_ballpos = ball->getPosition();
        dist = centerpos.getDistance(cur_ballpos);
        if (dist <= radius*2) {
            bool sametype = (ball->getBallType()==cur_ball->getBallType());
            //bool nodelete = (ball->getDeleteState()==BallSprite::deleteState::kNoDelete);
            if (sametype) {
                ball->updateState();
                this->srchAllAdjacent(ball);
            }
        }
    }

}