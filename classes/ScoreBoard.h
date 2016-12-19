#include"ScoreObserver.h"
#include"cocos2d.h"

class ScoreBoard :public ScoreObserver{
private:
	Label* _label;

public:
	void OnUpdate(const Pinball* Sender, int height);

	void bindLabel(Label* l){
		_label = l;
	}
};