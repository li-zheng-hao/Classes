#include "GameData.h"
GameData* GameData::_sharedGameData = nullptr;

GameData * GameData::getInstance()
{
	if (!_sharedGameData)
	{
		_sharedGameData = new GameData();
		_sharedGameData->init();
	}
	return _sharedGameData;
}

void GameData::init()
{
	_data = Dictionary::createWithContentsOfFile("file.plist");
	/*
	 * 2017/08/17
	 * @brief retain֮��ǵ�release
	 */
	CC_SAFE_RETAIN(_data);
}

GameData::~GameData()
{
	/*
	 * 2017/08/17
	 * @brief ��ֹ�ڴ�й©
	 */
	CC_SAFE_RELEASE(_data);
	CC_SAFE_DELETE(_sharedGameData);
}

const char* GameData::getStringFromKey(const std::string& key) const
{
	return _data->valueForKey(key)->getCString();
}

int GameData::getIntFromKey(const std::string &key) const
{
	return _data->valueForKey(key)->intValue();
}

float GameData::getFloatFromKey(const std::string &key) const
{
	return _data->valueForKey(key)->floatValue();
}

bool GameData::getBoolFromKey(const std::string & key) const
{
	return _data->valueForKey(key)->boolValue();
}

