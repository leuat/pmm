#ifndef TOKEN_H
#define TOKEN_H

#include <QString>


class TokenType {
public:
    enum Type {
        INTEGER, PLUS, MINUS, MUL, DIV, LPAREN,
        RPAREN, TEOF, ID, ASSIGN, BEGIN,
        END, SEMI, DOT, VAR, REAL,
        PROGRAM, COLON, COMMA, INTEGER_CONST,
        REAL_CONST, PROCEDURE, WRITELN, STRING,
        IF, THEN, EQUALS,NOTEQUALS, GREATER, LESS,
        FOR, TO, DO, NADA};

    static QString types[];
    static QString getType(Type t) {
        return types[t];
    }

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
    QString getType() {
        return TokenType::types[m_type];
    }

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
