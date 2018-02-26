#include "lexer.h"
#include <QDebug>


Lexer::Lexer()
{

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
        if (m_localPos>=m_lines[Pmm::Data::d.lineNumber].length()) {
            Pmm::Data::d.lineNumber ++;
            Pmm::Data::d.currentLineText = m_lines[Pmm::Data::d.lineNumber];
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

Token Lexer::String()
{
    QString result="";
    while (!m_finished && m_currentChar!="\"") {
        result +=m_currentChar;
        Advance();
    }
    Advance();
    ErrorHandler::e.DebugLow("Calling Lexer::String with string: " + result);

    return Token(TokenType::STRING, result);

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
            return String();
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

        if (m_currentChar=="=") {
            Advance();
            return Token(TokenType::EQUALS, "=");
        }
        if (m_currentChar==">") {
            Advance();
            return Token(TokenType::GREATER, ">");
        }
        if (m_currentChar=="<") {
            Advance();
            if (m_currentChar==">") {
                Advance();
                return Token(TokenType::NOTEQUALS, "<>");
            }
            return Token(TokenType::LESS, "<");
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
        ErrorHandler::e.Error( "Error parsing: " + m_currentChar );



    }
    return Token(TokenType::TEOF, "");
}
