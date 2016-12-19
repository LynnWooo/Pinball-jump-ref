#ifndef _BOARD__H_
#define _BOARD__H_
#include "cocos2d.h"
#include <string>
USING_NS_CC;

#define BOARD_TYPE_1 "stdboard.png"
#define BOARD_TYPE_2 "glassboard.png"
#define BOARDS_PER_LINE 6
#define VIEWWIDTH Director::getInstance()->getVisibleSize().width
//#define TYPE_3 "roundboard.png"
//#define TYPE_4 "triangleboard.png"



class Board :public Sprite
{
public:
	CREATE_FUNC(Board);

	virtual bool init();
		
	static Board* create(int posX, int posY, std::string type);
	
	inline float getWidth()const{return this->getContentSize().width*_scale;}

	inline float getHeight()const{ return this->getContentSize().height*_scale; }

	inline std::string getType()const{ return _type; }

    void update(float dt);

	void hit();

	void setMoveable(bool direction);
	

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
