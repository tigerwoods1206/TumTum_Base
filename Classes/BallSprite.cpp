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
        this->setOpacity(255);
    }
    else if (state == ballHilightType::kTouch) {
        this->setOpacity(255);
    }
    else if (state == ballHilightType::kFirstTouch) {
        this->setOpacity(255);
    }

    else if (state == ballHilightType::kChain) {
        this->setOpacity(40);
    }
    else if (state == ballHilightType::kAdjacent) {
        this->setOpacity(100);
    }
    else {
        this->setOpacity(255);
    }
}
