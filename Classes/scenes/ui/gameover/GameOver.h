#pragma once

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
private:
	void update(float dt);
	
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOver);
};