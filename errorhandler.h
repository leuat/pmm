#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#include <QString>
#include <QDebug>

class ErrorHandler
{
public:
    ErrorHandler();
    static ErrorHandler e;
    int m_level = 0;

    int ERROR_ONLY = 2;
    int DEBUG_HIGH = 1;
    int DEBUG_LOW = 0;


    void Message(QString str, int lvl=0) {
        QString s ="";
        for (int i=0;i<lvl;i++)
            s+=" ";

        qDebug() << s << str;

    }

    void DebugHigh(QString str, int lvl=0) {
        if (m_level<=DEBUG_HIGH)
            Message(str, lvl);
    }

    void DebugLow(QString str, int lvl=0) {
        if (m_level<=DEBUG_LOW)
            Message(str, lvl);
    }

    void Error(QString str) {

        Message("*** FATAL ERROR: " +str);
        exit(1);
    }





};

#endif // ERRORHANDLER_H
