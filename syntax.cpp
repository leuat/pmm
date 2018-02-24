#include "syntax.h"

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
}
