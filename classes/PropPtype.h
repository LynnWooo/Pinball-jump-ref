#pragma once
#ifndef PROPPTYPE_H
#define PROPPTYPE_H
#include "Entity.h"
#include"BaseCtlDec.h"
class PropPtype :
	public Entity
{
public:
	PropPtype();
	~PropPtype();

	virtual PropPtype* clone() = 0;

	static PropPtype* getRandomProp(){
		int i = (int)(CCRANDOM_0_1()*_size);
		return _props[i]->clone();
	}

protected:
	static void addProp(PropPtype* p){
		_props[_size++] = p;
	}
private:
	static int _size;

	static PropPtype* _props[15];
};

#endif