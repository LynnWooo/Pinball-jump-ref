#include "GameScene.h"
#include "ProcessController.h"

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	_cameraSpeed = 0;
	initBoardmap();//_boards = Boardmap::create();
	initBall();//_ball = Pinball::create();

	this->addChild(_boards);
	this->addChild(_ball);

	_score = 0;

	__String* str = __String::createWithFormat("%d", _score);
	_scoreBoard = Label::create(str->getCString(), "Marker Felt", 30);
    _scoreBoard->setPosition(40, Director::getInstance()->getVisibleSize().height-40);
	this->addChild(_scoreBoard);

	ProcessController::getInstance()->setScene(this);
	this->addChild(ProcessController::getInstance());
	scheduleUpdate();
    //ProcessController::getInstance()->scheduleUpdate();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3");
	return true;
}
void GameScene::initBoardmap()
{
    _boards = Boardmap::create();
    
    for (int i = 0; i < 6; i++)//init the bottom line with boards
    {
        auto board = Board::create((VIEWWIDTH / BOARDS_PER_LINE)*(i + 0.5), 20, BOARD_TYPE_1);
        _boards->addBoard(board);
    }
    
    for (int i = 0; i < 23; i++)
    {
        auto board = Board::create(CCRANDOM_0_1()*VIEWWIDTH, (i+1) * 40+10, BOARD_TYPE_1);
        _boards->addBoard(board);
    }
    
    auto board = Board::create(CCRANDOM_0_1()*VIEWWIDTH, 100, BOARD_TYPE_1);
    board->setMoveable(true);
    
    auto board2=Board::create(CCRANDOM_0_1()*VIEWWIDTH,400,BOARD_TYPE_2);
    board2->setMoveable(true);
    _boards->addBoard(board);
    _boards->addBoard(board2);
}

void GameScene::update(float dt)
{
    if (!_boards->isMoving())
        _cameraSpeed = 0;
    
    __String* str = __String::createWithFormat("%d", _score);
    _scoreBoard->setString(str->getCString());
    
}
void GameScene::initBall()//init the ball  randomly in 1/4~3/4 of the screen
{
    timeval time;
    gettimeofday(&time, 0);
    unsigned int tsrans = time.tv_usec * 1000;
    std::srand(tsrans);
    
    _ball = Pinball::create(CCRANDOM_0_1()*Director::getInstance()->getVisibleSize().width / 2 \
                            + Director::getInstance()->getVisibleSize().width / 4, 200);
    CCLOG("OK");
}