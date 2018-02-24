#ifndef TOKEN_H
#define TOKEN_H

#include <QString>


class TokenType {
public:
    enum Type {
        INTEGER, PLUS, MINUS, MUL, DIV, LPAREN,
        RPAREN, TEOF, ID, ASSIGN, BEGIN,
        END, SEMI, DOT, VAR, REAL,
        PROGRAM, COLON, COMMA, INTEGER_CONST, REAL_CONST};
    QString m_value;
    Type m_type;
    TokenType() {}
    TokenType (Type t, QString v) {
        m_type = t;
        m_value = v;
    }
};


class Token
{
public:
    TokenType::Type m_type;
    QString m_value;
    int m_intVal;

    Token();


    Token(TokenType::Type t, QString val) {
        m_value = val;
        m_type = t;
    }
    Token(TokenType::Type t, int val) {
        m_intVal = val;
        m_type = t;
    }

};

#endif // TOKEN_H
