#include "StartScene.h"
#include "GameData.h"
#include "StaticData.h"
#include "TouchLayer.h"
#include "FishLayer.h"
#include "CannonLayer.h"
#include "UILayer.h"
#include "BackGroundLayer.h"
#include "Fishes.h"
#include "Cannon.h"
#include "GameData.h"
#include "MainScene.h"
enum 
{
	k_Sprite_Type_Progress=0
};
bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/*
	 * 2017/09/12
	 * @brief 有些资源是后面加进来的，所以代码写的和半个月前写的代码不一致
	 */


	//背景层的添加（新增加的界面，资源采用异步加载，所以暂时先就这样直接硬加载背景）
	auto bg = Sprite::create("UI/background.jpg");
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(bg);

	//游戏标题
	auto title = Sprite::create(STATIC_DATA_STRING("title"));
	title->setPosition(Vec2(winSize.width/2,winSize.height/2+200));
	title->setScale(1.5);
	this->addChild(title);

	//加载进度条背景
	auto progress_bg = Sprite::create(STATIC_DATA_STRING("progress_bg"));
	progress_bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(progress_bg);
	//加载进度条
	auto process_sprite = Sprite::create(STATIC_DATA_STRING("progress_bar"));
	auto progress = ProgressTimer::create(process_sprite);
	progress->setType(ProgressTimer::Type::BAR);
	progress->setBarChangeRate(Vec2(1,0));
	progress->setMidpoint(Vec2(0,1));
	progress->setPosition(winSize.width / 2, winSize.height / 2);
	progress->setPercentage(0);
	progress->setTag(k_Sprite_Type_Progress);
	this->addChild(progress);
	
	//异步加载资源
	/*

	下面使用的call_back_1也就是这样
	std::function<void(Texture2D*)> f = std::bind(&StartScene::sourcesCallBack, this, std::placeholders::_1);
	从此可见一斑：callfunc之类的调用方式如下：
	void CallFuncN::execute()
	{
		if (_callFuncN)
		{
			(_selectorTarget->*_callFuncN)(_target);
		}
		else if (_functionN)
		{
			_functionN(_target);
		}
	}
	*/
	Director::getInstance()->getTextureCache()->addImageAsync("data.png", CC_CALLBACK_1(StartScene::sourcesCallBack, this));
	


	StartScene* start;
	return true;
}

void StartScene::preloadSources()
{
	StaticData::getInstance();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("data.plist");

	/*
	* 2017/08/17
	* @brief 加载鱼类的动画
	*/
	auto animationcache = AnimationCache::getInstance();
	int framecount = STATIC_DATA_INT("fishframecount");
	for (int type = k_Fish_One; type<k_Fish_Count; type++)
	{
		Vector<SpriteFrame*> frames(framecount);
		for (int i = 1; i <= framecount; i++)
		{
			String key = STATIC_DATA_STRING("fish_frame_name_count");
			String* filename = String::createWithFormat(STATIC_DATA_STRING("fish_frame_name_count"), type + 1, i);
			String realfilename = STATIC_DATA_STRING(filename->getCString());
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(filename->getCString()));
			frames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(frames);
		animation->setDelayPerUnit(0.1f);
		String* animationName = String::createWithFormat(STATIC_DATA_STRING("fishanimationformat"), type);

		animationcache->addAnimation(animation, animationName->getCString());
	}

	/*
	* 2017/08/19
	* @brief 加载炮台发射炮弹时放大动画
	*/

	for (int fishtype = k_Cannon_Type_1; fishtype<k_Cannon_Type_Count; fishtype++)
	{
		Vector<SpriteFrame*> newframes(2);
		for (int j = 1; j <= 2; j++)
		{
			String* frameName = String::createWithFormat("Cannon%d_%d", fishtype + 1, j);
			SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(frameName->getCString()));
			newframes.pushBack(sprite);
		}
		auto animation = Animation::createWithSpriteFrames(newframes);
		animation->setDelayPerUnit(0.2f);
		String* animationName = String::createWithFormat("cannonanimation%d", fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}

	/*
	* 2017/08/19
	* @brief 加载渔网的动画
	*/
	Vector<SpriteFrame*> frames(11);
	for (int j = 1; j <= 11; j++)
	{
		String* frameName = String::createWithFormat("net%d", j);
		SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(frameName->getCString()));
		frames.pushBack(sprite);
	}
	auto animation = Animation::createWithSpriteFrames(frames);
	animation->setDelayPerUnit(0.04f);
	AnimationCache::getInstance()->addAnimation(animation, "net");


	/*
	* 2017/08/22
	* @brief 鱼被捕捉成功的动画,一共两种，第一种有2帧，第二种有4帧
	*/

	int fishcaughttype = STATIC_DATA_INT("fishcaughtcountone");
	framecount = STATIC_DATA_INT("fishcaughtcountoneframes");
	int fishtype = 1;
	for (; fishtype <= fishcaughttype; fishtype++)
	{
		Vector<SpriteFrame*> vec(framecount);
		for (int j = 1; j <= framecount; j++)
		{

			String* framename = String::createWithFormat("fish%d_catch_%d", fishtype, j);
			SpriteFrame* spr = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(framename->getCString()));
			vec.pushBack(spr);
		}
		auto animation = Animation::createWithSpriteFrames(vec);
		animation->setDelayPerUnit(0.2f);
		auto animationName = String::createWithFormat("fishcaught%d", fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}
	fishcaughttype = STATIC_DATA_INT("fishcaughtcounttwo");

	framecount = STATIC_DATA_INT("fishcaughtcounttwoframes");
	for (; fishtype <= fishcaughttype; fishtype++)
	{
		Vector<SpriteFrame*> vec(framecount);
		for (int j = 1; j <= framecount; j++)
		{
			String* framename = String::createWithFormat("fish%d_catch_%d", fishtype, j);
			SpriteFrame* spr = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(framename->getCString()));
			vec.pushBack(spr);
		}
		auto animation = Animation::createWithSpriteFrames(vec);
		animation->setDelayPerUnit(0.2f);
		auto animationName = String::createWithFormat("fishcaught%d", fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}

}

void StartScene::sourcesCallBack(Texture2D* sender)
{

	auto progress=(ProgressTimer*)this->getChildByTag(k_Sprite_Type_Progress);
	auto prepare=ProgressTo::create(1.0f, 50);
	progress->runAction(prepare);
	this->preloadSources();

	auto ac=ProgressTo::create(1.0f, 100);
	auto callfunc = CallFunc::create(this, callfunc_selector(StartScene::progressMaxCallBack));
	auto seq = Sequence::create(ac, callfunc,NULL);
	progress->runAction(seq);
}

void StartScene::progressMaxCallBack()
{
	//todo 添加开始的菜单按钮
	auto mainscene = MainScene::create();
	auto transition = TransitionCrossFade::create(2.0f, mainscene);
	Director::getInstance()->pushScene(transition);
}

