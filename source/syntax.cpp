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
    reservedWords.append(Token(TokenType::ARRAY,"ARRAY"));
    reservedWords.append(Token(TokenType::OF,"OF"));
    reservedWords.append(Token(TokenType::BYTE,"BYTE"));
    reservedWords.append(Token(TokenType::INCBIN,"INCBIN"));
    reservedWords.append(Token(TokenType::STRING,"STRING"));

}

void Syntax::SetupBuiltinFunctions()
{
    builtInFunctions["writeln"] = BuiltInFunction(
                "writeln",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::STRING<< BuiltInFunction::Type::INTEGER );

    builtInFunctions["poke"] = BuiltInFunction(
                "poke",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);

    builtInFunctions["peek"] = BuiltInFunction(
                "peek",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);

    builtInFunctions["memcpy"] = BuiltInFunction(
                "memcpy",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);


    builtInFunctions["initrandom"] = (BuiltInFunction(
                                "initrandom",  QList<BuiltInFunction::Type>()));

    builtInFunctions["initsinetable"] = (BuiltInFunction(
                                "initsinetable",  QList<BuiltInFunction::Type>()));

    builtInFunctions["rand"] = BuiltInFunction(
                "rand",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);


    builtInFunctions["initmoveto"] = BuiltInFunction(
                "initmoveto",
                QList<BuiltInFunction::Type>());

    builtInFunctions["initeightbitmul"] = BuiltInFunction(
                "initeightbitmul",
                QList<BuiltInFunction::Type>());



    builtInFunctions["moveto"] = BuiltInFunction(
                "moveto",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER);

    builtInFunctions["pokescreen"] = BuiltInFunction(
                "pokescreen",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER);


    builtInFunctions["fill"] = BuiltInFunction(
                "fill",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["scroll"] = BuiltInFunction(
                "scroll",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["incscreenx"] = BuiltInFunction(
                "incscreenx",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["sin"] = BuiltInFunction(
                "sin",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["and"] = BuiltInFunction(
                "and",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["or"] = BuiltInFunction(
                "or",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["printstring"] = BuiltInFunction(
                "printstring",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::STRING << BuiltInFunction::Type::INTEGER
                );


    builtInFunctions["printnumber"] = BuiltInFunction(
                "printnumber",
                QList<BuiltInFunction::Type>()<<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["initprintstring"] = BuiltInFunction(
                "initprintstring",
                QList<BuiltInFunction::Type>()
                );


}


