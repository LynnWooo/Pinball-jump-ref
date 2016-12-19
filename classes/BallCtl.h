#pragma once
#ifndef ___BALLCTL_H_
#define ___BALLCTL_H_

#include "BaseCtl.h"
#include"Pinball.h"
#include"Boardmap.h"
class BallCtl :
	public BaseCtl
{
public:
	BallCtl();
	~BallCtl();

	void hit()		{ if (_speedY <= 0)_speedY = 7; }

	void dieOff()	{}

	void leftAcce()	{ if ((_speedX + _maxSpeedX) > 0)_speedX -= _xAcce; }

	void RightAcce(){ if (_speedX < _maxSpeedX)_speedX += _xAcce; }

	void update(float delta);

	void bindBall(Pinball* ball) { _ball = ball; }

	void bindBack(Boardmap* back){ _back = back; }

	bool isMovingUp(){ return _speedY > 0; }

	void setSpeedY(double speed){
		_speedY = speed;
	}

	void setSpeedX(double speed){
		_speedX = speed;
	}
private:
	Pinball*  _ball;
	Boardmap* _back;

	const double _downAcce  =  0.15;
	const double _xAcce  =  0.3;
	const double _yAcce  =  0.15;
	const double _recoverAcce =  0.05;
	const double _maxSpeedX =  6;
	
	double _speedY;
	double _speedX;
	double _relativeSpeed;
};

#endif