//
//  BallTouchState.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/15.
//
//

#ifndef __TumTum_Base__BallTouchState__
#define __TumTum_Base__BallTouchState__

#include "cocos2d.h"
#include "BallState.h"


using namespace cocos2d;


class BallTouchBegin : public State
{
public:
    virtual bool init();
    static BallTouchBegin *createBallTouchState();
    CREATE_FUNC(BallTouchBegin);
    virtual void run() {
        
    }
    
private:
    
};


class BallAleadyTouch : public State
{
public:
    virtual bool init();
    static BallAleadyTouch *createBallTouchState();
    CREATE_FUNC(BallAleadyTouch);
};


#endif /* defined(__TumTum_Base__BallTouchState__) */
