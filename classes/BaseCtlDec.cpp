#include "BaseCtlDec.h"
#include"ProcessController.h"


BaseCtlDec::BaseCtlDec()
{
	_pre = NULL;
}


BaseCtlDec::~BaseCtlDec()
{
}

void BaseCtlDec::eraseMyself(){
	this->removeFromParent();
	this->unscheduleUpdate();

	if (_pre == NULL){
		ProcessController::getInstance()->bindCtl(_next);
	}
	else{
		_pre->setNext(_next);
	}
}