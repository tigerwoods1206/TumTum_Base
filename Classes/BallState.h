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

class StateBase :public Node{
protected:
    enum Trans {
        Trans_Me_Again,   // 再び自分
        Trans_Occured,    // 状態遷移が起きた
    };
    
public:
    StateBase() {}
};

template< class VAL >
class BallState : public StateBase {
private:
    bool bFirstUpdate;
    
protected:
    virtual void entryAction(VAL& outerVal) {}
    virtual Trans inputAction(VAL& outerVal, BallState<VAL>  &outNextState) {return Trans_Me_Again;}
    virtual void exitAction(VAL& outerVal) {}
    
    //touch
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
public:
    BallState() : bFirstUpdate(true) {}
    
    // 状態更新
    
    BallState<VAL>  update(VAL& outerVal) {
        if (bFirstUpdate) {
            entryAction(outerVal);
            bFirstUpdate = false;
        }
        BallState<VAL> outerState;
        Trans trans = inputAction(outerVal, outerState);
        if (trans == Trans_Occured)
            exitAction(outerVal);
        return outerState;
    }
};

#endif /* defined(__TumTum_Base__BallState__) */
