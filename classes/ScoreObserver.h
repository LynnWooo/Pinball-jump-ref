#include"Pinball.h"

class ScoreObserver{
public:
	virtual void OnUpdate(const Pinball* Sender, int height) = 0;
};
