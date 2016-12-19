#pragma once
#ifndef ROCKETCTLDEC_H
#define ROCKETCTLDEC_H
#include "BaseCtlDec.h"

#define ROCKETDECPICTURE "fire.png"

class RocketCtlDec :
	public BaseCtlDec
{
public:
	RocketCtlDec();
	~RocketCtlDec();

	void hit();

	void dieOff();

	void leftAcce();

	void RightAcce();

	bool isMovingUp();

	void setSpeedY(double speed);

	void setSpeedX(double speed);

	Sprite* _sprite;

	void update(float dt);

	float duration;
};

#endif
