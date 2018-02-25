#ifndef SYNTAX_H
#define SYNTAX_H

#include <QString>
#include <QVector>
#include "token.h"
#include <QDebug>
#include <QMap>

#include "errorhandler.h"


class PVar {
public:
    TokenType::Type m_type;
    float m_fVal;
    bool m_isError = false;
    QString m_strVal;
    PVar() {
        m_isError = true;
    }
    PVar(const PVar& o) {
        m_type = o.m_type;
        m_fVal = o.m_fVal;
        m_strVal = o.m_strVal;
        m_isError = o.m_isError;
    }

    PVar(float f) {
        m_fVal = f;
        m_type = TokenType::REAL;
    }
    PVar(QString f) {
        m_strVal = f;
        m_type = TokenType::STRING;
    }

    bool operator==(const PVar& b) {
        if (m_type==TokenType::REAL && b.m_type==TokenType::REAL)
            return m_fVal == b.m_fVal;
        if (m_type==TokenType::STRING && b.m_type==TokenType::STRING)
            return m_strVal == b.m_strVal;
        ErrorHandler::e.Error("PVar::== - unknown type comparison");
        return false;
   }

    bool operator>(const PVar& b) {
        if (m_type==TokenType::REAL && b.m_type==TokenType::REAL)
            return m_fVal > b.m_fVal;
        if (m_type==TokenType::STRING || b.m_type==TokenType::STRING)
            ErrorHandler::e.Error("PVar::> cannot compare strings");

        ErrorHandler::e.Error("PVar::> - unknown type comparison");
        return false;
   }

    bool operator<(const PVar& b) {
        if (m_type==TokenType::REAL && b.m_type==TokenType::REAL)
            return m_fVal < b.m_fVal;
        if (m_type==TokenType::STRING || b.m_type==TokenType::STRING)
            ErrorHandler::e.Error("PVar::< cannot compare strings");

        ErrorHandler::e.Error("PVar::< - unknown type comparison");
        return false;
   }

    PVar operator+(const PVar& b)  {
        if (m_type==TokenType::REAL)
            return PVar(m_fVal +b.m_fVal);
        if (m_type==TokenType::STRING)
            return PVar(m_strVal + b.m_strVal);
        return PVar();
    }
    PVar operator-(const PVar& b)  {
        if (m_type==TokenType::REAL)
            return PVar(m_fVal -b.m_fVal);
        if (m_type==TokenType::STRING) {
            qDebug() << "Error: cannot subtract strings";
        }
        return PVar();
    }
    PVar operator/(const PVar& b)  {
        if (m_type==TokenType::REAL)
            return PVar(m_fVal /b.m_fVal);
        if (m_type==TokenType::STRING) {
            qDebug() << "Error: cannot divide strings";
        }
        return PVar();
    }
    PVar operator*(const PVar& b)   {
        if (m_type==TokenType::REAL)
            return PVar(m_fVal *b.m_fVal);
        if (m_type==TokenType::STRING) {
            qDebug() << "Error: cannot mul strings";
        }
        return PVar();
    }
    PVar operator*(const float& b)  {
        if (m_type==TokenType::REAL)
            return PVar(m_fVal *b);
        if (m_type==TokenType::STRING) {
            qDebug() << "Error: cannot mul strings";
        }
        return PVar();
    }

    QString toString() {
        if (m_type==TokenType::STRING)
            return m_strVal;
        if (m_type==TokenType::REAL)
            return QString::number(m_fVal);
        return "PVar not defined(!)";
    }

};




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

    QMap<QString, PVar*> globals;


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
              //  qDebug() << "Found token " <<  val;

                return t;
            }

        //exit(1);
        return Token(TokenType::ID, val);
    }
};

#endif // SYNTAX_H
