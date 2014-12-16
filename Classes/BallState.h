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
#include "BallSprite.h"

using namespace cocos2d;

template<class PARENT>
class State public Node {
protected:
    virtual bool init();
    State() {}
    static State *createState();
    CREATE_FUNC(State);
public:
    virtual ~State() {}
    // 何かする
    virtual void run(PARENT* parent, State<PARENT>* &newState) = 0;
};#endif /* defined(__TumTum_Base__BallState__) */
