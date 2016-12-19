#include "Pinball.h"

void Pinball::update(float dt)
{
	speedCtrl();
	this->setPosition(this->getPositionX() + _speedX, this->getPositionY() + _speedY - _relativeSpeed);
	
	if (this->getPosition().x < -this->getContentSize().width*_scale)
		this->setPosition(this->getContentSize().width*_scale + Director::getInstance()->getVisibleSize().width, this->getPosition().y);
	if (this->getPosition().x>Director::getInstance()->getVisibleSize().width + this->getContentSize().width*_scale)
		this->setPosition(-this->getContentSize().width*_scale, this->getPosition().y);

}

bool Pinball::init()
{
	if (!Sprite::init())
		return false;

	this->initWithFile(BALL_PICTURE);
	_scale = SMALL_SIZE;
	_speedX = 0;
	_speedY = 0;
	_accX = 0;
	_relativeSpeed = 0;
	_radius = this->getContentSize().width*_scale / 2;
	this->setScale(_scale);

	CCLOG("ball");
	scheduleUpdate();
	return true;
}

Pinball* Pinball::create(int posX, int posY)
{
	Pinball* ball = create();
	ball->setPosition(posX, posY);
	return ball;
}

void Pinball::speedCtrl()
{
	if ((!_accX) && _speedX != 0)
	_speedX+=( _speedX > 0 ? -0.05 : 0.05);
	_speedX += _accX;
	_speedY -= 0.15;
}