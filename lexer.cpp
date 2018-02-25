#include "lexer.h"
#include <QDebug>

Lexer::Lexer()
{

}

void Lexer::Error(QString text)
{
    qDebug() << "Error parsing: " << text << " on line " << m_lineNumber;
    qDebug() << m_lines[m_lineNumber];
    exit(1);
}

void Lexer::Advance()
{
    m_pos++;
    m_localPos++;
    if (m_pos>m_text.length()-1) {
        m_finished = true;
    }
    else {
        m_currentChar = m_text[m_pos];
        if (m_localPos>=m_lines[m_lineNumber].length()) {
            m_lineNumber ++;
            m_localPos = 0;
        }

        //if (m_currentChar=="\n") {
        //    m_lineNumber++;
        //}

    }

}

void Lexer::SkipWhiteSpace()
{
    while (!m_finished && (m_currentChar==" "||m_currentChar=="\n" ))
        Advance();
}

void Lexer::SkipComment()
{
    while (m_currentChar!= "}")
        Advance();
    Advance();
}

Token Lexer::Number()
{
    QString res="";
    while (!m_finished && Syntax::s.digit.contains(m_currentChar)) {
        res+=m_currentChar;
        Advance();
    }
    if (m_currentChar==".") {
        res+=m_currentChar;
        Advance();
        while (!m_finished && Syntax::s.digit.contains(m_currentChar)) {
            res+=m_currentChar;
            Advance();
        }
        return Token(TokenType::REAL_CONST, res.toFloat());
    }
    return Token(TokenType::INTEGER_CONST, res.toFloat());

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


        if (m_currentChar==" " || m_currentChar=="\n") {
            SkipWhiteSpace();
            continue;
        }
        if (m_currentChar == "\t" ) {
            Advance();
            continue;
        }

        if (m_currentChar=="{") {
            Advance();
            SkipComment();
            continue;

        }

        if (m_currentChar=="\"") {
            Advance();
            return Token(TokenType::QUOTATION, "\"");
        }


        if (m_currentChar==",") {
            Advance();
            return Token(TokenType::COMMA, ":");
        }


        if (Syntax::s.isAlpha(m_currentChar)) {
            return _Id();
        }

        if (Syntax::s.isDigit(m_currentChar))
            return Number();

        if (m_currentChar==":" && peek()=="=") {
            Advance();
            Advance();
            return Token(TokenType::ASSIGN,":=");
        }
        if (m_currentChar==":") {
            Advance();
            return Token(TokenType::COLON, ":");
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
            m_text = m_text.replace("\n", "");
            return Token(TokenType::DOT, ".");
        }

        Error(m_currentChar);


    }
    return Token(TokenType::TEOF, "");
}
