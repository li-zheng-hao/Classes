#include "Fishes.h"
#include "StaticData.h"
typedef enum ActionType
{
	k_Fish_Animate,
	k_Fish_Action,
	k_Fish_beCaught
};
Fishes * Fishes::create(FishType type)
{
	auto fish = new Fishes();
	if (fish&&fish->init(type))
	{
		fish->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(fish);
	}
	return fish;
}

bool Fishes::init(FishType type)
{
	_type = type;
	_status = k_Fish_Moving;
	auto fishname = String::createWithFormat(STATIC_DATA_STRING("fishanimationformat"), type);
	auto animation = AnimationCache::getInstance()->getAnimation(fishname->getCString());
	auto animate = Animate::create(animation);
	animate->setTag(k_Fish_Animate);
	String* spriteName = String::createWithFormat(STATIC_DATA_STRING("fishtypeformat"), type + 1);
	_sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(spriteName->getCString())));
	//String realname = STATIC_DATA_STRING(spriteName->getCString());
	//_sprite = Sprite::create(realname.getCString());
	this->addChild(_sprite);
	_sprite->runAction(RepeatForever::create(animate));
	return true;
}

void Fishes::moveToAction(Vec2 destination)
{
	auto startPoint = this->getPosition();
	float speed = ccpDistance(destination,startPoint) / 200;
	auto movetoAction = MoveTo::create(speed, destination);
	auto moveendAction = CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(Fishes::moveActionEnd));
	auto sequence = Sequence::create(movetoAction, moveendAction, NULL);
	sequence->setTag(k_Fish_Action);
	this->runAction(sequence);
}

void Fishes::moveActionEnd()
{
	this->removeFromParentAndCleanup(false);
}

void Fishes::reset()
{
	this->_status = k_Fish_Moving;
	this->setRotation(0);
	this->setVisible(true);
}

bool Fishes::CheckStatusIsCaughting()
{
	return _status == k_Fish_beCaughting ? true : false;
}

void Fishes::beCaught()
{
	this->_status = k_Fish_beCaughting;
	this->stopActionByTag(k_Fish_Action);
	/*
	之前的代码，先保存
	CCDelayTime* delayTime = CCDelayTime::create(1.0);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fishes::callfunc));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, callFunc, NULL);
	CCBlink* blink = CCBlink::create(1.0, 8);
	CCFiniteTimeAction *spawn = CCSpawn::create(seq, blink, NULL);
	this->runAction(spawn);
	*/
	auto animationName = String::createWithFormat("fishcaught%d", _type+1);
	auto animation = AnimationCache::getInstance()->getAnimation(animationName->getCString());
	animation->setLoops(1);
	auto animate=Animate::create(animation);
	auto callfunc = CallFunc::create(this, callfunc_selector(Fishes::callfunc));
	auto seq = Sequence::create(animate, callfunc,NULL);
	this->_sprite->runAction(seq);
	
}

void Fishes::callfunc()
{
	//this->stopAllActions();//这里有bug，如果不暂停所有动作，那么每次添加新的鱼时，都会调用这个函数，最后界面上一条鱼都不会显示.
	CCLOG("be call be call-----------------");
	this->removeFromParentAndCleanup(false);
}

cocos2d::Rect Fishes::getFishRect()
{
	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize size = _sprite->getContentSize();
	return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);
	
}
