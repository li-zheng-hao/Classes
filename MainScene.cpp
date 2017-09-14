#include "MainScene.h"
enum
{
	k_MainScene_TouchLayer,
	k_MainScene_CannonLayer,
	k_MainScene_FishLayer,
	k_MainScene_UILayer,
	k_MainScene_BackgroundLayer,
	k_MainScene_LayerCount
};
bool MainScene::init()
{
	if (Scene::init())
	{
		/*
		 * 2017/08/17
		 * @brief ��Ϸ���ݳ�ʼ��
		 */
		//preloadSources();
		

		/*
		 * 2017/08/17
		 * @brief ���в�ļ���
		 */
		_touchLayer = TouchLayer::create();
		this->addChild(_touchLayer, 5,k_MainScene_TouchLayer);

		_cannonLayer = CannonLayer::create();
		this->addChild(_cannonLayer,4,k_MainScene_CannonLayer);

		_fishLayer = FishLayer::create();
		this->addChild(_fishLayer, 2,k_MainScene_FishLayer);
		
		_uiLayer = UILayer::create();
		this->addChild(_uiLayer,3,k_MainScene_UILayer);

		_backGroundLayer = BackGroundLayer::create();
		this->addChild(_backGroundLayer, 1,k_MainScene_BackgroundLayer);


		this->schedule(schedule_selector(MainScene::checkAreaBetweenFishAndFishNet));
		return true;
	}
	return false;
	
}


void MainScene::cannonAimAt(const Vec2 & pos)
{
	_cannonLayer->cannonAimAt(pos);
}

void MainScene::cannonShootTo(const Vec2 & pos)
{
	_cannonLayer->cannonShootTo(pos);
}

void MainScene::checkAreaBetweenFishAndFishNet(float dt)
{
	if (_cannonLayer->isShoot())
	{
		Vector<Fishes*> vec = _fishLayer->_fishes;
		Rect fishNetArea = _cannonLayer->getFishNetCollisionArea();
		for(auto iter:vec)
		{
			Fishes* fish=(Fishes*)iter;
			if (fish->isRunning())
			{
				
				auto size = fish->getFishRect();
				/*
				 * 2017/09/14
				 * @brief ���������״̬�Ƿ񱻲�׽������beCaught�����ᱻ���úܶ�Σ���Ϊ����һ����ʱ�����ڲ��ϵĲ�ѯ
				 */
				if (size.intersectsRect(fishNetArea)&&!fish->CheckStatusIsCaughting())
				{
					fish->beCaught();
					continue;
				}
			}
			
		}
	}

}

