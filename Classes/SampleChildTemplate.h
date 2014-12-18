//
//  SampleChildTemplate.h
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/18.
//
//

#ifndef TumTum_Base_SampleChildTemplate_h
#define TumTum_Base_SampleChildTemplate_h

#include "cocos2d.h"
#include "SampleTemplate.h"

using namespace cocos2d;

template <class PARENT>
class SampleChildTemplate : public SampleTemplate<PARENT>
{
public:
    SampleChildTemplate2 *ret();
};

template <class PARENT>
class SampleChildTemplate2 : public SampleTemplate2<PARENT>
{
public:
    
};


#endif
