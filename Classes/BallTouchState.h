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

class BallTouchState : public BallState<bool>
{
    
    class BallTouch : public BallState<BallTouchState>
    {
    public:
        virtual bool init();
        static BallTouch *createBallTouchState();
        CREATE_FUNC(BallTouch);
        
    };

    
public:
    virtual bool init();
    static BallTouchState *createBallTouchState();
    CREATE_FUNC(BallTouchState);
    virtual void entryAction(BallTouchState& outerVal) {
        
    };
    virtual Trans inputAction(BallTouchState& outerVal, BallState<BallTouchState>  &outNextState) {
        //outNextState =
        return StateBase::Trans_Me_Again;
    }
    virtual void exitAction(BallTouchState& outerVal);
};


class BallAleadyTouch : public BallState<bool>
{
public:
    virtual bool init();
    static BallAleadyTouch *createBallTouchState();
    CREATE_FUNC(BallAleadyTouch);
};


#endif /* defined(__TumTum_Base__BallTouchState__) */
