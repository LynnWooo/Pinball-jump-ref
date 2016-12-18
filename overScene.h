#ifndef _OVERSCENE_H
#define _OVERSCENE_H 
#include "cocos2d.h"

USING_NS_CC;
class overScene :
	public Scene
{
public:
	CREATE_FUNC(overScene);

    virtual bool init();

    static overScene* create(int score);
    
    void restartaction(Ref*);
    
    void menuaction(Ref*);
private:
	int _score;
};
#endif
