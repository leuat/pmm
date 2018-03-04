#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include "syntax.h"
#include "token.h"
#include "data_pmm.h"

#include "errorhandler.h"

class Lexer
{
    QString m_currentChar;
    uint m_pos = 0;
    bool m_finished = false;

public:
    QString m_text;
    uint m_localPos = 0;
    QStringList m_lines;
    Lexer();
    Lexer(QString text, QStringList lines) {
        m_text = text;
        m_pos = 0;
        m_currentChar = m_text[m_pos];
        m_lines = lines;
        Pmm::Data::d.Init();
    }

    void Error(QString text);
    void Advance();
    void SkipWhiteSpace();
    void SkipComment();
    Token Number();
    Token _Id();
    Token String();
    QString peek();

    Token GetNextToken();

};

#endif // LEXER_H
