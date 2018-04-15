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
    reservedWords.append(Token(TokenType::ELSE,"ELSE"));
    reservedWords.append(Token(TokenType::OR,"OR"));
    reservedWords.append(Token(TokenType::AND,"AND"));
    reservedWords.append(Token(TokenType::POINTER,"POINTER"));
    reservedWords.append(Token(TokenType::AT,"AT"));
    reservedWords.append(Token(TokenType::INCLUDE,"INCLUDE"));
    reservedWords.append(Token(TokenType::DEFINE,"DEFINE"));
    reservedWords.append(Token(TokenType::IFDEF,"IFDEF"));
    reservedWords.append(Token(TokenType::IFNDEF,"IFNDEF"));
    reservedWords.append(Token(TokenType::ENDIF,"ENDIF"));
    reservedWords.append(Token(TokenType::OFFPAGE,"OFFPAGE"));
    reservedWords.append(Token(TokenType::ONPAGE,"ONPAGE"));
    reservedWords.append(Token(TokenType::STEP,"STEP"));
    reservedWords.append(Token(TokenType::UNROLL,"UNROLL"));
//    reservedWords.append(Token(TokenType::LOOPX,"LOOPX"));
//    reservedWords.append(Token(TokenType::LOOPY,"LOOPY"));


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
                BuiltInFunction::Type::INTEGER
               //  << BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["togglebit"] = BuiltInFunction(
                "togglebit",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
               //  << BuiltInFunction::Type::INTEGER
                );
    builtInFunctions["getbit"] = BuiltInFunction(
                "getbit",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
               //  << BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["memcpy"] = BuiltInFunction(
                "memcpy",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);

    builtInFunctions["unrolledmemcpy"] = BuiltInFunction(
                "unrolledmemcpy",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER);

    builtInFunctions["memcpylarge"] = BuiltInFunction(
                "memcpylarge",
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

    builtInFunctions["init16x8mul"] = BuiltInFunction(
                "init16x8mul",
                QList<BuiltInFunction::Type>());

    builtInFunctions["init8x8div"] = BuiltInFunction(
                "init8x8div",
                QList<BuiltInFunction::Type>());

    builtInFunctions["init16x8div"] = BuiltInFunction(
                "init16x8div",
                QList<BuiltInFunction::Type>());



    builtInFunctions["moveto"] = BuiltInFunction(
                "moveto",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER <<
                BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER);

    builtInFunctions["copycharsetfromrom"] = BuiltInFunction(
                "copycharsetfromrom",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
             );


    builtInFunctions["inc"] = BuiltInFunction(
                "inc",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
             );


    builtInFunctions["dec"] = BuiltInFunction(
                "dec",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
             );




/*    builtInFunctions["pokescreen"] = BuiltInFunction(
                "pokescreen",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER);

    builtInFunctions["pokescreencolor"] = BuiltInFunction(
                "pokescreencolor",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER << BuiltInFunction::Type::INTEGER<<BuiltInFunction::Type::INTEGER);

*/
    builtInFunctions["fill"] = BuiltInFunction(
                "fill",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["scrollx"] = BuiltInFunction(
                "scrollx",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["scrolly"] = BuiltInFunction(
                "scrolly",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["incscreenx"] = BuiltInFunction(
                "incscreenx",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["setmemoryconfig"] = BuiltInFunction(
                "setmemoryconfig",
                QList<BuiltInFunction::Type>()<<
                BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["enablerasterirq"] = BuiltInFunction(
                "enablerasterirq",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["startirq"] = BuiltInFunction(
                "startirq",
                QList<BuiltInFunction::Type>() << BuiltInFunction::Type::INTEGER
                );


    builtInFunctions["closeirq"] = BuiltInFunction(
                "closeirq",
                QList<BuiltInFunction::Type>()
                );


    builtInFunctions["enableirq"] = BuiltInFunction(
                "enableirq",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["preventirq"] = BuiltInFunction(
                "preventirq",
                QList<BuiltInFunction::Type>()
                );


    builtInFunctions["inczp"] = BuiltInFunction(
                "inczp",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                );


    builtInFunctions["hidebordery"] = BuiltInFunction(
                "hidebordery",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["hideborderx"] = BuiltInFunction(
                "hideborderx",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                );


    builtInFunctions["transformcolors"] = BuiltInFunction(
                "transformcolors",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                );



    builtInFunctions["copyhalfscreen"] = BuiltInFunction(
                "copyhalfscreen",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                );
    builtInFunctions["copyfullscreen"] = BuiltInFunction(
                "copyfullscreen",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                );

/*    builtInFunctions["sin"] = BuiltInFunction(
                "sin",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );
*/
/*    builtInFunctions["and"] = BuiltInFunction(
                "and",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["or"] = BuiltInFunction(
                "or",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER<<
                BuiltInFunction::Type::INTEGER
                );
*/
    builtInFunctions["printstring"] = BuiltInFunction(
                "printstring",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::STRING << BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
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
                << BuiltInFunction::Type::INTEGER
                );



    builtInFunctions["copyzpdata"] = BuiltInFunction(
                "copyzpdata",
                QList<BuiltInFunction::Type>()
                << BuiltInFunction::Type::INTEGER
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

    builtInFunctions["clearbitmap"] = BuiltInFunction(
                "clearbitmap",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["call"] = BuiltInFunction(
                "call",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["disableciainterrupts"] = BuiltInFunction(
                "disableciainterrupts",
                QList<BuiltInFunction::Type>()
                );

/*    builtInFunctions["enableinterrupts"] = BuiltInFunction(
                "enableinterrupts",
                QList<BuiltInFunction::Type>()
                );
*/
    builtInFunctions["kernalinterrupt"] = BuiltInFunction(
                "kernalinterrupt",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["loop"] = BuiltInFunction(
                "loop",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["clearsound"] = BuiltInFunction(
                "clearsound",
                QList<BuiltInFunction::Type>()
                );


    builtInFunctions["rasterirq"] = BuiltInFunction(
                "rasterirq",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["waitforraster"] = BuiltInFunction(
                "waitforraster",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["waitnoraster"] = BuiltInFunction(
                "waitnoraster",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );


    builtInFunctions["setspriteloc"] = BuiltInFunction(
                "setspriteloc",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["swap"] = BuiltInFunction(
                "swap",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );
    builtInFunctions["setmulticolormode"] = BuiltInFunction(
                "setmulticolormode",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["setregularcolormode"] = BuiltInFunction(
                "setregularcolormode",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["setbitmapmode"] = BuiltInFunction(
                "setbitmapmode",
                QList<BuiltInFunction::Type>()
                );


    builtInFunctions["settextmode"] = BuiltInFunction(
                "settextmode",
                QList<BuiltInFunction::Type>()

                );


    builtInFunctions["setbank"] = BuiltInFunction(
                "setbank",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["abs"] = BuiltInFunction(
                "abs",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["copyimagecolordata"] = BuiltInFunction(
                "copyimagecolordata",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );



}


