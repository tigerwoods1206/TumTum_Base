//
//  BallAleadyTouchMoved.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/18.
//
//

#ifndef TumTum_Base_BallAleadyTouchMoved_h
#define TumTum_Base_BallAleadyTouchMoved_h

#include "BallState.h"
#include "BallTouchEnd.h"

using namespace cocos2d;

template<class PARENT>
class BallAleadyTouchMoved : public State<PARENT>
{
public:
    
    //virtual bool init();
    CREATE_FUNC(BallAleadyTouchMoved);
    static BallAleadyTouchMoved *createState() {
        auto pInst = new BallAleadyTouchMoved<PARENT>;
        return pInst;
    };
    
    virtual  State<PARENT> *run(PARENT* parent, State<PARENT>* &newState){
        if (parent->getIsTouchEnd()) {
            log("ball state touchmoved->touchend");
            return BallTouchEnd<PARENT>::createState();
        }
        else {
            return this;
        }
    }
    
};


#endif
