#include "CorePath.h"

CorePath::CorePath(const float& pathPositionY, const float& balloonMovingSpeed)
{
	mPathPositionY = pathPositionY;
	mBalloonMovingSpeed = balloonMovingSpeed;

	mIsTouching = false;
	mIsTouchingRight = true;
}

CorePath::~CorePath()
{
	// Destructor
}