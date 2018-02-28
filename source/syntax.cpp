#include "syntax.h"
#include <QtMath>

Syntax Syntax::s;

Syntax::Syntax()
{
    SetupReservedWords();
    SetupBuiltinFunctions();
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
    //reservedWords.append(Token(TokenType::WRITELN,"WRITELN"));
    reservedWords.append(Token(TokenType::IF,"IF"));
    reservedWords.append(Token(TokenType::THEN,"THEN"));
    reservedWords.append(Token(TokenType::FOR,"FOR"));
    reservedWords.append(Token(TokenType::TO,"TO"));
    reservedWords.append(Token(TokenType::DO,"DO"));
    reservedWords.append(Token(TokenType::WHILE,"WHILE"));

}

void Syntax::SetupBuiltinFunctions()
{
    QVector<BuiltInFunction::Type> writeln;
    writeln.append(BuiltInFunction::STRING);
    writeln.append(BuiltInFunction::INTEGER);
    builtInFunctions["writeln"] = (BuiltInFunction(
                                "writeln",  writeln));


    QVector<BuiltInFunction::Type> print;
    print.append(BuiltInFunction::INTEGER);
    print.append(BuiltInFunction::INTEGER);
    print.append(BuiltInFunction::STRING);
    print.append(BuiltInFunction::INTEGER);
    builtInFunctions["print"] = (BuiltInFunction(
                                "print",  print));

    QVector<BuiltInFunction::Type> poke;
    poke.append(BuiltInFunction::INTEGER);
    poke.append(BuiltInFunction::INTEGER);
    poke.append(BuiltInFunction::INTEGER);
    builtInFunctions["poke"] = (BuiltInFunction(
                                "poke",  poke));

    QVector<BuiltInFunction::Type> peek;
    peek.append(BuiltInFunction::INTEGER);
    peek.append(BuiltInFunction::INTEGER);
    peek.append(BuiltInFunction::INTEGER);
    builtInFunctions["peek"] = (BuiltInFunction(
                                "peek",  peek));

}

