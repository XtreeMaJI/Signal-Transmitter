#include "cstringhelper.h"

std::vector<double> CStringHelper::parseQStringToDoubleVec(QString str, QChar separatorChar)
{
    std::vector<double> values;

    if(str.length() == 0)
        return values;

    QString valueStr = "";
    auto ch = str.begin();
    while(ch != str.end())
    {
        if(*ch != separatorChar && ch != str.end())
        {
            valueStr.append(*ch);
        }
        else
        {
            values.push_back(valueStr.toDouble());
            valueStr = "";
        }

        ch++;

        if(ch == str.end() && !valueStr.isEmpty())
            values.push_back(valueStr.toDouble());
    }

    return values;
}
