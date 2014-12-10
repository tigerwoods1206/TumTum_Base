//
//  GameScene.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/10.
//
//

#ifndef __TumTum_Base__GameScene__
#define __TumTum_Base__GameScene__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene : public Scene
{
public:
    virtual bool init();
    static Scene *createGameScene();
    CREATE_FUNC(GameScene);
    
    GameScene();
    ~GameScene();
    
    void createSprite(Vec2 &pos);
    
    //touch
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
private:
    Scene *back_wall;
};

#endif /* defined(__TumTum_Base__GameScene__) */
