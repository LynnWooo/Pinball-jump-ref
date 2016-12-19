#ifndef TESTPROP_H
#define TESTPROP
#include"PropPtype.h"
#include"TestCtlDec.h"

#define TESTPICTURE "spring.png"
#define TESTSIZE Director::getInstance()->getVisibleSize().width / 20 / this->getContentSize().width

class TestProp :public PropPtype{
public:
	float getWidth()const{ return this->getContentSize().width*TESTSIZE; }

	float getHeight()const{ return this->getContentSize().height*TESTSIZE; }

	BaseCtlDec* hit();

	std::string getType()const{ return TESTPICTURE; }

	PropPtype* clone(){ return new TestProp(count++); }

	BaseCtlDec* getDec(){
		return new TestCtlDec();
	}
private:
	static TestProp _prop;

	TestProp();

	TestProp(int i);

	int count;
};

#endif