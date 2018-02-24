#ifndef SYNTAX_H
#define SYNTAX_H

#include <QString>
#include <QVector>
#include "token.h"
#include <QDebug>
#include <QMap>

class Syntax
{
public:
    QVector<Token> reservedWords;
    Syntax();
    void SetupReservedWords();
    QString digit = "0123456789";
    QString alpha = "abcdefghijklmnopqrstuvwxyz";
    QString alnum =alpha+digit;

    QMap<QString, float> globals;


    static Syntax s;

    bool isDigit(QString s) {
        return digit.contains(s);
    }
    bool isAlnum(QString s) {
        return alnum.contains(s.toLower());
    }
    bool isAlpha(QString s) {
        return alpha.contains(s.toLower());
    }

    Token GetID(QString val) {
        for (Token& t: reservedWords)
            if (val==t.m_value)
                return t;

        //qDebug() << "Error: could not find token " <<  val;
        //exit(1);
        return Token(TokenType::ID, val);
    }
};

#endif // SYNTAX_H
