#ifndef ___PINBALL_H_
#define ___PINBALL_H_
#include "cocos2d.h"

#define BALL_PICTURE "Ball.png"
#define SMALL_SIZE Director::getInstance()->getVisibleSize().width / 20 / this->getContentSize().width
USING_NS_CC;

class Pinball :public Sprite
{
public:
	CREATE_FUNC(Pinball);

	virtual bool init();

	static Pinball* create(int posX, int posY);

	inline void hit(){ _speedY = 7 ; }

	inline double getSpeed()const{ return _speedY; }

	inline double getRadius()const{ return _radius; }

	void setAccelaration(double acc){ _accX = acc; }

	inline void downSpeed(double speed){ _relativeSpeed = speed; }

	void update(float dt);
private:
	void speedCtrl();
	//
	double _scale;
	double _radius;
	double _accX;
	double _speedX;
	double _speedY;
	double _relativeSpeed;
};
#endif