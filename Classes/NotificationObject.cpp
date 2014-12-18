//
//  NotificationObject.cpp
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/17.
//
//

#include "NotificationObject.h"

NotificationObject::NotificationObject()
{
}

NotificationObject::~NotificationObject()
{
    NotificationCenter::getInstance()->removeObserver(this, kTouchBegan);
    NotificationCenter::getInstance()->removeObserver(this, kTouchMoved);
    NotificationCenter::getInstance()->removeObserver(this, kTouchEnd);
}

void NotificationObject::callback(Ref *sender) {
    log("called NotificationObject method");
}

void NotificationObject::setNotice() {
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationObject::callback), kTouchBegan, NULL);
}

void NotificationObject::postNotice(const std::string &key, Ref *sender)
{
    NotificationCenter::getInstance()->postNotification(key, sender);
}