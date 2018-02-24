#include "lexer.h"
#include <QDebug>

Lexer::Lexer()
{

}

void Lexer::Error(QString text)
{
    qDebug() << "Error parsing: " << text;
    exit(1);
}

void Lexer::Advance()
{
    m_pos++;
    if (m_pos>m_text.length()-1) {
        m_finished = true;
    }
    else
        m_currentChar = m_text[m_pos];

}

void Lexer::SkipWhiteSpace()
{
    while (!m_finished && m_currentChar==" ")
        Advance();
}

int Lexer::Integer()
{
    QString res="";
    while (!m_finished && Syntax::s.digit.contains(m_currentChar)) {
        res+=m_currentChar;
        Advance();
    }
    return res.toInt();

}

Token Lexer::GetNextToken()
{
    while (!m_finished) {
        if (m_currentChar==" ")
            SkipWhiteSpace();

        if (Syntax::s.isDigit(m_currentChar))
            return Token(TokenType::INTEGER, Integer());

        if (m_currentChar=="+") {
            Advance();
            return Token(TokenType::PLUS, "+");
        }
        if (m_currentChar=="-") {
            Advance();
            return Token(TokenType::MINUS, "-");
        }
        if (m_currentChar=="*") {
            Advance();
            return Token(TokenType::MUL, "*");
        }
        if (m_currentChar=="/") {
            Advance();
            return Token(TokenType::DIV, "/");
        }
        if (m_currentChar=="(") {
            Advance();
            return Token(TokenType::LPAREN, "(");
        }
        if (m_currentChar==")") {
            Advance();
            return Token(TokenType::RPAREN, ")");
        }
        Error(m_currentChar);


    }
    return Token(TokenType::TEOF, "");
}
