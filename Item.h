

#ifndef __Pinball_Jump__Item__
#define __Pinball_Jump__Item__
#include "cocos2d.h"

USING_NS_CC;
class Item:public Sprite
{
public:
    CREATE_FUNC(Item);
    
    virtual bool init()
    {
        if(!Sprite::init())
            return false;
        
        return true;
    }
private:
    std::string name;
    
};


#endif /* defined(__Pinball_Jump__Item__) */
