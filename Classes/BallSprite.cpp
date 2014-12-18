//
//  BallSprite.cpp
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/11.
//
//

#include "BallSprite.h"

BallSprite *BallSprite::createBallSprite(Node *parent, const std::string& filename)
{
    auto pInstance = BallSprite::create();
    
    //Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    
    pInstance->setTexture(filename);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    //auto sprite = Sprite::create();
    
    //反発係数と摩擦係数
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.density = 0.0;
    material.restitution = 0.0f;
    material.friction = 1.0f;
    
    //auto pBall = PhysicsBody::createCircle(50, material);
    //Size ballrect = Size(100, 100);
    float radius = getBallRadius();
    auto pBall = PhysicsBody::createCircle(radius);
    pBall->setDynamic(true);
    pBall->setRotationEnable(true);
    pBall->setContactTestBitmask(true);
    pBall->setRotationOffset(0);
    pBall->setMass(0);
    
    parent->addChild(pInstance);
    pInstance->setPhysicsBody(pBall);
   
    return pInstance;
}

float BallSprite::getBallRadius()
{
    
    return 50;
}

bool BallSprite::init()
{
    if ( !Sprite::init() ) {
        return false;
    }
    _ballContactState = ballContactState::kNone;
    _deleteState      = deleteState::kNoDelete;
    _ballType         = ballType::kRed;
    _ballHilightType  = ballHilightType::kNoTouch;
    
    _isTouchBegan = false;
    _isTouchMoved = false;
    _isTouchEnd   = false;
    
    curState = BallTouchWait<BallSprite>::createState();
    
    this->setOpacity(200);
    return true;
}

BallSprite::ballContactState BallSprite::getBallContState(){
    
    return _ballContactState;
}

void BallSprite::setBallContState(ballContactState state) {
    PhysicsBody *body =  this->getPhysicsBody();
    if (state == ballContactState::kFloorContact || ballContactState::kSecondContact) {
        //cpSpaceAddPostStepCallback
        //body->setDynamic(false);
        Vec2 ver = Vec2(0, 0.1);
        //body->setVelocity(ver);
    }
    else {
        //body->setDynamic(true);
    }
    _ballContactState = state;
}

bool BallSprite::isInCircle(Vec2 pos, Node *parent) {
    const Vec2 bpos = parent->convertToNodeSpace(this->getPosition());
    float dist = pos.getDistance(bpos);
    if(dist <= getBallRadius()) {
        return true;
    }
    else {
        return false;
    }
}

bool BallSprite::isInCircle(Touch touch) {
    const Vec2 bpos = this->getPosition();
    Director* pDirector = CCDirector::getInstance();
    Point touchPoint = pDirector -> convertToGL(touch.getLocationInView());
    float dist = touchPoint.getDistance(bpos);
    if(dist <= getBallRadius()) {
        return true;
    }
    else {
        return false;
    }

}

bool BallSprite::getIsTouchBegan() {
    return _isTouchBegan;
}
void BallSprite::setIsTouchBegan() {
    _isTouchBegan = true;
}
bool BallSprite::getIsTouchMoved() {
    return _isTouchMoved;
}
void BallSprite::setIsTouchMoved() {
    _isTouchMoved = true;
}
bool BallSprite::getIsTouchEnd() {
    return _isTouchEnd;
}
void BallSprite::setIsTouchEnd() {
    _isTouchEnd = true;
}

void BallSprite::setCenter(Vec2 pos) {
    _centerPos = pos;
    this->setPosition(pos);
}

BallSprite::deleteState BallSprite::getDeleteState() {

    return _deleteState;
}

void BallSprite::setDeleteState(deleteState state){
    _deleteState = state;
}

BallSprite::ballType BallSprite::getBallType() {
    return _ballType;
}

void BallSprite::setBallType(ballType state) {
    _ballType = state;
}

BallSprite::ballHilightType BallSprite::getBallHilightType() {
    return _ballHilightType;
}
void BallSprite::setBallHilightType(ballHilightType state) {
    _ballHilightType = state;
    if (state ==  ballHilightType::kNoTouch) {
        this->setOpacity(200);
        this->setNormalTexture();
    }
    else if (state == ballHilightType::kTouch) {
        this->setOpacity(200);
        this->setNormalTexture();
    }
    else if (state == ballHilightType::kFirstTouch) {
        this->setOpacity(200);
        this->setNormalTexture();
    }
    else if (state == ballHilightType::kChain) {
        this->setOpacity(150);
        this->setHilightTexture();
        
    }
    else if (state == ballHilightType::kAdjacent) {
        this->setOpacity(255);
        this->setHilightTexture();
    }
    else {
        this->setOpacity(200);
        this->setNormalTexture();
    }
}

void BallSprite::setNormalTexture() {
    ballType type = this->getBallType();
    switch (type) {
        case ballType::kRed:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("ball.png"));
            break;
        case ballType::kBrue:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("blue_ball.png"));
            break;
        case ballType::kYellow:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("yellow_ball.png"));
            break;
        case ballType::kPurple:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("pur_ball.png"));
            break;
        default:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("ball.png"));
            break;
    }

}
void BallSprite::setHilightTexture() {
    ballType type = this->getBallType();
    switch (type) {
        case ballType::kRed:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_ball.png"));
            break;
        case ballType::kBrue:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_blue_ball.png"));
            break;
        case ballType::kYellow:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_yellow_ball.png"));
            break;
        case ballType::kPurple:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_pur_ball.png"));
            break;
        default:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_ball.png"));
            break;
    }
}

