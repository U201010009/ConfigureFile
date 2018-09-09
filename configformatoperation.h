#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

/************************************************************
  *	
  *		File Name					:		FileOperation.h
  *		Project Information         :       get file config, for example "a = b", get a' value b
  *		Create Time	                :       zyl 2017-04-28
  *		Modified Time               :       2018-09-08
  *
  ***********************************************************/
  


#include <string>
#include <list>

typedef enum 
{
    CONFIGFORMAT_OPERATION_SUCCESS = 0,
    CONFIGFORMAT_OPERATION_FAILED
}CONFIGFORMAT_OPERATION_STATUS;


class CConfigFormatOperation
{
	typedef struct
	{
		std::string key_;
		std::string value_;
	}ConfigInfo;

    typedef std::list<ConfigInfo> ConfigFormatFileInfos;
public:
    CConfigFormatOperation(const std::string& filename);
    ~CConfigFormatOperation();

	//read file messages and put messages into map
    CONFIGFORMAT_OPERATION_STATUS read();

    //get the name's value, iIndex(repeat strName count)
    CONFIGFORMAT_OPERATION_STATUS getValuebyName(const std::string& strName, std::string& outValue, int iIndex = 0);

    //change the name's value, iIndex(repeat strName count)
    CONFIGFORMAT_OPERATION_STATUS setValue(const std::string& strName, const std::string& strValue, int iIndex = 0);

	//write file
    CONFIGFORMAT_OPERATION_STATUS write();
	

private:
	std::string getValue(const std::string& str, char f = '=');
	std::string getName(const std::string& str, char f = '=');
	bool isNotes(const std::string& str);

private:
    ConfigFormatFileInfos m_valueList;
	std::string m_fileName;
};


#endif //FILE_OPERATION_H
