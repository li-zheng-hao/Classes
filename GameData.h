#ifndef GameData_H
#define GameData_H
#include "cocos2d.h"
USING_NS_CC;
class GameData
{
public:
	static GameData* getIntance();
	CC_SYNTHESIZE(int, _gold, Gold);
	CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
	CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
	void init();

	/*
	 * 2017/09/12
	 * @brief �����ݴ洢
	 */
	void flush();

	/*
	 * 2017/09/12
	 * @brief �ı���
	 */
	void alterGold(int delta);

	/*
	 * 2017/09/12
	 * @brief ��������
	 */
	void reset();
	/*
	 * 2017/09/12
	 * @brief ����ʵ������
	 */
	void purge();
protected:
	static GameData* _sharedGameData;
private:
	GameData();
	~GameData();
};

#endif
