#ifndef _GAMESCENE_
#define _GAMESCENE_
#include"cocos2d.h"
#include "Boardmap.h"
#include "Pinball.h"
//#include "ProcessController.h"

USING_NS_CC;
class GameScene :public Scene
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();

	void addScore(int num){ _score += num; }

	inline Pinball* getBall(){ return _ball; }

	inline Boardmap* getBackground(){ return _boards; }

	void cameraMove(double length)
	{
		_boards->moveDown(length);
		_cameraSpeed = length / 60;
	}

	inline double getCameraSpeed()const{ return _cameraSpeed; }

    inline int getScore()const{return _score;}
    
    void update(float dt);

    void initBoardmap();
    
    void initBall();
private:
	Pinball* _ball;
	Boardmap* _boards;
	double _cameraSpeed;
	int _score;
	Label* _scoreBoard;
};
#endif
