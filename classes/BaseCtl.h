#ifndef BASECTL_H
#define BASECTL_H
#include "cocos2d.h"
extern class BaseCtlDec;

USING_NS_CC;

class BaseCtl:
	public Node
{
public:
	BaseCtl();
	~BaseCtl();

	virtual void hit() = 0;

	virtual void dieOff() = 0;

	virtual void leftAcce() = 0;

	virtual void RightAcce() = 0;

	virtual bool isMovingUp() = 0;

	virtual void setSpeedY(double speed) = 0;

	virtual void setSpeedX(double speed) = 0;

	void setPre(BaseCtlDec* p){ }
};

#endif

