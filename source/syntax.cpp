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
    reservedWords.append(Token(TokenType::ASM,"ASM"));
    reservedWords.append(Token(TokenType::INCSID,"INCSID"));
    reservedWords.append(Token(TokenType::INTERRUPT,"INTERRUPT"));

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
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);


    builtInFunctions["initrandom"] = (BuiltInFunction(
                                "initrandom",  QList<BuiltInFunction::Type>(), true));

    builtInFunctions["initsinetable"] = (BuiltInFunction(
                                "initsinetable",  QList<BuiltInFunction::Type>(), true));

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

    builtInFunctions["pokescreencolor"] = BuiltInFunction(
                "pokescreencolor",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER<<BuiltInFunction::Type::INTEGER);


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

    builtInFunctions["initjoystick"] = BuiltInFunction(
                "initjoystick",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["joystick"] = BuiltInFunction(
                "joystick",
               QList<BuiltInFunction::Type>()
                );


    builtInFunctions["spritepos"] = BuiltInFunction(
                "spritepos",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                );


    builtInFunctions["playsound"] = BuiltInFunction(
                "playsound",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["initsid"] = BuiltInFunction(
                "initsid",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["clearscreen"] = BuiltInFunction(
                "clearscreen",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["call"] = BuiltInFunction(
                "call",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["disableinterrupts"] = BuiltInFunction(
                "disableinterrupts",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["enableinterrupts"] = BuiltInFunction(
                "enableinterrupts",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["kernelinterrupt"] = BuiltInFunction(
                "kernelinterrupt",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["loop"] = BuiltInFunction(
                "loop",
                QList<BuiltInFunction::Type>()
                );


    builtInFunctions["rasterirq"] = BuiltInFunction(
                "rasterirq",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["waitraster"] = BuiltInFunction(
                "waitraster",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );
    builtInFunctions["setspriteloc"] = BuiltInFunction(
                "setspriteloc",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );


}


