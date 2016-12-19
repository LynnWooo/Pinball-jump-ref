#include"ScoreBoard.h"

void ScoreBoard::OnUpdate(Pinball* Sender, int height){
	if (_label != NULL){
		__String* str = __String::createWithFormat("Height: %d", height);
		_label->setString(str->getCString());
	}
}