#include "CoinModel.h"
#include "utils/levels/level3/animation/GetAnimation.h"
#include "utils/physics/CustomPhysicsBody.h"
#include "common/definitionlevels/DefinitionLevel3.h"
#include "common/Definition.h"

CoinModel::CoinModel(cocos2d::Scene* scene) : CoreModel("")
{
    Init();
    scene->addChild(mCoreSprite);
}

CoinModel::CoinModel(cocos2d::Node* node) : CoreModel("")
{
    Init();
    node->addChild(mCoreSprite);
}

CoinModel::~CoinModel()
{
    // Destrucltor
}

void CoinModel::Init()
{
    auto getAnimation = GetAnimation::GetInstance();
    mSpriteFrames = getAnimation->GetSpriteFramesWidthPlistFile(COIN_PLIST_NAME_PATH, COIN_NAME_FRAME_FORMAT, 10);
    
    mCoreSprite = cocos2d::Sprite::createWithSpriteFrame(mSpriteFrames.front());
    mCoreSprite->setTag(COIN_TAG);
    mCoreSprite->runAction(GetAnimation::GetInstance()->GetAnimationRepeatForever(mSpriteFrames));

    CustomPhysicsBody::getInstance()->parseJsonFile(COIN_PHYSICS_JSON);
    auto coinPhysicsBody = CustomPhysicsBody::getInstance()->bodyFormJson(mCoreSprite, COIN_PHYSICS_NAME, cocos2d::PhysicsMaterial( 1, 1, 0 ));

    if (coinPhysicsBody != nullptr)
    {
        coinPhysicsBody->setDynamic(false);
        coinPhysicsBody->setCategoryBitmask(COIN_COLLISION_BITMASK);
        coinPhysicsBody->setContactTestBitmask(true);

        mCoreSprite->setPhysicsBody(coinPhysicsBody);
    }
}

void CoinModel::Update()
{

}
