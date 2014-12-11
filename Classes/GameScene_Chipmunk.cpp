//
//  GameScene_Chipmunk.cpp
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/10.
//
//

#include "GameScene_Chipmunk.h"
#include <random>

GameScene_Chipmunk::GameScene_Chipmunk()
{
    
}

GameScene_Chipmunk::~GameScene_Chipmunk()
{
}

Scene *GameScene_Chipmunk::createGameScene_Chipmunk()
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
    
    auto layer = GameScene_Chipmunk::create();
    scene->addChild(layer);
    layer->setTag(1);
    return scene;
}

bool GameScene_Chipmunk::init()
{
    if ( !Scene::init() ) {
        return false;
    }
    
    //画面サイズサイズを取得
    auto window_size = Director::getInstance()->getWinSize();
    
    //床
    auto floor = Sprite::create();
    floor->setPosition(window_size.width/2, 0);
    floor->setTextureRect(Rect(0,0,window_size.width,100));
    floor->setColor(Color3B(255,255,255));
    floor->setTag(spriteType::kFloor);
    _floor = floor->getSpriteFrame()->getRect();
    
    auto left_wall =  Sprite::create();
    left_wall->setPosition(10, window_size.height/2);
    left_wall->setTextureRect(Rect(0,0,10,window_size.height));
    left_wall->setColor(Color3B(255,255,255));
    _leftwall = left_wall->getSpriteFrame()->getRect();
    
    auto right_wall =  Sprite::create();
    right_wall->setPosition(window_size.width, window_size.height/2);
    right_wall->setTextureRect(Rect(0,0,10,window_size.height));
    right_wall->setColor(Color3B(255,255,255));
    _rightwall = right_wall->getSpriteFrame()->getRect();
    
    _ceil = Rect(window_size.width/2, window_size.height - 200, window_size.width, 20);
    
    //wall->setRotation(10.0f);
    //反発係数と摩擦係数
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    material.friction = 1.0f;
    
    auto pWall = PhysicsBody::createBox(floor->getContentSize(), material);
    //重力干渉を受けるか
    pWall->setDynamic(false);
    //回転させるか
    pWall->setRotationEnable(false);
    pWall->setContactTestBitmask(true);
    floor->setPhysicsBody(pWall);
    addChild(floor);
    
    auto pright_wall = PhysicsBody::createBox(right_wall->getContentSize(), material);
    //重力干渉を受けるか
    pright_wall->setDynamic(false);
    //回転させるか
    pright_wall->setRotationEnable(false);
    right_wall->setPhysicsBody(pright_wall);
    addChild(right_wall);
    
    auto pleft_wall = PhysicsBody::createBox(left_wall->getContentSize(), material);
    //重力干渉を受けるか
    pleft_wall->setDynamic(false);
    //回転させるか
    pleft_wall->setRotationEnable(false);
    left_wall->setPhysicsBody(pleft_wall);
    addChild(left_wall);
    
    
    //event listener
    //イベントリスナー作成
    auto listener = EventListenerTouchAllAtOnce::create();
    
    //イベントを飲み込むかどうか
    //listener->setSwallowTouches(true);
    
    //タッチメソッド設定
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene_Chipmunk::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene_Chipmunk::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene_Chipmunk::onTouchesEnded, this);
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //優先度100でディスパッチャーに登録
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    //衝突検知
    auto plistener = EventListenerPhysicsContact::create();
    plistener->onContactBegin = CC_CALLBACK_1(GameScene_Chipmunk::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(plistener, this);
    
    auto plistenerend = EventListenerPhysicsContact::create();
    plistenerend->onContactPostSolve = CC_CALLBACK_2(GameScene_Chipmunk::onContactPostSolve, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(plistenerend, this);
    
    this->fillBoll();
    
    scheduleUpdate();
    
    return true;
}


BallSprite *GameScene_Chipmunk::createSprite(Vec2 &pos){
    BallSprite *ball = BallSprite::createBallSprite(this, "ball.png");
    ball->setCenter(pos);
    ball->setTag(spriteType::kBall);
    _bollArray.push_back(ball);
    return ball;
}

void GameScene_Chipmunk::update(float dt) {
    this->delTouchedBalls();
}


#pragma mark ---------
#pragma mark タップ処理
void GameScene_Chipmunk::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    Point location  = touches.at(0)->getLocationInView();
    Vec2 f_location = Vec2(location.x, location.y);
    
    for (auto targetObject : _bollArray)
    {
        BallSprite *ball = (BallSprite *)targetObject;
        
        if (ball->isInCircle(f_location, this)) {
            ball->setDeleteState(BallSprite::deleteState::kDelete);
        }
    }

    
    return;
}

void GameScene_Chipmunk::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    
    return;
}
void GameScene_Chipmunk::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    // this will return x, y coordinate
    /*
    Point location = touches.at(0)->getLocationInView();
    
    // convert this location to Cocos2d x, y coordinate
    location = Director::getInstance()->convertToGL(location);
    CCLOG("boll pos = %lf %lf",location.x, location.y);
    
    this->createSprite(location);
     */
}

