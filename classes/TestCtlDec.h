#pragma once
#ifndef TESTCTLDEC_H
#define TESTCTLDEC_H
#include "BaseCtlDec.h"
class TestCtlDec :
	public BaseCtlDec
{
public:
	TestCtlDec();
	~TestCtlDec();

	void hit();

	void dieOff();

	void leftAcce();

	void RightAcce();

	bool isMovingUp();

	void setSpeedY(double speed);

	void setSpeedX(double speed);
};

#endif