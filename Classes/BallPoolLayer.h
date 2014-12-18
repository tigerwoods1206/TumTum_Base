//
//  BallPoolLayer.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/17.
//
//

#ifndef __TumTum_Base__BallPoolLayer__
#define __TumTum_Base__BallPoolLayer__

#include "cocos2d.h"
#include "BallSprite.h"

using namespace cocos2d;

class BallPoolLayer : public Layer
{
public:
    virtual bool init();
    static BallPoolLayer *createBallPoolLayer();
    CREATE_FUNC(BallPoolLayer);
    
    BallSprite *createSprite(Vec2 &pos);
    
    void update();
    void addBallArray();
    
    
    void delTouchedBalls();
    void srchAllAdjacent(BallSprite* cur_ball);
    
private:
    std::vector<BallSprite*> _bollArray;
    
};

#endif /* defined(__TumTum_Base__BallPoolLayer__) */
