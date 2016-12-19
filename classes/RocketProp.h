#pragma once
#ifndef ROCKETPROP_H
#define ROCKETPROP_H

#include "PropPtype.h"
#include "RocketCtlDec.h"

#define ROCKETPICTURE "rocket.png"
#define ROCKETSCALE Director::getInstance()->getVisibleSize().width / 15 / this->getContentSize().width

class RocketProp :
	public PropPtype
{
public:
	float getWidth()const{ return this->getContentSize().width*ROCKETSCALE; }

	float getHeight()const{ return this->getContentSize().height*ROCKETSCALE; }

	BaseCtlDec* hit();

	std::string getType()const{ return ROCKETPICTURE; }

	PropPtype* clone(){ return new RocketProp(count++); }

	BaseCtlDec* getDec(){ return NULL; }
private:
	static RocketProp _prop;

	RocketProp();

	RocketProp(int i);

	int count;
};

#endif
