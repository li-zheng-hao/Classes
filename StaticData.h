#ifndef StaticData_H
#define StaticData_H
#include "cocos2d.h"
USING_NS_CC;
//-----------------����һЩ�궨��	begin---------------------
#define STATIC_DATA_STRING(key) StaticData::getInstance()->getStringFromKey(key)
#define STATIC_DATA_INT(key) StaticData::getInstance()->getIntFromKey(key)
#define STATIC_DATA_FLOAT(key) StaticData::getInstance()->getFloatFromKey(key)
#define STATIC_DATA_BOOL(key) StaticData::getInstance()->getBoolFromKey(key)
#define winSize Director::getInstance()->getWinSize()
//-----------------����һЩ�궨��	end-----------------------

class StaticData
{
public:
	/*
	 * 2017/08/17
	 * @brief �����ǵ���ģʽ
	 */
	static StaticData* getInstance();
	void init();
	~StaticData();
	
	/*
	 * 2017/08/17
	 * @brief ��Dictionary��һЩ�ӿڽ��н�һ���ķ�װ
	 */
	const char* getStringFromKey(const std::string &key)const ;
	int getIntFromKey(const std::string &key)const;
	float getFloatFromKey(const std::string &key)const;
	bool getBoolFromKey(const std::string &key)const;
protected:
	static StaticData* _sharedStaticData;
	Dictionary* _data;
private:
		//��ֹͨ�����ַ�ʽ���д���
	StaticData();

};
#endif

