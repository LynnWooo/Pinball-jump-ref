#ifndef ___PINBALL_H_
#define ___PINBALL_H_
#include "cocos2d.h"
#include<vector>
class ScoreObserver;

#define BALL_PICTURE "Ball.png"
#define SMALL_SIZE Director::getInstance()->getVisibleSize().width / 20 / this->getContentSize().width
USING_NS_CC;
using namespace std;

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

//	void update(float dt);

	void addObserver(ScoreObserver* observer);

	void removeObserver(ScoreObserver* observer);

	int getMaxHeight(){ return _maxHeight; }

	void initHeight(){ _maxHeight = 0; }

	double getScale(){ return _scale; }

	void addHeight(double len){
		_height += len;
		if (_height > _maxHeight){
			_maxHeight = _height;
			UpdateAllObservers();
		}
	}

	void dieOff();
private:
	void speedCtrl();
	//
	double _scale;
	double _radius;
	double _accX;
	double _speedX;
	double _speedY;
	double _relativeSpeed;

	double _maxHeight;
	double _height;
	vector<ScoreObserver*> _observerList;

	void UpdateAllObservers();
};
#endif