#pragma mark ---------
#pragma mark 衝突処理
bool GameScene_Chipmunk::onContactBegin(PhysicsContact& contact)
{
    //衝突したら呼ばれる
    //ノードを取得
    return true;
}

void GameScene_Chipmunk::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
    auto node1 = contact.getShapeA()->getBody()->getNode();
    auto node2 = contact.getShapeB()->getBody()->getNode();
    if (node1->getTag()== spriteType::kFloor && node2->getTag()== spriteType::kBall) {
        BallSprite *ball = (BallSprite *)node2;
        bool ball_state_none    = (ball->getBallContState() == BallSprite::ballContactState::kNone);
        if (ball_state_none) {
             ball->setBallContState(BallSprite::ballContactState::kFloorContact);
        }
       
    }
    else if (node2->getTag()== spriteType::kFloor && node1->getTag()== spriteType::kBall) {
        BallSprite *ball = (BallSprite *)node1;
        bool ball_state_none    = (ball->getBallContState() == BallSprite::ballContactState::kNone);
        ball->setBallContState(BallSprite::ballContactState::kFloorContact);
        if (ball_state_none) {
            ball->setBallContState(BallSprite::ballContactState::kFloorContact);
        }
    }
    else if (node2->getTag()== spriteType::kBall && node1->getTag()== spriteType::kBall) {
        BallSprite *ball1 = (BallSprite *)node1;
        BallSprite *ball2 = (BallSprite *)node2;
        bool ball1_state_floor   = (ball1->getBallContState() == BallSprite::ballContactState::kFloorContact);
        bool ball2_state_floor   = (ball2->getBallContState() == BallSprite::ballContactState::kFloorContact);
        bool ball1_state_none    = (ball1->getBallContState() == BallSprite::ballContactState::kNone);
        bool ball2_state_none    = (ball2->getBallContState() == BallSprite::ballContactState::kNone);
        bool ball1_state_second  = (ball1->getBallContState() == BallSprite::ballContactState::kSecondContact);
        bool ball2_state_second  = (ball2->getBallContState() == BallSprite::ballContactState::kSecondContact);
        
        if (ball1_state_none || ball2_state_floor) {
            ball1->setBallContState(BallSprite::ballContactState::kSecondContact);
        }
        else if (ball1_state_floor || ball2_state_none) {
            ball2->setBallContState(BallSprite::ballContactState::kSecondContact);
        }
        else if (ball1_state_none || ball2_state_second) {
            ball1->setBallContState(BallSprite::ballContactState::kSecondContact);
        }
        else if (ball2_state_none || ball1_state_second) {
            ball2->setBallContState(BallSprite::ballContactState::kSecondContact);
        }
        
    }

}


#pragma mark ---------
#pragma mark ボール満タン
bool GameScene_Chipmunk::isFullBoll(BallSprite *ball) {
    if (ball->getBallContState()!= BallSprite::ballContactState::kNone) {
        return false;
    }
    
    Rect ballRect = ball->getSpriteFrame()->getRect();
    
    if (_ceil.intersectsRect(ballRect)) {
        return true;
    }
    
    return false;
}

void GameScene_Chipmunk::fillBoll() {
    std::random_device rd;
    
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> score(0.2,2);
    
    auto window_size = Director::getInstance()->getWinSize();
    float radius = BallSprite::getBallRadius();
    Size vir_rectSize = Size(radius*2, radius*2);
    for (float pos_x = 0; pos_x <= window_size.width; pos_x += vir_rectSize.width *score(mt) ) {
        for (float pos_y = 0; pos_y <= window_size.height; pos_y += vir_rectSize.height * score(mt)) {
            Vec2 pos = Vec2(pos_x, pos_y);
            BallSprite *ball = this->createSprite(pos);
            if (this->isFullBoll(ball)) {
                return;
            }
        }
    }
}

Rect GameScene_Chipmunk::fillBoll_createRect(Size size, Vec2 pos)
{
    return Rect(pos.x, pos.y, size.width, size.height);
}

#pragma mark ---------
#pragma mark ボール削除
void GameScene_Chipmunk::delTouchedBalls() {
    
    std::vector<BallSprite*>::iterator tempIterator;
    std::vector<BallSprite*> tmpbollArray;
    
    std::vector<std::vector<BallSprite*>::iterator> deleteIteratorArray;
    for( tempIterator = _bollArray.begin(); tempIterator != _bollArray.end(); tempIterator++ ) {
         BallSprite *ball = (BallSprite *)*tempIterator;
        if (ball->getDeleteState()==BallSprite::deleteState::kDelete) {
            ball->removeFromParent();
        }
        else {
            tmpbollArray.push_back(ball);
        }
    }
    
    _bollArray.clear();
    for (auto nodelball = tmpbollArray.begin(); nodelball != tmpbollArray.end(); nodelball++) {
        BallSprite *ball = (BallSprite *)*nodelball;
        _bollArray.push_back(ball);
    }
    
}
