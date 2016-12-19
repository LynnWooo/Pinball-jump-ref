#include "overScene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "ProcessController.h"
bool overScene::init(){
    if (!Scene::init())
        return false;
    auto sprite=Sprite::create("gameover.png");
    sprite->setPosition(Director::getInstance()->getVisibleSize()/2);
    this->addChild(sprite);

    MenuItemImage* restartMenuItem = MenuItemImage::create(
                                                         "playagain1.png",
                                                         "playagain2.png",
                                                         CC_CALLBACK_1(overScene::restartaction, this));
    
    MenuItemImage* backMenuItem = MenuItemImage::create(
                                                        "menu1.png",
                                                        "menu2.png",
                                                        CC_CALLBACK_1(overScene::menuaction, this));
    restartMenuItem->setPosition(300, 200);
    restartMenuItem->setScale(0.5);
    backMenuItem->setPosition(350,150);
    backMenuItem->setScale(0.5);
    Menu* mu = Menu::create(restartMenuItem,backMenuItem, NULL);
    mu->setPosition(Point::ZERO);
    this->addChild(mu);
    scheduleUpdate();
    _score = 0;
    
    return true;
}

void overScene::restartaction(Ref*)
{
    Director::getInstance()->replaceScene(GameScene::create());
}

void overScene::menuaction(Ref*)
{
    Director::getInstance()->replaceScene(StartScene::create());

}

overScene* overScene::create(int score){
    auto scene = create();
    
    __String* str = __String::createWithFormat("%d", score);
    auto lb = Label::create(str->getCString(), "Marker Felt", 30);
    lb->setColor(Color3B(0, 0, 0));
    
        scene->addChild(lb);
    lb->setPosition(365, 440);
    scene->_score = score;
    return scene;
}
