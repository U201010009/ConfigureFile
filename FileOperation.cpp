
#include "FileOperation.h"

using namespace std;

MyFileOperation::MyFileOperation(const string& filename) :
	m_filename(filename)
		, m_valueMap()
{

}

MyFileOperation::~MyFileOperation()
{
	if (!m_valueMap.empty())
	{
		m_valueMap.clear();
	}
}

//public methods : get file messages and put messages into map
bool MyFileOperation::getfile()
{
	if ("" == m_filename)
	{
		return false;
	}
	ifstream ifs(m_filename.c_str());
	string buff;
	while(getline(ifs, buff))
	{
		if ("" == buff || isnotes(buff))
		{
			continue;
		}
		string strname = getName(buff);
		string strvalue = getValue(buff);
		m_valueMap.insert(MyFileValue::value_type(strname, strvalue));
	}
	return true;
}

//public methods : get the name's value
string MyFileOperation::getValuebyName(const string& name)
{
	string ret = "";
	if (m_valueMap.empty())
	{
		return ret;
	}
	MyFileValue::iterator it = m_valueMap.find(name.c_str());
	if (it != m_valueMap.end())
	{
		ret = it->second;
	}
	return ret;
}

//public methods : change the name's value
FILE_OPERATION_STATUS MyFileOperation::setValue(const string& name, const string& values)
{
	if (m_filename.empty() || m_valueMap.empty())
	{
		return FX_FAILED;
	}
	string buff;
	list<string>strbuff;
	bool bname = false;

	ifstream ifs(m_filename, ios::in | ios::ate);
	if (!ifs.is_open())
	{
		return FX_FAILED;
	}
	ifs.seekg(0, ios_base::beg);
	while (getline(ifs, buff))
	{
		buff += '\n';
		strbuff.push_back(buff);
		if (buff.empty() || isnotes(buff))
		{
			continue;
		}

		if (isname(buff, name))
		{
			strbuff.pop_back();
			strbuff.push_back(changeValue(buff, values));
			bname = true;
		}
	}
	ifs.close();

	ofstream ofs(m_filename, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		strbuff.clear();
		return FX_FAILED;
	}

	while (!strbuff.empty())
	{
		ofs<<(strbuff.front().c_str());
		strbuff.pop_front();
	}
	strbuff.clear();
	ofs.close();

	MyFileValue:: iterator it = m_valueMap.find(name.c_str());
	if (m_valueMap.end() != it)
	{
		//m_valueMap.insert(MyFileValue::value_type(name, values)); //won't cover the value
		m_valueMap[name] = values;
	}

	return bname ? FX_SUCCESS : FX_FAILED;
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

bool MyFileOperation::isnotes(const string& buff)
{
	if('#' == *(buff.c_str()))
	{
		return true;
	}
	return false;
}

bool MyFileOperation::isname(const string& name, const string& dest_name)
{
	const char* pname = name.c_str();
	const char* pdest_name = dest_name.c_str();
	return NULL != strstr(pname, pdest_name) ? true : false;
}

string MyFileOperation::changeValue(const string& buff, const string& values, char f/* = '='*/)
{
	const char* pvalues = values.c_str();
	const char* pbuff = buff.c_str();
	string ret = "";
	const char* pos = NULL;
	if(pos = strstr(pbuff, &f))
	{
		while(*pbuff != f && *pbuff != '\0')
		{
			ret += *pbuff;
			++pbuff;
		}
		while (*pos == f || *pos == ' ' && *pos != '\0')
		{
			ret += *pos;
			++pos;
		}
		ret += pvalues;
		ret += '\n';
	}
	return ret;
}
