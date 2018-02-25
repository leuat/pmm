#ifndef DATA_H
#define DATA_H

#include <QString>

class Data
{
public:
    Data();
    static Data d;
    int lineNumber = 0;
    QString currentLineText;

};

#endif // DATA_H
