#include "Board.h"
#include"Boardmap.h"
#include "simpleAudioEngine.h"
void Board::hit()
{
    if(_type==BOARD_TYPE_1)
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
    if (_type == BOARD_TYPE_2)
	{
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("break.mp3");
        this->initWithFile("glassboard_1.png");
        this->setScale(_scale);
        Board* board=create();
        board->initWithFile("glassboard_2.png");
        board->setPosition(this->getPosition());
        board->setScale(_scale);
        this->_parent->addChild(board);
        
        this->runAction(MoveBy::create(3, Vec2(-50,-400)));
        board->runAction(MoveBy::create(3, Vec2(50,-400)));
        
	}
}

void Board::setMoveable(bool direction)//direction==true,go up&down,direction==false,go left&right
{
	_moveable = true;
	if (direction)
		this->runAction(RepeatForever::create(Sequence::create(\
		MoveTo::create(2, Vec2(this->getPositionX(), this->getPosition().y + 150)), \
		MoveTo::create(3, Vec2(this->getPositionX(), this->getPosition().y)), \
		NULL)));
	else
	{
		_speedX = CCRANDOM_0_1() < 0.5 ? 2 : -2;
		scheduleUpdate();
	}
}

bool Board::init()
{
	if (!Sprite::init())
		return false;

	_has_item = false;
	_moveable = false;

	return true;

}

Board* Board::create(int posX, int posY, std::string type)
{
	Board* board = create();

	board->_type = (type);
	board->initWithFile(board->_type);
	board->_scale = VIEWWIDTH / board->getContentSize().width / BOARDS_PER_LINE;
	board->setScale(board->_scale);
	board->setPosition(posX, posY);

	return board;
}

void Board::update(float dt)
{
    if (getPositionX() >= VIEWWIDTH - getWidth() / 2 || getPositionX() <= getWidth() / 2)
        _speedX = -_speedX;
    setPosition(Vec2(getPositionX() + _speedX, getPositionY()));
}
