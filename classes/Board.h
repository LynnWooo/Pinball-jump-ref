#ifndef _BOARD__H_
#define _BOARD__H_
#include "cocos2d.h"
#include <string>
#include"Entity.h"
USING_NS_CC;

#define BOARD_TYPE_1 "stdboard.png"
#define BOARD_TYPE_2 "glassboard.png"
#define BOARDS_PER_LINE 6
#define VIEWWIDTH Director::getInstance()->getVisibleSize().width
//#define TYPE_3 "roundboard.png"
//#define TYPE_4 "triangleboard.png"



class Board :public Entity
{
public:
	virtual bool init();
		
	static Board* create(int posX, int posY, std::string type);
	
	float getWidth()const{return this->getContentSize().width*_scale;}

	float getHeight()const{ return this->getContentSize().height*_scale; }

	inline std::string getType()const{ return _type; }

    void update(float dt);

	BaseCtlDec* hit();

	void setMoveable(bool direction);

	bool isMoving(){ return _moveable; }

	BaseCtlDec* getDec(){ return NULL; }
	
	CREATE_FUNC(Board);
private:
	//parameters
	bool _has_item;
	bool _moveable;
	double _speedX;
	double _speedY;
	std::string _type;
	float _scale;
	//bool _child_of;//child of _back1?true:false;
};
#endif
