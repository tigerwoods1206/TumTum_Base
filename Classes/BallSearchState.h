//
//  BallSearchState.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/17.
//
//

#ifndef __TumTum_Base__BallHilightState__
#define __TumTum_Base__BallHilightState__

#include "cocos2d.h"
#include "BallState.h"
#include "BallSprite.h"

using namespace cocos2d;

class BallPreSearch : public State<BallSprite>
{
public:
    virtual bool init();
    static BallPreSearch *createState();
    //CREATE_FUNC(BallHilightState);
    virtual StateInfo run(BallSprite* parent, State<BallSprite>* &newState) = 0;
    
};

class BallNextChain : public State<BallSprite>
{
public:
    virtual bool init();
    static BallNextChain *createState();
    //CREATE_FUNC(BallHilightState);
    virtual StateInfo run(BallSprite* parent, State<BallSprite>* &newState) = 0;
    
};

class BallSearchFinish : public State<BallSprite>
{
public:
    virtual bool init();
    static BallSearchFinish *createState();
    //CREATE_FUNC(BallHilightState);
    virtual StateInfo run(BallSprite* parent, State<BallSprite>* &newState) = 0;
    
};

#endif /* defined(__TumTum_Base__BallHilightState__) */
