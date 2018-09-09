#include <iostream>

#include "configformatoperation.h"

int main(int , char **)
{
    std::string strFile = "test.cfg";
    CConfigFormatOperation tmpConfig(strFile);
    if (CONFIGFORMAT_OPERATION_SUCCESS != tmpConfig.read())
    {
        std::cout << "read " << strFile << " failed!" << std::endl;
        return -1;
    }
    std::cout << "read " << strFile << " success." << std::endl;

    std::string strValue;
    std::string strName = "name";
    for (int i = 0; i < 7; ++i)
    {
        if (CONFIGFORMAT_OPERATION_SUCCESS != tmpConfig.getValuebyName(strName, strValue, i))
        {
            std::cout << "get " << strName << "'value failed! index = " << i << std::endl;
        }
        else
        {
            std::cout << strName << " = " << strValue << ", index = " << i << std::endl;
        }
    }

    int iIndex = 3;
    strValue = "333333333";
    if (CONFIGFORMAT_OPERATION_SUCCESS != tmpConfig.setValue(strName, strValue, iIndex))
    {
        std::cout << "set " << strName << " = " << strValue << " failed! index = " << iIndex << std::endl;
    }
    else
    {
        std::cout << "set " << strName << " = " << strValue << " success, index = " << iIndex << std::endl;
    }

    //tmpConfig.write();

    return 0;
}
