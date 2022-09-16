#ifndef CSTRINGHELPER_H
#define CSTRINGHELPER_H

#include <QString>

class CStringHelper
{
public:
    CStringHelper() = delete;
    static std::vector<double> parseQStringToDoubleVec(QString str, QChar separatorChar);
};

#endif // CSTRINGHELPER_H
