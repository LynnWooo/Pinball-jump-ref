#include"Pinball.h"

class ScoreObserver{
public:
	virtual void OnUpdate(Pinball* Sender, int height) = 0;
};
