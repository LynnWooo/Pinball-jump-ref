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
//	_back[0]->runAction(MoveBy::create(1, Vec2(0, -length)));
//	_back[1]->runAction(MoveBy::create(1, Vec2(0, -length)));
	_back[0]->setPosition(_back[0]->getPositionX(), _back[0]->getPositionY() - length);
	_back[1]->setPosition(_back[1]->getPositionX(), _back[1]->getPositionY() - length);

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

Entity* Boardmap::checkImpact(const Pinball* ball)
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < _boards_in_back[j].size(); i++)
		{
			if (_boards_in_back[j][i]->isVisible()&&_boards_in_back[j][i]->getPositionY() + _back[j]->getPositionY() < ball->getPositionY()\
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

void Boardmap::createBoards(double difficulty)
{
	int k = 0;
	if (!_boards_in_back[1].size())	//如果背景1中没有板子就生成背景1的板子
		k = 1;
	bool must = false;

	for (int i = 0; i < 24; i++)
	{
		//CCRANDOM_0_1返回一个0 1之间的随机数
		if (must)
		{
			//must动作 与case 1完全一致
			auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2, i * 40 + CCRANDOM_0_1() * 10, BOARD_TYPE_1);
			if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i<15)	//一定的概率设置为可移动，且只有前15次循环有可能
				board->setMoveable(CCRANDOM_0_1() < 0.5);

			_back[k]->addChild(board);
			_boards_in_back[k].push_back(board);
			must = false;
		}
		else
			
			switch ((int)(CCRANDOM_0_1() * 23) % (int)(difficulty * 5 - 1))	//a[0~23] b[1~4] c=a%b c[0~3]
		{
			case 0:{
				//当difficulty过小时（<0.6）必定触发 在下一次循环触发must动作
				must = true;
			}break;
			case 1:{
				//只产生一块板子，板子类型是木板，位置算法不考虑
				auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2, i * 40 + CCRANDOM_0_1() * 20, BOARD_TYPE_1);
				if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i < 15)	//一定的概率设置为可移动，且只有前15次循环有可能	
					board->setMoveable(CCRANDOM_0_1() < 0.5);

				_back[k]->addChild(board);
				_boards_in_back[k].push_back(board);
			}break;
			case 2:{
				//产生两块板子，板子类型是木板，位置算法不考虑
				for (int j = 0; j < 2; j++)
				{
					auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH / 2 - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2 + VIEWWIDTH / 2 * j, i * 40 + CCRANDOM_0_1() * 20, BOARD_TYPE_1);
					if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i < 15)	//一定的概率设置为可移动，且只有前15次循环有可能
						board->setMoveable(CCRANDOM_0_1() < 0.5);

					_back[k]->addChild(board);
					_boards_in_back[k].push_back(board);
				}
			}break;
			case 3:{
				//产生三块板子，板子类型可能是玻璃板，位置算法不考虑
				for (int j = 0; j < 3; j++)
				{
					//0.1的概率是玻璃板 
					auto board = Board::create(CCRANDOM_0_1()*(VIEWWIDTH / 3 - VIEWWIDTH / BOARDS_PER_LINE) + VIEWWIDTH / BOARDS_PER_LINE / 2 + VIEWWIDTH / 3 * j, i * 40 + CCRANDOM_0_1() * 20, CCRANDOM_0_1()>0.9 ? BOARD_TYPE_2 : BOARD_TYPE_1);
					if (CCRANDOM_0_1() < (1 - difficulty) * 2 && i < 15)	//一定的概率设置为可移动，且只有前15次循环有可能
						board->setMoveable(CCRANDOM_0_1() < 0.5);

					_back[k]->addChild(board);
					_boards_in_back[k].push_back(board);
				}
			}break;
		}
		//switch end
	}
	//for 24 times end

	//添加道具
	for (int i = 0; i < _boards_in_back[k].size(); i++){
		if (_boards_in_back[k][i]->getType() == BOARD_TYPE_1&&((Board*)_boards_in_back[k][i])->isMoving() == false){
			PropPtype* prop = PropPtype::getRandomProp();
			Board* tmpBoard = (Board*)_boards_in_back[k][i];
			prop->setPosition(tmpBoard->getPosition().x, tmpBoard->getPosition().y + tmpBoard->getHeight());

			_back[k]->addChild(prop);
			_boards_in_back[k].push_back(prop);

//			break;
		}
	}
}