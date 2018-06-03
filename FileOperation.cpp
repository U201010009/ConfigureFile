
#include "FileOperation.h"

#define		FILE_NOTES		'#'

using namespace std;

MyFileOperation::MyFileOperation(const string& filename) :
	m_filename(filename)
	, m_valueList()
{

}

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
	if ("" == m_filename)
	{
		return FILE_OPERATION_FAILED;
	}
	ifstream ifs(m_filename.c_str());
	string buff;
	while(getline(ifs, buff))
	{
		if ("" == buff || isNotes(buff))
		{
			ConfigInfo tmpInfo = { buff, "" };
			m_valueList.push_back(tmpInfo);
		}
		else
		{
			ConfigInfo tmpInfo;
			tmpInfo.key_ = getName(buff);
			tmpInfo.value_ = getValue(buff);
			m_valueList.push_back(tmpInfo);
		}
	}
	return FILE_OPERATION_SUCCESS;
}

//public methods : get the name's value
string MyFileOperation::getValuebyName(const string& name)
{
	string ret = "";
	if (m_valueList.empty())
	{
		return ret;
	}
	for (MyFileInfos::const_iterator cit = m_valueList.begin(); cit != m_valueList.end(); ++cit)
	{
		if (name == cit->key_)
		{
			ret = cit->value_;
			break;
		}
	}
	return ret;
}

//public methods : change the name's value
FILE_OPERATION_STATUS MyFileOperation::setValue(const string& name, const string& values)
{
	if (m_filename.empty() || m_valueList.empty())
	{
		return FILE_OPERATION_FAILED;
	}

	for (MyFileInfos::iterator it = m_valueList.begin(); it != m_valueList.end(); ++it)
	{
		if (name == it->key_)
		{
			it->value_ = values;
			return FILE_OPERATION_SUCCESS;
		}
	}

	return FILE_OPERATION_FAILED;
}


//write file
FILE_OPERATION_STATUS MyFileOperation::write()
{
	ofstream ofs(m_filename, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		return FILE_OPERATION_FAILED;
	}

	for (MyFileInfos::const_iterator cit = m_valueList.begin(); cit != m_valueList.end(); ++cit)
	{
		if (cit->key_.empty() || FILE_NOTES == cit->key_.at(0))
		{
			ofs << cit->key_ << endl;
		}
		else
		{
			string strLine = cit->key_;
			strLine += "=";
			strLine += cit->value_;
			ofs << strLine << endl;
		}
	}

	ofs.close();

	return FILE_OPERATION_SUCCESS;
}




string MyFileOperation::getValue(const string& buff, char f/* = '='*/)
{
	string Value = "";
	const char* pos = buff.c_str();
	if (pos = strstr(pos, &f))
	{
		while (*pos == ' ' || *pos == f)
		{
			++pos;
		}
		while(*pos != ' ' && *pos != f && *pos != '\0')
		{
			Value += *pos;
			++pos;
		}
	}
	return Value;
}


string MyFileOperation::getName(const string& buff, char f/* = '='*/)
{
	string Name = "";
	const char* pos = buff.c_str();
	if(strstr(pos, &f))
	{
		while (*pos == ' ')
		{
			++pos;
		}
		while (*pos != ' ' && *pos != f)
		{
			Name += *pos;
			++pos;
		}
	}
	return Name;
}

bool MyFileOperation::isNotes(const string& buff)
{
	if(FILE_NOTES == *(buff.c_str()))
	{
		return true;
	}
	return false;
}

