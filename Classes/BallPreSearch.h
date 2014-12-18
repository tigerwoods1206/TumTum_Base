//
//  BallPreSearch.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/18.
//
//

#ifndef TumTum_Base_BallPreSearch_h
#define TumTum_Base_BallPreSearch_h
#include "BallState.h"

using namespace cocos2d;

template<class PARENT>
class BallPreSearch : public State<PARENT>
{
public:
    //virtual bool init();
    static BallPreSearch<PARENT> *createState() {
        //auto pInst = BallTouchWait::create();
        auto pInst = new BallPreSearch<PARENT>;
        return pInst;
    }
    
    virtual  State<PARENT>* run(PARENT* parent, State<PARENT>* &newState){
        
        for (auto ball : parent->getBallArray) {
            parent->srchAllAdjacent(ball);
        }
        
        return this;
    }
    
};


#endif
