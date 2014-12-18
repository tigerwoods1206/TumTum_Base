//
//  BallAleadyTouchEnd.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/18.
//
//

#ifndef TumTum_Base_BallAleadyTouchEnd_h
#define TumTum_Base_BallAleadyTouchEnd_h
#include "BallState.h"

using namespace cocos2d;

template<class PARENT>
class BallTouchEnd : public State<PARENT>
{
public:
    //virtual bool init();
    CREATE_FUNC(BallTouchEnd);
    static BallTouchEnd *createState() {
        //auto pInst = BallTouchEnd<PARENT>::create();
        auto pInst = new BallTouchEnd<PARENT>;
        return pInst;
    }
    
    virtual  State<PARENT> *run(PARENT* parent, State<PARENT>* &newState) {
        log("ball state is end");
        return this;
    };
};


#endif
