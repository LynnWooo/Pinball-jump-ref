#ifndef _STARTGAME_H_
#define _STARTGAME_H_
#include "cocos2d.h"
#include "Boardmap.h"
#include "Pinball.h"
#include "GameScene.h"
USING_NS_CC;
class StartScene :public Scene
{
public:
	CREATE_FUNC(StartScene);

    virtual bool init();

    void startaction(Ref*);

    void helpaction(Ref*);

    void update(float dt);
private:
	Board* _demoBoard;;
	Pinball* _demoBall;
};
#endif
