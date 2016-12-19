#pragma once
#ifndef BASECTLDEC_H
#define BASECTLDEC_H
#include"BaseCtl.h"

extern class ProcessController;

class BaseCtlDec :
	public BaseCtl
{
public:
	BaseCtlDec();
	~BaseCtlDec();

	void setNext(BaseCtl* p){ _next = p; }

	void setPre(BaseCtlDec* p){ _pre = p; }
protected:
	void eraseMyself();

	BaseCtl* _next;

private:
	BaseCtlDec* _pre;
};

#endif