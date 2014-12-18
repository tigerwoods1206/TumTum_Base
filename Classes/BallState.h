//
//  BallState.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/15.
//
//

#ifndef __TumTum_Base__BallState__
#define __TumTum_Base__BallState__

#include "cocos2d.h"

using namespace cocos2d;

template<class PARENT>
class State: public Node {
protected:
    
public:
    enum StateInfo {
        StateInfo_Continue,
        StateInfo_Next
    };
    virtual ~State() {}
    
    virtual  State* run(PARENT* parent, State<PARENT>* &newState) {
        return this;
    }
protected:
    State() {}
    
};

#endif /* defined(__TumTum_Base__BallState__) */
