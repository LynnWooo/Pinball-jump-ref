#include "ProcessController.h"
#include "overScene.h"
ProcessController* ProcessController::_ptr = 0;

ProcessController* ProcessController::getInstance()
{
	if (!_ptr)
	{
		_ptr = new ProcessController();
		if (!(_ptr&&_ptr->init()))
		{
			delete _ptr;
			_ptr = 0;
		}
	}
    if(!_ptr->_running)
    {
        
        _ptr->onEnter();
        _ptr->_running=true;
        _ptr->scheduleUpdate();
    }
	return _ptr;
}

bool ProcessController::init()
{
	if (!Node::create())
		return false;
	
	_leftpressed = false;
	_rightpressed = false;
	_difficulty = 1;

	auto kbd = EventListenerKeyboard::create();
	kbd->onKeyPressed = [=](EventKeyboard::KeyCode key, Event *)
	{
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			if (_rightpressed)
				_rightpressed = false;
			_leftpressed = true;
		}; break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			if (_leftpressed)
				_leftpressed = false;
			_rightpressed = true;
		}; break;
		default: break;
		}
	};
	kbd->onKeyReleased = [=](EventKeyboard::KeyCode key, Event *)
	{
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:_leftpressed = false; break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			timeval time;
			gettimeofday(&time, 0);
			unsigned int tsrans = time.tv_usec * 1000;
			std::srand(tsrans);
			_rightpressed = false; 
		} break;
		default: break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kbd, this);

    
    
   
	CCLOG("inited");
	scheduleUpdate();
	return true;
}

void ProcessController::ballctrl()
{
	_scene->getBall()->setAccelaration(_leftpressed ? -0.3 : (_rightpressed ? 0.3 : 0));
	_scene->getBall()->downSpeed(_scene->getCameraSpeed());
}

void ProcessController::update(float dt)
{
	ballctrl();
	//CCLOG("running");
	if (getBall()->getSpeed() < 0)
		checkImpact();
    if(getBall()->getPositionY()<0)
    {
        auto scene=overScene::create(_scene->getBallHeight());
        Director::getInstance()->replaceScene(TransitionSlideInB::create(1,scene));
        removeFromParent();
        //unscheduleUpdate();
        //_scene=0;
        _running=false;
        onExit();
    }
	
}

void ProcessController::checkImpact()
{
	auto board =getBoardmap()->checkImpact(getBall());
	
	if (!board)
		return;

	getBall()->setPosition(getBall()->getPositionX(), getBoardmap()->getVisiblePosition(board->getPosition()).y + board->getHeight() / 2 + getBall()->getRadius());
	if (board->getType() == BOARD_TYPE_1)
	{
		if (getBoardmap()->getVisiblePosition(board->getPosition()).y >= Director::getInstance()->getVisibleSize().height*0.35)
		{
			_scene->cameraMove(getBoardmap()->getVisiblePosition(board->getPosition()).y - 100);
			if (getBoardmap()->haveEmptyMap())
				getBoardmap()->createBoards(_difficulty);
			if (_difficulty > 0.45)_difficulty -= 0.015;
//			_scene->addScore((getBoardmap()->getVisiblePosition(board->getPosition()).y - 100) / _difficulty / _difficulty);
		}
		getBall()->hit();
	}
	board->hit();
	
}

