#include "BallCtl.h"


BallCtl::BallCtl()
{
	_speedX = 0;
	_speedY = 0;
	_relativeSpeed = 0;
	scheduleUpdate();
}


BallCtl::~BallCtl()
{
}

void BallCtl::update(float dt){
	//position control
	_ball->setPosition(_ball->getPositionX() + _speedX, _ball->getPositionY() + _speedY - _relativeSpeed);

	//speed control
	if (_speedX != 0){
		if (_speedX < 0)_speedX += _recoverAcce;
		else _speedX -= _recoverAcce;
	}
	_speedY -= _yAcce;

	//reflash the height of ball
	_ball->addHeight(_speedY);
	//if ball is over half of the back and speedY > 0 move the back next time
	if (_relativeSpeed != 0){
		_back->moveDown(_relativeSpeed);
	}

	if (_speedY > 0 && _ball->getPositionY() > Director::getInstance()->getVisibleSize().height / 2){
		_relativeSpeed = _speedY;
	}
	else{
		_relativeSpeed = 0;
	}
	//if ball is beyond the screen
	if (_ball->getPosition().y < 0) dieOff();

	if (_ball->getPosition().x < -_ball->getContentSize().width*_ball->getScale())
		_ball->setPosition(_ball->getContentSize().width*_ball->getScale() + Director::getInstance()->getVisibleSize().width, _ball->getPosition().y);
	if (_ball->getPosition().x>Director::getInstance()->getVisibleSize().width + _ball->getContentSize().width*_ball->getScale())
		_ball->setPosition(-_ball->getContentSize().width*_ball->getScale(), _ball->getPosition().y);
}