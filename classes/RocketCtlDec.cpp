#include "RocketCtlDec.h"


RocketCtlDec::RocketCtlDec()
{
	duration = 0;

	_sprite = Sprite::create(ROCKETDECPICTURE);
	_sprite->setScale(Director::getInstance()->getVisibleSize().width/5  / _sprite->getContentSize().width);
	_sprite->setPosition(Vec2(_sprite->getContentSize().width/2-28, -_sprite->getContentSize().height/2+20));

	this->addChild(_sprite);
	scheduleUpdate();
}


RocketCtlDec::~RocketCtlDec()
{
}

void RocketCtlDec::hit(){
	this->_next->hit();
}

void RocketCtlDec::dieOff(){
	this->_next->dieOff();
}

void RocketCtlDec::leftAcce(){
	this->_next->leftAcce();
}

void RocketCtlDec::RightAcce(){
	this->_next->RightAcce();
}

bool RocketCtlDec::isMovingUp(){
	return this->_next->isMovingUp();
}

void RocketCtlDec::setSpeedY(double speed){
	this->_next->setSpeedY(speed);
}

void RocketCtlDec::setSpeedX(double speed){
	this->_next->setSpeedX(speed);
}

void RocketCtlDec::update(float dt){
	duration += dt;
	if (duration <= 2){
		this->setSpeedY(15);
	}
	else{
		unscheduleUpdate();
		eraseMyself();
	}
}