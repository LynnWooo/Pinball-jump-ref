#include"TestProp.h"

TestProp TestProp::_prop;

BaseCtlDec* TestProp::hit(){
	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("spring"));
	auto action = Repeat::create(animate, 1);
	auto callFunc = CallFunc::create([=](){ this->setVisible(false); });
	auto sequence = Sequence::create(action, callFunc,NULL);

	this->runAction(sequence);
	return new TestCtlDec();
}

TestProp::TestProp(){
	count = 0;
	addProp(this);
}

TestProp::TestProp(int i){ 
	initWithFile(TESTPICTURE);
	this->setScale(TESTSIZE);

	if (i == 0){
		Vector<SpriteFrame*> spriteFrameVec;
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		char path[256] = { 0 };

		for (int i = 1; i <= 3; i++){
			sprintf_s(path, "spring\\%d.png", i);

			float x = Director::getInstance()->getVisibleSize().width / 20;

			SpriteFrame* spriteFrame = SpriteFrame::create(path, Rect(0, (i - 1)*getContentSize().height, getContentSize().width, getContentSize().height));
			spriteFrameCache->addSpriteFrame(spriteFrame, path);
			spriteFrameVec.pushBack(spriteFrame);
		}

		auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "spring");
	}
}