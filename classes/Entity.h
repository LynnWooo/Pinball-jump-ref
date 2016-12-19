#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "cocos2d.h"
#include"BaseCtlDec.h"
#include<string>

extern class Pinball;

USING_NS_CC;

class Entity:public Sprite
{
public:
	Entity(){};
	~Entity(){};

	virtual float getWidth()const = 0;

	virtual float getHeight()const = 0;

	virtual BaseCtlDec* hit() = 0;

	virtual std::string getType()const = 0;

	virtual BaseCtlDec* getDec() = 0;

};

#endif
