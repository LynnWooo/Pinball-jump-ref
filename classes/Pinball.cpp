#include "Pinball.h"
#include"ScoreObserver.h"

//void Pinball::update(float dt)
//{
//	speedCtrl();
//	this->setPosition(this->getPositionX() + _speedX, this->getPositionY() + _speedY - _relativeSpeed);
//
//	/*------ref by Lantern------*/
//	_height += _speedY;
//	if (_height > _maxHeight){
//		_maxHeight = _height;
//		UpdateAllObservers();
//	}
//	/*--------------------------------*/
//
//
//	if (this->getPosition().x < -this->getContentSize().width*_scale)
//		this->setPosition(this->getContentSize().width*_scale + Director::getInstance()->getVisibleSize().width, this->getPosition().y);
//	if (this->getPosition().x>Director::getInstance()->getVisibleSize().width + this->getContentSize().width*_scale)
//		this->setPosition(-this->getContentSize().width*_scale, this->getPosition().y);
//
//}

bool Pinball::init()
{
	if (!Sprite::init())
		return false;

	this->initWithFile(BALL_PICTURE);
	_scale = SMALL_SIZE;
	_speedX = 0;
	_speedY = 0;
	_accX = 0;
	_relativeSpeed = 0;
	_radius = this->getContentSize().width*_scale / 2;
	this->setScale(_scale);
	_maxHeight = 0;
	_height = 0;
	_observerList = vector<ScoreObserver*>();

	CCLOG("ball");
	scheduleUpdate();
	return true;
}

Pinball* Pinball::create(int posX, int posY)
{
	Pinball* ball = create();
	ball->setPosition(posX, posY);
	return ball;
}

void Pinball::speedCtrl()
{
	if ((!_accX) && _speedX != 0)	//没按按键时平移速度逐渐减慢
	_speedX+=( _speedX > 0 ? -0.05 : 0.05);

	_speedX += _accX;	//根据按键输入改变平移方向速度
	_speedY -= 0.15;	//向下加速度
}

/*------ref by Lantern------*/
void Pinball::UpdateAllObservers(){
	for (int i = 0; i < _observerList.size(); i++){
		_observerList[i]->OnUpdate(this, (int)_maxHeight);
	}
}

void Pinball::addObserver(ScoreObserver* observer){
	for (int i = 0; i < _observerList.size(); i++){
		if (_observerList[i] == observer) return;
	}

	_observerList.push_back(observer);
}

void Pinball::removeObserver(ScoreObserver* observer){
	for (vector<ScoreObserver*>::iterator i = _observerList.begin(); i != _observerList.end(); i++){
		if (*i == observer){
			_observerList.erase(i);
			break;
		}
	}
}
/*--------------------------------*/