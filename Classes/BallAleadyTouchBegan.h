//
//  BallTouchBegan.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/18.
//
//

#ifndef TumTum_Base_BallTouchBegan_h
#define TumTum_Base_BallTouchBegan_h

#include "BallState.h"
#include "BallTouchEnd.h"

using namespace cocos2d;

template<class PARENT>
class BallAleadyTouchBegan : public State<PARENT>
{
public:
    
    //virtual bool init();
    CREATE_FUNC(BallAleadyTouchBegan);
    static BallAleadyTouchBegan *createState() {
        //auto pInst = BallAleadyTouchBegan<PARENT>::create();
        auto pInst = new BallAleadyTouchBegan<PARENT>;
        return pInst;
    };
    
    virtual  State<PARENT> *run(PARENT* parent, State<PARENT>* &newState){
        if (parent->getIsTouchEnd()) {
            log("ball state touchbegan->touchend");
            return BallTouchEnd<PARENT>::createState();
        }
        else {
            return this;
        }
    }
    
};


#endif
