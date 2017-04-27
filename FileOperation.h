#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

/************************************************************
  *	
  *		File Name					:		FileOperation.h
  *		Project Information         :       get file config, for example "a = b", get a' value b
  *		Create Time					: 		zyl 2017-04-28
  *
  ***********************************************************/
  


#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>

typedef std::map<std::string, std::string> MyFileValue;

typedef enum 
{
	FX_SUCCESS = 0,
	FX_FAILED
}FILE_OPERATION_STATUS;


class MyFileOperation
{
public:
	MyFileOperation(const std::string& filename);
	~MyFileOperation();

	//get file messages and put messages into map
	bool getfile();
	//get the name's value
	std::string getValuebyName(const std::string& name);
	//change the name's value
	FILE_OPERATION_STATUS setValue(const std::string& name, const std::string& values);
	

private:
	std::string getValue(const std::string& buff, char f = '=');
	std::string getName(const std::string& buff, char f = '=');
	bool isnotes(const std::string& buff);
	bool isname(const std::string& name, const std::string& dest_name);
	std::string changeValue(const std::string& buff, const std::string& values, char f = '=');

private:
	MyFileValue m_valueMap;
	std::string m_filename;
};


#endif //FILE_OPERATION_H