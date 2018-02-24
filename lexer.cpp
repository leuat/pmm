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
    else {
        m_currentChar = m_text[m_pos];
        if (m_currentChar=="\n") {
            m_lineNumber++;
        }

    }

}

void Lexer::SkipWhiteSpace()
{
    while (!m_finished && (m_currentChar==" "||m_currentChar=="\n" ))
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

Token Lexer::_Id()
{
    QString result="";
    while (!m_finished && Syntax::s.isAlnum(m_currentChar)) {
        result +=m_currentChar;
        Advance();
    }
    return Syntax::s.GetID(result);

}

QString Lexer::peek()
{
    if (m_pos+1>=m_text.length())
        return "";
    return QString(m_text[m_pos+1]);
}

Token Lexer::GetNextToken()
{
    while (!m_finished) {
        if (m_currentChar==" " || m_currentChar=="\n")
            SkipWhiteSpace();

        if (Syntax::s.isAlpha(m_currentChar)) {
            return _Id();
        }

        if (Syntax::s.isDigit(m_currentChar))
            return Token(TokenType::INTEGER, Integer());

        if (m_currentChar==":" && peek()=="=") {
            Advance();
            Advance();
            return Token(TokenType::ASSIGN,":=");
        }
        if (m_currentChar==";") {
            Advance();
            return Token(TokenType::SEMI,";");
        }

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
        if (m_currentChar==".") {
            Advance();
            Advance();
            return Token(TokenType::DOT, ".");
        }
        Error(m_currentChar);


    }
    return Token(TokenType::TEOF, "");
}
