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
    QString m_orgText = "";
    QString m_text = "";
    uint m_localPos = 0;
    QStringList m_lines;
    QString m_path;
    Lexer();
    Lexer(QString text, QStringList lines, QString path) {
        m_orgText = text;
        m_pos = 0;
        m_path = path;
        m_currentChar = m_text[m_pos];
        m_lines = lines;
        Pmm::Data::d.Init();
    }

    void IncludeFiles();
    void Error(QString text);
    void Advance();
    void SkipWhiteSpace();
    void SkipComment();
    void SkipUntilNewLine();
    QString loadTextFile(QString filename);
    Token Number();
    Token _Id();
    Token String();
    QString peek();
    void Initialize();

    Token GetNextToken();

};

#endif // LEXER_H
