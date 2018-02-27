#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#include <QString>
#include <QDebug>
#include "source/data_pmm.h"
#include <stdio.h>
#include <iostream>
#include <QTextEdit>
#include <exception>
using namespace std;

class FatalErrorException: public exception
{
public:
    QString message;
    FatalErrorException(QString msg)
    {
        message = msg;
    }
};

class ErrorHandler
{
public:
    ErrorHandler();
    static ErrorHandler e;
    int m_level = 0;

    int ERROR_ONLY = 2;
    int DEBUG_HIGH = 1;
    int DEBUG_LOW = 0;

    QString m_teOut;


    void OutputText(QString str) {
        std::cout << str.toStdString() << std::endl;
        m_teOut = m_teOut + str + "\n";
    }

    void Message(QString str, int lvl=0) {
        QString s ="";
        for (int i=0;i<lvl;i++)
            s+=" ";

        s = s + str + "\n";
        std::cout << s.toStdString();
        m_teOut = m_teOut + s;

    }

    void DebugHigh(QString str, int lvl=0) {
        if (m_level<=DEBUG_HIGH)
            Message(str, lvl);
    }

    void DebugLow(QString str, int lvl=0) {
        if (m_level<=DEBUG_LOW)
            Message(str, lvl);
    }
    bool exitOnError= true;

    void Error(QString str) {
        QString msg = "";
        msg +="\n**** FATAL ERROR on line: " + QString::number(Pmm::Data::d.lineNumber+1);
        msg+="\nSource: " + Pmm::Data::d.currentLineText;
        msg+="\nMessage: " + str;
//        Message("\n**** FATAL ERROR on line: " + QString::number(Pmm::Data::d.lineNumber+1));
  //      Message("Source: " + Pmm::Data::d.currentLineText);
        throw FatalErrorException(msg);
        //Message(str);

        //if (exitOnError)
        //    exit(1);
    }

    void CatchError(FatalErrorException e, QString extraMessage="") {
        Message(extraMessage + e.message);
        if (exitOnError)
            exit(1);
    }





};

#endif // ERRORHANDLER_H
