#ifndef _PROCEXXXXXXXX_H_
#define _PROCEXXXXXXXX_H_
#include "cocos2d.h"
#include "GameScene.h"
#include "Pinball.h"
#include "Boardmap.h"
#include "Board.h"
#include "simpleAudioEngine.h"
#include "BaseCtl.h"
USING_NS_CC;

class ProcessController : public Node
{
public:
	static ProcessController* getInstance();

	inline Pinball* getBall()const{ return _scene->getBall(); }

	inline Boardmap* getBoardmap()const{ return _scene->getBackground(); }

	void setScene(GameScene* scene){ 
		_scene = scene;
		_ballCtl = _scene->getBallCtl();
	}

	void bindCtl(BaseCtl* controller){
		_ballCtl = controller;
	}

	void update(float dt);

	void checkImpact();

	void ballctrl();
	
private:
	ProcessController(){}
	virtual ~ProcessController(){}
	virtual bool init();
	//Parameters below
	static ProcessController* _ptr;
	GameScene* _scene;
	BaseCtl* _ballCtl;
	bool _leftpressed;
	bool _rightpressed;
	double _difficulty;
    bool _running;
};
#endif
