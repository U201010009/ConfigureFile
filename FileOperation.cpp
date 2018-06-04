#include "FileOperation.h"

#include <iostream>
#include <fstream>

#define		FILE_NOTES		'#'

MyFileOperation::MyFileOperation(const std::string& filename) :
	m_fileName(filename)
{}

MyFileOperation::~MyFileOperation()
{
	if (!m_valueList.empty())
	{
		m_valueList.clear();
	}
}

//public methods : read file messages and put messages into map
FILE_OPERATION_STATUS MyFileOperation::read()
{
	if ("" == m_fileName)
	{
		return FILE_OPERATION_FAILED;
	}
	std::ifstream ifs(m_fileName.c_str());
	if (!ifs.is_open())
	{
		return FILE_OPERATION_FAILED;
	}
	std::string strBuff;
	while(getline(ifs, strBuff))
	{
		if ("" == strBuff || isNotes(strBuff))
		{
			ConfigInfo tmpInfo = { strBuff, "" };
			m_valueList.push_back(tmpInfo);
		}
		else
		{
			ConfigInfo tmpInfo;
			tmpInfo.key_ = getName(strBuff);
			tmpInfo.value_ = getValue(strBuff);
			m_valueList.push_back(tmpInfo);
		}
	}
	ifs.close();
	return FILE_OPERATION_SUCCESS;
}

//public methods : get the name's value
std::string MyFileOperation::getValuebyName(const std::string& strName)
{
	if (m_valueList.empty())
	{
		return "";
	}
	for (MyFileInfos::const_iterator cit = m_valueList.begin(); cit != m_valueList.end(); ++cit)
	{
		if (strName == cit->key_)
		{
			return cit->value_;
		}
	}
	return "";
}

//public methods : change the name's value
FILE_OPERATION_STATUS MyFileOperation::setValue(const std::string& strName, const std::string& strValue)
{
	if (m_fileName.empty() || m_valueList.empty())
	{
		return FILE_OPERATION_FAILED;
	}

	for (MyFileInfos::iterator it = m_valueList.begin(); it != m_valueList.end(); ++it)
	{
		if (strName == it->key_)
		{
			it->value_ = strValue;
			return FILE_OPERATION_SUCCESS;
		}
	}

	return FILE_OPERATION_FAILED;
}


//write file
FILE_OPERATION_STATUS MyFileOperation::write()
{
	std::ofstream ofs(m_fileName.c_str(), std::ios::out | std::ios::trunc);
	if (!ofs.is_open())
	{
		return FILE_OPERATION_FAILED;
	}

	for (MyFileInfos::const_iterator cit = m_valueList.begin(); cit != m_valueList.end(); ++cit)
	{
		if (cit->key_.empty() || FILE_NOTES == cit->key_.at(0))
		{
			ofs << cit->key_ << std::endl;
		}
		else
		{
			std::string strLine = cit->key_;
			strLine += "=";
			strLine += cit->value_;
			ofs << strLine << std::endl;
		}
	}
	ofs.close();
	return FILE_OPERATION_SUCCESS;
}




std::string MyFileOperation::getValue(const std::string& str, char f/* = '='*/)
{
	std::string strValue = "";
	std::string::size_type stPos = str.find(f);
	if (std::string::npos != stPos)
	{
		std::string strPos = str.substr(stPos);
		const char* pos = strPos.c_str();
		while (*pos == ' ' || *pos == f)
		{
			if (*pos == '\0')
			{
				return "";
			}
			++pos;
		}
		while(*pos != ' ' && *pos != f && *pos != '\0')
		{
			strValue += *pos;
			++pos;
		}
	}
	return strValue;
}


std::string MyFileOperation::getName(const std::string& str, char f/* = '='*/)
{
	std::string strName = "";
	const char* pos = str.c_str();
	if(std::string::npos != str.find(f))
	{
		while (*pos == ' ')
		{
			if (*pos == '\0')
			{
				return "";
			}
			++pos;
		}
		while (*pos != ' ' && *pos != f && *pos != '\0')
		{
			strName += *pos;
			++pos;
		}
	}
	return strName;
}

bool MyFileOperation::isNotes(const std::string& str)
{
	if (!str.empty())
	{
		if (FILE_NOTES == str.at(0))
		{
			return true;
		}
	}
	return false;
}

