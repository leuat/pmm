#include "syntax.h"
#include <QtMath>

Syntax Syntax::s;

Syntax::Syntax()
{
    SetupReservedWords();
}

void Syntax::SetupReservedWords()
{
    reservedWords.clear();
    reservedWords.append(Token(TokenType::BEGIN,"BEGIN"));
    reservedWords.append(Token(TokenType::END,"END"));
    reservedWords.append(Token(TokenType::VAR,"VAR"));
    reservedWords.append(Token(TokenType::PROGRAM,"PROGRAM"));
    reservedWords.append(Token(TokenType::DIV,"DIV"));
    reservedWords.append(Token(TokenType::INTEGER,"INTEGER"));
    reservedWords.append(Token(TokenType::REAL,"REAL"));
    reservedWords.append(Token(TokenType::PROCEDURE,"PROCEDURE"));
    reservedWords.append(Token(TokenType::WRITELN,"WRITELN"));
    reservedWords.append(Token(TokenType::IF,"IF"));
    reservedWords.append(Token(TokenType::THEN,"THEN"));
    reservedWords.append(Token(TokenType::FOR,"FOR"));
    reservedWords.append(Token(TokenType::TO,"TO"));
    reservedWords.append(Token(TokenType::DO,"DO"));

}
