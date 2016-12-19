#ifndef _BOARDMAP_H_
#define _BOARDMAP_H_
#include "cocos2d.h"
#include "Board.h"
#include "Pinball.h"
#include <vector>
#include"PropPtype.h"
USING_NS_CC;

#define BACKGROUND_PICTURE "background.png"
class Boardmap :public Layer
{
public:
	CREATE_FUNC(Boardmap);

	virtual bool init();

	void addBoard(Board* board);

	void createBoards(double difficulty = 0.9);

	inline float getVisiblePosition()
	{
		if (_back[0]->isVisible())
			return _back[0]->getPositionY();
		else
			return _back[1]->getPositionY();
	}

	inline Vec2 getVisiblePosition(const Vec2 pos)
	{
		Vec2 vec = pos;
		if (_back[0]->isVisible())
			vec.y += _back[0]->getPositionY();
		else
			vec.y += _back[1]->getPositionY();
		if (vec.y <-500)
			vec.y += _back[0]->getContentSize().height;
		else if(vec.y>=_back[0]->getContentSize().height)
			vec.y -= _back[0]->getContentSize().height;
		return vec;
	}

	Entity* checkImpact(const Pinball* ball);

	bool isMoving(){ return (_back[0]->isVisible() ? _back[1] : _back[0])->getNumberOfRunningActions()!=0; }

	void moveDown(double length);

	bool haveEmptyMap(){ return _boards_in_back[0].size() == 0 ? true : (_boards_in_back[1].size() == 0 ? true : false); }
private:	
    
	std::vector<Entity*> _boards_in_back[2];
	Sprite* _back[2];
};
#endif