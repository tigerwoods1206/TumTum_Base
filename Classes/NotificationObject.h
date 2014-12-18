//
//  NotificationObject.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/17.
//
//

#ifndef __TumTum_Base__NotificationObject__
#define __TumTum_Base__NotificationObject__

#include "cocos2d.h"

#define kTouchBegan "TouchBegan"
#define kTouchMoved "TouchMoved"
#define kTouchEnd   "TouchEnd"

using namespace cocos2d;

class NotificationObject : public Node
{
public:
    NotificationObject();
    
    virtual ~NotificationObject();
    
    CREATE_FUNC(NotificationObject);
    virtual void callback(Ref *sender);
    void postNotice(const std::string &key, Ref *sender);
    void setNotice();
};

#endif /* defined(__TumTum_Base__NotificationObject__) */
