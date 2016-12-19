#include "TestCtlDec.h"


TestCtlDec::TestCtlDec()
{
}


TestCtlDec::~TestCtlDec()
{
}

void TestCtlDec::hit(){
	if (this->_next->isMovingUp() == false){
		this->_next->setSpeedY(15);
	}
	eraseMyself();
}

void TestCtlDec::dieOff(){
	this->_next->dieOff();
}

void TestCtlDec::leftAcce(){
	this->_next->leftAcce();
}

void TestCtlDec::RightAcce(){
	this->_next->RightAcce();
}

bool TestCtlDec::isMovingUp(){
	return this->_next->isMovingUp();
}

void TestCtlDec::setSpeedY(double speed){
	this->_next->setSpeedY(speed);
}

void TestCtlDec::setSpeedX(double speed){
	this->_next->setSpeedX(speed);
}