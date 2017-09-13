#include "StaticData.h"
#define DATA_PATH "file.plist"
StaticData* StaticData::_sharedStaticData = nullptr;

StaticData::StaticData()
{

}

StaticData * StaticData::getInstance()
{
	if (!_sharedStaticData)
	{
		_sharedStaticData = new StaticData();
		_sharedStaticData->init();
	}
	return _sharedStaticData;
}

void StaticData::init()
{
	_data = Dictionary::createWithContentsOfFile(DATA_PATH);
	/*
	 * 2017/08/17
	 * @brief retain֮��ǵ�release
	 */
	CC_SAFE_RETAIN(_data);
}

StaticData::~StaticData()
{
	/*
	 * 2017/08/17
	 * @brief ��ֹ�ڴ�й©
	 */
	CC_SAFE_RELEASE(_data);
	CC_SAFE_DELETE(_sharedStaticData);
}

//-----------------�����ǽ��ֵ��һЩ�ӿڽ�һ����װbegin---------------------
const char* StaticData::getStringFromKey(const std::string& key) const
{
	return _data->valueForKey(key)->getCString();
}

int StaticData::getIntFromKey(const std::string &key) const
{
	return _data->valueForKey(key)->intValue();
}

float StaticData::getFloatFromKey(const std::string &key) const
{
	return _data->valueForKey(key)->floatValue();
}

bool StaticData::getBoolFromKey(const std::string & key) const
{
	return _data->valueForKey(key)->boolValue();
}


//-----------------�����ǽ��ֵ��һЩ�ӿڽ�һ����װ end-----------------------