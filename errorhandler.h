#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#include <QString>
#include <QDebug>
#include "data.h"
#include <stdio.h>
#include <iostream>

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

        std::cout << (s + str).toStdString() << std::endl;

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
        Message("\n**** FATAL ERROR on line: " + QString::number(Data::d.lineNumber+1));
        Message("Source: " + Data::d.currentLineText);
        Message(str);
        exit(1);
    }





};

#endif // ERRORHANDLER_H
