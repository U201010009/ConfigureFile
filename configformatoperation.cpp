#include "configformatoperation.h"

#include <iostream>
#include <fstream>

#define		FILE_NOTES		'#'

static std::string removeSpaceFromHeaderAndEnd(std::string);

CConfigFormatOperation::CConfigFormatOperation(const std::string& filename) :
	m_fileName(filename)
{}

CConfigFormatOperation::~CConfigFormatOperation()
{
	if (!m_valueList.empty())
	{
		m_valueList.clear();
	}
}

//public methods : read file messages and put messages into map
CONFIGFORMAT_OPERATION_STATUS CConfigFormatOperation::read()
{
    if (m_fileName.empty())
	{
        return CONFIGFORMAT_OPERATION_FAILED;
	}
	std::ifstream ifs(m_fileName.c_str());
	if (!ifs.is_open())
	{
        return CONFIGFORMAT_OPERATION_FAILED;
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
    return CONFIGFORMAT_OPERATION_SUCCESS;
}

//public methods : get the name's value
CONFIGFORMAT_OPERATION_STATUS CConfigFormatOperation::getValuebyName(const std::string& strName, std::string& outValue, int iIndex)
{
	if (m_valueList.empty())
	{
        return CONFIGFORMAT_OPERATION_FAILED;
	}

    int iCount = 0;
    for (ConfigFormatFileInfos::const_iterator cit = m_valueList.begin(); cit != m_valueList.end(); ++cit)
	{
		if (strName == cit->key_)
		{
            if (iCount == iIndex)
            {
                outValue = cit->value_;
                return CONFIGFORMAT_OPERATION_SUCCESS;
            }
            else
            {
                ++iCount;
                continue;
            }
		}
	}
    return CONFIGFORMAT_OPERATION_FAILED;
}

//public methods : change the name's value
CONFIGFORMAT_OPERATION_STATUS CConfigFormatOperation::setValue(const std::string& strName, const std::string& strValue, int iIndex)
{
	if (m_fileName.empty() || m_valueList.empty())
	{
        return CONFIGFORMAT_OPERATION_FAILED;
	}

    int iCount = 0;
    for (ConfigFormatFileInfos::iterator it = m_valueList.begin(); it != m_valueList.end(); ++it)
	{
		if (strName == it->key_)
		{
            if (iCount == iIndex)
            {
                it->value_ = strValue;
                return CONFIGFORMAT_OPERATION_SUCCESS;
            }
            else
            {
                ++iCount;
                continue;
            }
		}
	}

    return CONFIGFORMAT_OPERATION_FAILED;
}


//write file
CONFIGFORMAT_OPERATION_STATUS CConfigFormatOperation::write()
{
	std::ofstream ofs(m_fileName.c_str(), std::ios::out | std::ios::trunc);
	if (!ofs.is_open())
	{
        return CONFIGFORMAT_OPERATION_FAILED;
	}

    for (ConfigFormatFileInfos::const_iterator cit = m_valueList.begin(); cit != m_valueList.end(); ++cit)
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
    return CONFIGFORMAT_OPERATION_SUCCESS;
}




std::string CConfigFormatOperation::getValue(const std::string& str, char f/* = '='*/)
{
	std::string strValue = "";
	std::string::size_type stPos = str.find(f);
	if (std::string::npos != stPos)
	{
        std::string strPos = str.substr(stPos + 1);
        if (strPos.empty())
            return strValue;

        //
        strValue = removeSpaceFromHeaderAndEnd(strPos);


	}
	return strValue;
}


std::string CConfigFormatOperation::getName(const std::string& str, char f/* = '='*/)
{
	std::string strName = "";
    std::string::size_type stPos = str.find(f);
    if(std::string::npos != stPos)
	{
        std::string strPos = str.substr(0, stPos);
        if (strPos.empty())
            return strName;

        strName = removeSpaceFromHeaderAndEnd(strPos);
	}
	return strName;
}

bool CConfigFormatOperation::isNotes(const std::string& str)
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


std::string removeSpaceFromHeaderAndEnd(std::string strSrc)
{
    if (strSrc.empty())
        return "";

    std::string strDst;
    strDst.reserve(strSrc.size());

    while (!strSrc.empty() && ' ' == strSrc.at(strSrc.size() - 1))
    {
        strSrc.at(strSrc.size() - 1) = '\0';
    }
    if (strSrc.empty())
        return strDst;

    const char* pTmp = strSrc.c_str();
    while (' ' == *pTmp)
    {
        ++pTmp;
    }

    strDst = pTmp;
    return strDst;
}

