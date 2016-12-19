#include "Boardmap.h"
#include "Board.h"

//std::vector<Board*> Boardmap::_boards_in_back[2];
//Sprite* Boardmap::_back[] = { 0 };
bool Boardmap::init()
{
	if (!Layer::init())
		return false;

	timeval time;
	gettimeofday(&time, 0);
	unsigned int tsrans = time.tv_usec * 1000;
	std::srand(tsrans);

	_back[0] = Sprite::create(BACKGROUND_PICTURE);
	_back[1] = Sprite::create(BACKGROUND_PICTURE);

	_back[0]->setAnchorPoint(Vec2(0, 0));
	this->addChild(_back[0]);

	_back[1]->setFlippedY(true);
	_back[1]->setAnchorPoint(Vec2(0, 0));
	_back[1]->setPosition(0, _back[0]->getContentSize().height);	
	this->addChild(_back[1]);

	return true;
}

void Boardmap::moveDown(double length)
{
	_back[0]->runAction(MoveBy::create(1, Vec2(0, -length)));
	_back[1]->runAction(MoveBy::create(1, Vec2(0, -length)));
	if (_back[0]->getPositionY() < 0&&_back[0]->getPositionY()>_back[1]->getPositionY())
	{
		_back[1]->setPosition(0, _back[0]->getPositionY() + _back[0]->getContentSize().height);	
		_back[1]->removeAllChildren();
		_back[1]->setLocalZOrder(1);
		_back[0]->setLocalZOrder(0);
		_boards_in_back[1].clear();
	}
	if (_back[1]->getPositionY() < 0 && _back[0]->getPositionY()<_back[1]->getPositionY())
	{
		_back[0]->setPosition(0, _back[1]->getPositionY() + _back[1]->getContentSize().height);
		_back[0]->removeAllChildren();
		_back[1]->setLocalZOrder(0);
		_back[0]->setLocalZOrder(1);
		_boards_in_back[0].clear();
	}
}

Board* Boardmap::checkImpact(const Pinball* ball)
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < _boards_in_back[j].size(); i++)
		{
			if (_boards_in_back[j][i]->getPositionY() + _back[j]->getPositionY() < ball->getPositionY()\
				&&_boards_in_back[j][i]->getPositionX() + _boards_in_back[j][i]->getWidth() / 2 > ball->getPositionX()\
				&&_boards_in_back[j][i]->getPositionX() - _boards_in_back[j][i]->getWidth() / 2 <= ball->getPositionX()\
				&&ball->getPositionY() - _boards_in_back[j][i]->getPositionY() - _back[j]->getPositionY() < _boards_in_back[j][i]->getHeight() / 2 + ball->getRadius()
				)
			{
				return _boards_in_back[j][i];
			}
		}
	}
	return 0;
}

void Boardmap::addBoard(Board* board)
{
	bool next = false;
	board->setPosition(board->getPositionX(), getVisiblePosition(board->getPosition()).y);
	if (board->getPosition().y > _back[0]->getContentSize().height)
	{
		next = true;
		board->setPosition(board->getPositionX(), board->getPositionY() - _back[0]->getContentSize().height);
	}
	if (!(_back[0]->isVisible() && next) && (_back[0]->isVisible() || next))
	{
		_back[0]->addChild(board);
		_boards_in_back[0].push_back(board);
	}
	else
	{
		_back[1]->addChild(board);
		_boards_in_back[1].push_back(board);
	}
}