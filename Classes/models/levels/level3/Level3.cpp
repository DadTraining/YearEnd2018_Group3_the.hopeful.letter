#include "Level3.h"
#include "common/Definition.h"

Level3::Level3(cocos2d::Scene *scene) : CoreLevel()
{
    mIndex = 0;

    float visibleSizeHight = cocos2d::Director::getInstance()->getVisibleSize().height;

    mCoreLevelFrame.push_back(new Level3Frame1(scene));
    mCoreLevelFrame.push_back(new Level3Frame3(scene));
    mCoreLevelFrame.push_back(new Level3Frame4(scene));
	mCoreLevelFrame.push_back(new Level3Frame2(scene));

    for (int i = 0; i < mCoreLevelFrame.size(); i++)
    {
        mCoreLevelFrame.at(i)->SetPositionY(i * visibleSizeHight + visibleSizeHight);
    }

    mCirclePathExtend = new CirclePathExtend(scene);

    // Create physics contact
    mPhysicsContact = cocos2d::EventListenerPhysicsContact::create();
    mPhysicsContact->onContactBegin = CC_CALLBACK_1(Level3::OnContactBegin, this);
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mPhysicsContact, scene);
}

Level3::~Level3()
{

}

void Level3::Init()
{

}

void Level3::Update()
{
	mFrameCount++;
	if (mFrameCount >= FPS * 62)
	{
		CCLOG("next");
	}

    for (int i = 0; i < mCoreLevelFrame.size(); i++)
    {
        mCoreLevelFrame.at(i)->Update();
		if (mCoreLevelFrame.at(i)->HasFinishedMoving())
		{
			mCoreLevelFrame.at(i)->SetPositionY((i - mCoreLevelFrame.size()) * cocos2d::Director::getInstance()->getVisibleSize().height);
		}
    }

    mCirclePathExtend->Update();
}

bool Level3::OnContactBegin(cocos2d::PhysicsContact &contact)
{
    auto shapeA = contact.getShapeA()->getBody()->getNode();
    auto shapeB = contact.getShapeB()->getBody()->getNode();

	if (shapeA != nullptr && shapeB != nullptr)
	{
		if ((shapeA->getTag() == BALLOON_TAG && shapeB->getTag() == OBSTACLES_TAG) ||
			shapeB->getTag() == BALLOON_TAG && shapeA->getTag() == OBSTACLES_TAG)
		{
			auto balloonExplosion = cocos2d::ParticleSystemQuad::create("sprites/gameplay/balloon/balloon_explosion.plist");
			balloonExplosion->setPosition(cocos2d::Vec2(0, 0));
			if (shapeA->getTag() == BALLOON_TAG)
			{
				shapeA->getPhysicsBody()->setEnabled(false);
				shapeA->setOpacity(0);
				shapeA->addChild(balloonExplosion);
			}
			else if (shapeB->getTag() == BALLOON_TAG)
			{
				shapeB->getPhysicsBody()->setEnabled(false);
				shapeB->setOpacity(0);
				shapeB->addChild(balloonExplosion);
			}
		}
		else if ((shapeA->getTag() == BALLOON_TAG && shapeB->getTag() == COIN_TAG) ||
			(shapeA->getTag() == COIN_TAG && shapeB->getTag() == BALLOON_TAG))
		{
			if (shapeA->getTag() == COIN_TAG)
			{
				shapeA->getPhysicsBody()->setEnabled(false);
				shapeA->removeFromParent();
			}
			else if (shapeB->getTag() == COIN_TAG)
			{
				shapeB->getPhysicsBody()->setEnabled(false);
				shapeB->removeFromParent();
			}

		}
	}

    return true;
}
