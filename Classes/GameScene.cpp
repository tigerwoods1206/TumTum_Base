//
//  GameScene.cpp
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/10.
//
//

#include "GameScene.h"

GameScene::GameScene()

{
    
}

GameScene::~GameScene()
{
  
}

Scene *GameScene::createGameScene()
{
    //物理演算を使う為にcreateWithPhysicsを使用
    auto scene = Scene::createWithPhysics();
    
    //Worldに対して重力をセット
    Vect gravity;
    gravity.setPoint(0, -50);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSpeed(6.0f);
    
    //物理オブジェクトを可視的にしてくれるデバックモード
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    layer->setTag(1);
    return scene;
}

bool GameScene::init()
{
    if ( !Scene::init() ) {
        return false;
    }
    
    //画面サイズサイズを取得
    auto window_size = Director::getInstance()->getWinSize();
    
    //床
    auto wall = Sprite::create();
    wall->setPosition(150, 0);
    wall->setTextureRect(Rect(0,0,1000,100));
    wall->setColor(Color3B(255,255,255));
    //wall->setRotation(10.0f);
    //反発係数と摩擦係数
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    material.friction = 0.0f;
    
    auto pWall = PhysicsBody::createBox(wall->getContentSize(), material);
    //重力干渉を受けるか
    pWall->setDynamic(false);
    //回転させるか
    pWall->setRotationEnable(false);
    wall->setPhysicsBody(pWall);
    addChild(wall);
    
    
    //event listener
    //イベントリスナー作成
    auto listener = EventListenerTouchAllAtOnce::create();
    
    //イベントを飲み込むかどうか
    //listener->setSwallowTouches(true);
    
    //タッチメソッド設定
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //優先度100でディスパッチャーに登録
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    return true;
}

//-------------------------
// タップ時
void GameScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    
    
    return;
}

void GameScene::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    int i = 0;
    int count = 0;
    
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        iterator++;
    }
    
    return;
}
void GameScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    // this will return x, y coordinate
    Point location = touches.at(0)->getLocationInView();
    
    // convert this location to Cocos2d x, y coordinate
    location = Director::getInstance()->convertToGL(location);
    CCLOG("boll pos = %lf %lf",location.x, location.y);
    
    this->createSprite(location);
}

void GameScene::createSprite(Vec2 &pos){
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* sprite = Sprite::create("ball.png");
    //auto sprite = Sprite::create();
    sprite->setPosition(pos);
    
    auto pBall = PhysicsBody::createCircle(50);
    pBall->setDynamic(true);
    pBall->setRotationEnable(true);
    sprite->setPhysicsBody(pBall);
    this->addChild(sprite);
}
