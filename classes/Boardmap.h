#ifndef _BOARDMAP_H_
#define _BOARDMAP_H_
#include "cocos2d.h"
#include "Board.h"
#include "Pinball.h"
#include <vector>
USING_NS_CC;

#define BACKGROUND_PICTURE "background.png"
class Boardmap :public Layer
{
public:
	CREATE_FUNC(Boardmap);

	virtual bool init();

	void addBoard(Board* board);

	void createBoards(double difficulty=0.9)
	{
		int k = 0;
		if (!_boards_in_back[1].size())
			k = 1;
		bool must = false;
		for (int i = 0; i < 24; i++)
		{
			if (must)
			{
				auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2, i * 40 + CCRANDOM_0_1() * 10, BOARD_TYPE_1);
				if (CCRANDOM_0_1() < (1 - difficulty) * 2&&i<15)
					board->setMoveable(CCRANDOM_0_1() < 0.5);
				_back[k]->addChild(board);
				_boards_in_back[k].push_back(board);
				must = false;
			}
			else
			switch ((int)(CCRANDOM_0_1() * 23) % (int)(difficulty*5-1))
			{
			case 0:{
				must = true;
			}break;
			case 1:{
				auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2, i * 40 + CCRANDOM_0_1() * 20, BOARD_TYPE_1);
				if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i < 15)
					board->setMoveable(CCRANDOM_0_1() < 0.5);
				_back[k]->addChild(board);
				_boards_in_back[k].push_back(board);
			}break;
			case 2:{
				for (int j = 0; j < 2; j++)
				{
					auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH / 2 - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2 + VIEWWIDTH / 2 * j, i * 40 + CCRANDOM_0_1() * 20, BOARD_TYPE_1);
					if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i < 15)
						board->setMoveable(CCRANDOM_0_1() < 0.5);
					_back[k]->addChild(board);
					_boards_in_back[k].push_back(board);
				}
			}break;
			case 3:{
				for (int j = 0; j < 3; j++)
				{
                    auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH / 3 - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2 + VIEWWIDTH / 3 * j, i * 40 + CCRANDOM_0_1() * 20, CCRANDOM_0_1()>0.9? BOARD_TYPE_2:BOARD_TYPE_1);
					if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i < 15)
						board->setMoveable(CCRANDOM_0_1() < 0.5);
					_back[k]->addChild(board);
					_boards_in_back[k].push_back(board);
				}
			}break;
			}
		}
	}

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

	Board* checkImpact(const Pinball* ball);

	bool isMoving(){ return (_back[0]->isVisible() ? _back[1] : _back[0])->getNumberOfRunningActions()!=0; }

	void moveDown(double length);

	bool haveEmptyMap(){ return _boards_in_back[0].size() == 0 ? true : (_boards_in_back[1].size() == 0 ? true : false); }
private:	
    
	std::vector<Board*> _boards_in_back[2];
	Sprite* _back[2];
};
#endif