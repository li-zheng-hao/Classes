#ifndef MainScene_H
#define MainScene_H
#include "cocos2d.h"
#include "StaticData.h"
#include "TouchLayer.h"
#include "FishLayer.h"
#include "CannonLayer.h"
#include "UILayer.h"
#include "BackGroundLayer.h"
#include "Fishes.h"
#include "Cannon.h"
#include "GameData.h"
USING_NS_CC;
class MainScene:public Scene
{
public:
	CREATE_FUNC(MainScene);
	bool init();
	void preloadSources();
	/*
	 * 2017/08/19
	 * @brief ����̨����һЩ����
	 */
	void cannonAimAt(const Vec2 &pos);
	void cannonShootTo(const Vec2& pos);

	/*
	 * 2017/08/23
	 * @brief �ж���������֮���Ƿ񽻲�
	 */

	void checkAreaBetweenFishAndFishNet(float dt);
protected:
	UILayer* _uiLayer;
	TouchLayer* _touchLayer;
	FishLayer* _fishLayer;
	CannonLayer* _cannonLayer;
	BackGroundLayer* _backGroundLayer;
};
#endif

