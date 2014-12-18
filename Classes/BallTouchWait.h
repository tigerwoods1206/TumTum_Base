//
//  BallTouchWait.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/18.
//
//

#ifndef TumTum_Base_BallTouchWait_h
#define TumTum_Base_BallTouchWait_h
#include "BallState.h"
#include "BallAleadyTouchBegan.h"
#include "BallAleadyTouchMoved.h"
#include "BallTouchEnd.h"

using namespace cocos2d;

template<class PARENT>
class BallTouchWait : public State<PARENT>
{
public:
    //virtual bool init();
    CREATE_FUNC(BallTouchWait<PARENT>);
    static BallTouchWait<PARENT> *createState() {
        //auto pInst = BallTouchWait::create();
        auto pInst = new BallTouchWait<PARENT>;
        return pInst;
    }
    
    virtual  State<PARENT>* run(PARENT* parent, State<PARENT>* &newState){
        if (parent->getIsTouchBegan()) {
            log("ball state wait->touchbegan");
            return BallAleadyTouchBegan<PARENT>::createState();
        }
        else if(parent->getIsTouchMoved()) {
            log("ball state wait->touchmoved");
            return BallAleadyTouchMoved<PARENT>::createState();
        }
        else {
            return this;
        }
    }
    
};


#endif
