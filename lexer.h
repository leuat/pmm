#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include "syntax.h"
#include "token.h"

class Lexer
{
    QString m_text;
    QString m_currentChar;
    uint m_pos = 0;
    bool m_finished = false;

public:
    uint m_lineNumber = 0;
    Lexer();
    Lexer(QString text) {
        m_text = text;
        m_pos = 0;
        m_currentChar = m_text[m_pos];
    }

    void Error(QString text);
    void Advance();
    void SkipWhiteSpace();
    int Integer();
    Token _Id();
    QString peek();

    Token GetNextToken();

};

#endif // LEXER_H
