#ifndef SYNTAX_H
#define SYNTAX_H

#include <QString>
#include <QVector>
#include "token.h"
#include <QDebug>
#include <QMap>
#include "pvar.h"
#include "errorhandler.h"




class BuiltInFunction {
public:
    enum Type {STRING, INTEGER, REAL};
    QString m_name;
    QVector<Type> m_params;
    BuiltInFunction() {}
//    QVector<PVar> m_params;

    BuiltInFunction(QString name, QVector<Type> params) {
        m_name = name;
        m_params = params;
    }
};

class Syntax
{
public:
    QVector<Token> reservedWords;
    //QVector<BuiltInFunction> builtinFunctions;
    QMap<QString, BuiltInFunction> builtInFunctions;
    Syntax();
    void SetupReservedWords();
    void SetupBuiltinFunctions();
    QString puredigit = "0123456789#";
    QString digit = "#0123456789$%";
    QString digitAll = "#0123456789$%ABCDEFabcdef";
    QString alpha = "abcdefghijklmnopqrstuvwxyz_";
    QString alnum =alpha+digit;
    QString alnumString =alpha+digit+ " ;:æøå!#¤%&/()=.,-+*";
    uint lineNumber = 0;
    void SetupConstants();

    static Syntax s;

    bool isNumeric(QString s) {
        bool ok;
        int dec = s.toInt(&ok, 10);
        return ok;
    }

    bool isDigit(QString s) {
        // Check if HEX
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
