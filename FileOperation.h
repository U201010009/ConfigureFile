#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

/************************************************************
  *	
  *		File Name					:		FileOperation.h
  *		Project Information         :       get file config, for example "a = b", get a' value b
  *		Create Time					: 		zyl 2017-04-28
  *		Modified Time				:		2018-06-04
  *
  ***********************************************************/
  


#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

typedef enum 
{
	FILE_OPERATION_SUCCESS = 0,
	FILE_OPERATION_FAILED
}FILE_OPERATION_STATUS;


class MyFileOperation
{
	typedef struct
	{
		std::string key_;
		std::string value_;
	}ConfigInfo;

	typedef std::list<ConfigInfo> MyFileInfos;
public:
	MyFileOperation(const std::string& filename);
	~MyFileOperation();

	//read file messages and put messages into map
	FILE_OPERATION_STATUS read();
	//get the name's value
	std::string getValuebyName(const std::string& name);
	//change the name's value
	FILE_OPERATION_STATUS setValue(const std::string& name, const std::string& values);
	//write file
	FILE_OPERATION_STATUS write();
	

private:
	std::string getValue(const std::string& buff, char f = '=');
	std::string getName(const std::string& buff, char f = '=');
	bool isNotes(const std::string& buff);

private:
	MyFileInfos m_valueList;
	std::string m_filename;
};


#endif //FILE_OPERATION_H