void BallSprite::updateState() {
    
    State<BallSprite> *newState = NULL;
    newState = curState->run(this, newState);
    if (newState!=curState) {
        delete curState;
        curState = newState;
    }
}

BallSprite::~BallSprite() {
    delete curState;
}
/*
State<BallSprite>::StateInfo BallSprite::run(BallSprite* parent, State<BallSprite>* &newState) {
    if (parent->getIsTouchBegan()) {
       // newState = BallAleadyTouchBegin::createState();
    }
    else if (parent->getIsTouchMoved()) {
       // newState = BallAleadyTouchMoved::createState();
    }
    
    return  State<BallSprite>::StateInfo::StateInfo_Continue;

}
*/
/*
#pragma mark -
#pragma mark BallTouchWait

template<> bool BallSprite::BallTouchWait<BallSprite>::init() {
    return true;
}

template<> State<BallSprite::BallSprite>::StateInfo BallSprite::BallTouchWait<BallSprite>::run(BallSprite* parent, State<BallSprite>* &newState) {
    
    if (parent->getIsTouchBegan()) {
        newState = BallAleadyTouchBegin::createState();
    }
    else if (parent->getIsTouchMoved()) {
        newState = BallAleadyTouchMoved::createState();
    }
    
    return  State<BallSprite>::StateInfo::StateInfo_Continue;
}

#pragma mark -
#pragma mark BallAleadyTouchBegin

bool BallSprite::BallAleadyTouchBegin::init() {
    return true;
}

BallSprite::BallAleadyTouchBegin *BallSprite::BallAleadyTouchBegin::createState() {
    auto pInstance = (BallAleadyTouchBegin *)State<BallSprite>::create();
    return pInstance;
}

State<BallSprite>::StateInfo BallSprite::BallAleadyTouchBegin::run(BallSprite* parent, State<BallSprite>* &newState) {
    if (parent->getIsTouchEnd()) {
        newState = BallEnd::createState();
    }
    
    return  State<BallSprite>::StateInfo::StateInfo_Continue;
}

#pragma mark -
#pragma mark BallAleadyTouchMoved

bool BallSprite::BallAleadyTouchMoved::init() {
    return true;
}

BallSprite::BallAleadyTouchMoved *BallSprite::BallAleadyTouchMoved::createState() {
    auto pInstance = (BallAleadyTouchMoved *)State<BallSprite>::create();
    return pInstance;
}

State<BallSprite>::StateInfo BallSprite::BallAleadyTouchMoved::run(BallSprite* parent, State<BallSprite>* &newState) {
    
    if (parent->getIsTouchEnd()) {
        newState = BallEnd::createState();
    }
    
    return  State<BallSprite>::StateInfo::StateInfo_Continue;
}

#pragma mark -
#pragma mark BallEnd

bool BallSprite::BallEnd::init() {
    return true;
}

BallSprite::BallEnd *BallSprite::BallEnd::createState() {
    auto pInstance = (BallEnd *)State<BallSprite>::create();
    return pInstance;
}

State<BallSprite>::StateInfo BallSprite::BallEnd::run(BallSprite* parent, State<BallSprite>* &newState) {
    return  State<BallSprite>::StateInfo::StateInfo_Next;
}

#pragma mark -
#pragma mark BallPreSearch

bool BallSprite::BallPreSearch::init() {
    return true;
}

BallSprite::BallPreSearch *BallSprite::BallPreSearch::createState() {
    auto pInstance = (BallPreSearch *)State<BallSprite>::create();
    return pInstance;
}

State<BallSprite>::StateInfo BallSprite::BallPreSearch::run(BallSprite* parent, State<BallSprite>* &newState) {
    return  State<BallSprite>::StateInfo::StateInfo_Next;
}

#pragma mark -
#pragma mark BallNextChain

bool BallSprite::BallNextChain::init() {
    return true;
}

BallSprite::BallNextChain *BallSprite::BallNextChain::createState() {
    auto pInstance = (BallNextChain *)State<BallSprite>::create();
    return pInstance;
}

State<BallSprite>::StateInfo BallSprite::BallNextChain::run(BallSprite* parent, State<BallSprite>* &newState) {
    return  State<BallSprite>::StateInfo::StateInfo_Next;
}
#pragma mark -
#pragma mark BallPreSearch

bool BallSprite::BallSearchFinish::init() {
    return true;
}

BallSprite::BallSearchFinish *BallSprite::BallSearchFinish::createState() {
    auto pInstance = (BallSearchFinish *)State<BallSprite>::create();
    return pInstance;
}

State<BallSprite>::StateInfo BallSprite::BallSearchFinish::run(BallSprite* parent, State<BallSprite>* &newState) {
    return  State<BallSprite>::StateInfo::StateInfo_Next;
}
*/
