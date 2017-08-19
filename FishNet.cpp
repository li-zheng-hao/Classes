#include "FishNet.h"
#include "GameData.h"
bool FishNet::init()
{
	auto animation = AnimationCache::getInstance()->getAnimation("net");
	auto aniamte = Animate::create(animation);
	this->runAction(aniamte);
	auto sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("net11")));
	this->setContentSize(sprite->getContentSize());//�������Ĵ�С����Ϊ���һ��ͼƬ�Ĵ�С��Ҳ������������ͼ
	return true;
}
