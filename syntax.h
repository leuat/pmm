#ifndef SYNTAX_H
#define SYNTAX_H

#include <QString>
#include <QVector>
#include "token.h"
#include <QDebug>
#include <QMap>
#include "pvar.h"
#include "errorhandler.h"




class Syntax
{
public:
    QVector<Token> reservedWords;
    Syntax();
    void SetupReservedWords();
    QString digit = "0123456789";
    QString alpha = "abcdefghijklmnopqrstuvwxyz";
    QString alnum =alpha+digit;
    QString alnumString =alpha+digit+ " ;:æøå!#¤%&/()=.,-+*";
    uint lineNumber = 0;
    void SetupConstants();

    static Syntax s;

    bool isDigit(QString s) {
        return digit.contains(s);
    }
    bool isAlnum(QString s) {
        return alnum.contains(s.toLower());
    }
    bool isString(QString s) {
        return alnumString.contains(s.toLower());
    }

    bool isAlpha(QString s) {
        return alpha.contains(s.toLower());
    }

    Token GetID(QString val) {
        for (Token& t: reservedWords)
            if (val.toUpper()==t.m_value) {
                //qDebug() << "Found token " <<  val;

                return t;
            }

        //exit(1);
        return Token(TokenType::ID, val);
    }
};

#endif // SYNTAX_H
