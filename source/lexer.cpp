#include "lexer.h"
#include <QDebug>

#include <iostream>
using namespace std;

Lexer::Lexer()
{

}

void Lexer::IncludeFiles()
{
    QRegExp rx("\\{\\s*\\$include.*\\}", Qt::CaseInsensitive);
    QStringList list;
    int pos = 0;
    QString newText = m_orgText;
    m_text = m_orgText;
   // return;
    while ((pos = rx.indexIn(m_orgText, pos)) != -1) {
/*        qDebug() <<rx.cap(0);
        qDebug() << pos << " with " << rx.matchedLength();*/
        QString filename= rx.cap(0).toLower().remove("{").remove("}").remove("$include").trimmed();
        qDebug() << "FIle " << filename;
        QString include = loadTextFile(m_path +"/" +filename);
        qDebug() << "File loaded!";
//        newText.remove(pos, rx.matchedLength());
        newText.replace(rx.cap(0), include);
        pos += rx.matchedLength();
    }
    m_text = newText;
//    qDebug() << newText;
//    exit(1);
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
        if (Pmm::Data::d.lineNumber<m_lines.count())
        if (m_currentChar=="\n") {
            Pmm::Data::d.lineNumber ++;
            if (Pmm::Data::d.lineNumber<m_lines.count())
            Pmm::Data::d.currentLineText = m_lines[Pmm::Data::d.lineNumber];
            m_localPos = 0;
        }


    }

}

void Lexer::SkipWhiteSpace()
{
    while (!m_finished && (m_currentChar==" "|| m_currentChar=="\n" || m_currentChar=="\t"))
        Advance();
}

void Lexer::SkipComment()
{
    while (!(m_currentChar== "*" && peek()=="/") && !m_finished)

        Advance();

    Advance();
    Advance();

}

void Lexer::SkipUntilNewLine()
{
    while (!(m_currentChar== "\n") && !m_finished)

        Advance();

}

QString Lexer::loadTextFile(QString filename)
{
    QFile file(filename);
    if(!file.open( QIODevice::ReadOnly|QIODevice::Text ) ) {
        ErrorHandler::e.Error("Could not open file for inclusion: " + filename);
    }
    QTextStream in(&file);
    QString text ="";
    while(!in.atEnd())
        text+= in.readLine();
    return text;
}

Token Lexer::Number()
{
    QString res="";
    while (!m_finished && Syntax::s.digitAll.contains(m_currentChar)) {
        res+=m_currentChar;
        Advance();
    }
    if (m_currentChar==".") {
        res+=m_currentChar;
        Advance();
        while (!m_finished && Syntax::s.digitAll.contains(m_currentChar)) {
            res+=m_currentChar;
            Advance();
        }


        return Token(TokenType::REAL_CONST, res.toFloat());
    }
    bool ok;
    float val = 0;
    // Memory address
    bool isConstant = false;
    if (res.contains("#")) {
        res.remove("#");
        isConstant = true;
    }

    if (res.contains("$")) {
        res.remove("$");
        val = res.toInt(&ok, 16);
    }
    else
    if (res.contains("%")) {
        res.remove("%");
        val = res.toInt(&ok, 2);
    }



    else
        val = res.toFloat();

    if (isConstant)
        return Token(TokenType::INTEGER_CONST, val);
    else
        return Token(TokenType::ADDRESS, val);

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

void Lexer::Initialize()
{
    IncludeFiles();
    m_currentChar = m_text[0];
}

Token Lexer::GetNextToken()
{
    while (!m_finished) {
        if (m_currentChar==" " || m_currentChar=="\n" || m_currentChar=="\t") {
            SkipWhiteSpace();
            continue;
        }
        if (m_currentChar == "\t" ) {
            Advance();
            continue;
        }

        if (m_currentChar=="/") {
            if (peek()=="*") {
                Advance();
                Advance();
                SkipComment();
                continue;
            }

        }

        if (m_currentChar=="/") {
            if (peek()=="/") {
                SkipUntilNewLine();
                continue;
            }

        }
        if (m_currentChar=="\"") {
            Advance();
            return String();
        }

        if (m_currentChar=="[") {
            Advance();
            return Token(TokenType::LBRACKET,"[");
        }
        if (m_currentChar=="]") {
            Advance();
            return Token(TokenType::RBRACKET,"]");
        }

        if (m_currentChar==",") {
            Advance();
            return Token(TokenType::COMMA, ":");
        }

        if (Syntax::s.isDigit(m_currentChar)) {
            return Number();
        }

        if (Syntax::s.isAlpha(m_currentChar)) {
          //  qDebug() << m_currentChar << " is Alpha";

            return _Id();
        }


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
