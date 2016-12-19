#include "RocketProp.h"

RocketProp RocketProp::_prop;

BaseCtlDec* RocketProp::hit(){
	this->setVisible(false);
	return new RocketCtlDec();
}

RocketProp::RocketProp(){
	count = 0;
	addProp(this);
}

RocketProp::RocketProp(int i){
	initWithFile(ROCKETPICTURE);
	this->setScale(ROCKETSCALE);
}