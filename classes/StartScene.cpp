#include "StartScene.h"
#include "simpleAudioEngine.h"
bool StartScene::init()
{
    if (!Scene::init())
        return false;
    
    auto sprite = Sprite::create(BACKGROUND_PICTURE);
    sprite->setPosition(Director::getInstance()->getVisibleSize()/2);
    this->addChild(sprite);
    MenuItemImage* startMenuItem = MenuItemImage::create(
                                                         "play1.png",
                                                         "play2.png",
                                                         CC_CALLBACK_1(StartScene::startaction, this));
    
    MenuItemImage* helpMenuItem = MenuItemImage::create(
                                                        "toy1.png",
                                                        "toy2.png",
                                                        CC_CALLBACK_1(StartScene::helpaction, this));
    
    
    startMenuItem->setPosition(300, 300);
    startMenuItem->setScale(0.5);
    helpMenuItem->setPosition(300, 200);
    helpMenuItem->setScale(0.5);
    
    _demoBoard = Board::create(100, 50, BOARD_TYPE_1);
    _demoBall = Pinball::create(100, 200);
    
    auto lb=Label::create("Pinball Jump", "Marker Felt", 45);
    lb->setColor(Color3B(87, 61, 29));
    lb->setPosition(200, 500);
    this->addChild(lb);
    this->addChild(_demoBall);
    this->addChild(_demoBoard);
    
    Menu* mu = Menu::create(startMenuItem,helpMenuItem, NULL);
    mu->setPosition(Point::ZERO);
    this->addChild(mu);
    scheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("break.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("hit.mp3");
    return true;
}

void StartScene::startaction(Ref*){
    Director::getInstance()->replaceScene(GameScene::create());
}

void StartScene::helpaction(Ref*){
    Director::getInstance()->replaceScene(GameScene::create());
}

void StartScene::update(float dt)
{
    if (_demoBoard->getPositionY() < _demoBall->getPositionY()\
        &&_demoBall->getPositionY() - _demoBoard->getPositionY() < _demoBoard->getHeight() / 2 + _demoBall->getRadius()
        && _demoBall->getSpeed() < 0)
    {
        _demoBall->setPosition(_demoBall->getPositionX(), _demoBoard->getPositionY() +
                               _demoBoard->getHeight() / 2 + _demoBall->getRadius());
        _demoBall->hit();
        _demoBoard->hit();
    }
}