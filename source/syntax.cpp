#include "syntax.h"
#include <QtMath>


Syntax Syntax::s;

Syntax::Syntax()
{
    SetupReservedWords();
    SetupBuiltinFunctions();
    SetupKeys();
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
    reservedWords.append(Token(TokenType::CSTRING,"CSTRING"));
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



    builtInFunctions["wait"] = (BuiltInFunction(
    "wait",  QList<BuiltInFunction::Type>() << BuiltInFunction::Type::INTEGER, true));

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


    builtInFunctions["jammer"] = BuiltInFunction(
                "jammer",
                QList<BuiltInFunction::Type>()
                 << BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER);

    builtInFunctions["nmiirq"] = BuiltInFunction(
                "nmiirq",
                QList<BuiltInFunction::Type>()
                << BuiltInFunction::Type::INTEGER);


    builtInFunctions["fld"] = BuiltInFunction(
                "fld",
                QList<BuiltInFunction::Type>()
                << BuiltInFunction::Type::INTEGER);


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
                << BuiltInFunction::Type::INTEGER
                );
    builtInFunctions["copyfullscreen"] = BuiltInFunction(
                "copyfullscreen",
                QList<BuiltInFunction::Type>()<< BuiltInFunction::Type::INTEGER
                << BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["copyfullscreenunrolled"] = BuiltInFunction(
                "copyfullscreenunrolled",
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

    builtInFunctions["keypressed"] = BuiltInFunction(
                "keypressed",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["abs"] = BuiltInFunction(
                "abs",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                );

    builtInFunctions["return"] = BuiltInFunction(
                "return",
                QList<BuiltInFunction::Type>()
                );

    builtInFunctions["returninterrupt"] = BuiltInFunction(
                "returninterrupt",
                QList<BuiltInFunction::Type>()
                );


    builtInFunctions["copyimagecolordata"] = BuiltInFunction(
                "copyimagecolordata",
                QList<BuiltInFunction::Type>()
                <<BuiltInFunction::Type::INTEGER
                <<BuiltInFunction::Type::INTEGER
                );



}

void Syntax::SetupKeys()
{
    int row[8] = {0b11111110,0b11111101,0b11111011,0b11110111,0b11101111,0b11011111,0b10111111,0b01111111};
    int column[8] = {0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
    m_c64keys.clear();
    m_c64keys[0x01] = C64Key("A","KEY_A",0x01 , row[1], column[2]);
    m_c64keys[0x02] = C64Key("B","KEY_B",0x02 , row[3], column[4]);
    m_c64keys[0x03] = C64Key("C","KEY_C",0x03 , row[2], column[4]);
    m_c64keys[0x04] = C64Key("D","KEY_D",0x04 , row[2], column[2]);
    m_c64keys[0x05] = C64Key("E","KEY_E",0x05 , row[1], column[6]);
    m_c64keys[0x06] = C64Key("F","KEY_F",0x06 , row[2], column[5]);
    m_c64keys[0x07] = C64Key("G","KEY_G",0x07 , row[3], column[2]);
    m_c64keys[0x08] = C64Key("H","KEY_H",0x08 , row[3], column[5]);
    m_c64keys[0x09] = C64Key("I","KEY_I",0x09 , row[4], column[1]);
    m_c64keys[0x0A] = C64Key("J","KEY_J",0x0A , row[4], column[2]);
    m_c64keys[0x0B] = C64Key("K","KEY_K",0x0B , row[4], column[5]);
    m_c64keys[0x0C] = C64Key("L","KEY_L",0x0C , row[5], column[2]);
    m_c64keys[0x0D] = C64Key("M","KEY_M",0x0D , row[4], column[4]);
    m_c64keys[0x0E] = C64Key("N","KEY_N",0x0E , row[4], column[7]);
    m_c64keys[0x0F] = C64Key("O","KEY_O",0x0F , row[4], column[6]);
    m_c64keys[0x10] = C64Key("P","KEY_P",0x10 , row[5], column[1]);
    m_c64keys[0x11] = C64Key("Q","KEY_Q",0x11 , row[7], column[6]);
    m_c64keys[0x12] = C64Key("R","KEY_R",0x12 , row[2], column[1]);
    m_c64keys[0x13] = C64Key("S","KEY_S",0x13 , row[1], column[5]);
    m_c64keys[0x14] = C64Key("T","KEY_T",0x14 , row[2], column[6]);
    m_c64keys[0x15] = C64Key("U","KEY_U",0x15 , row[3], column[6]);
    m_c64keys[0x16] = C64Key("V","KEY_V",0x16 , row[3], column[7]);
    m_c64keys[0x17] = C64Key("W","KEY_W",0x17 , row[1], column[1]);
    m_c64keys[0x18] = C64Key("X","KEY_X",0x18 , row[2], column[7]);
    m_c64keys[0x19] = C64Key("Y","KEY_Y",0x19 , row[3], column[1]);
    m_c64keys[0x1A] = C64Key("Z","KEY_Z",0x1A , row[1], column[4]);
    m_c64keys[0x30] = C64Key("0","KEY_0",0x30 , row[4], column[3]);
    m_c64keys[0x31] = C64Key("1","KEY_1",0x31 , row[7], column[0]);
    m_c64keys[0x32] = C64Key("2","KEY_2",0x32 , row[7], column[3]);
    m_c64keys[0x33] = C64Key("3","KEY_3",0x33 , row[1], column[0]);
    m_c64keys[0x34] = C64Key("4","KEY_4",0x34 , row[1], column[3]);
    m_c64keys[0x35] = C64Key("5","KEY_5",0x35 , row[2], column[0]);
    m_c64keys[0x36] = C64Key("6","KEY_6",0x36 , row[2], column[3]);
    m_c64keys[0x37] = C64Key("7","KEY_7",0x37 , row[3], column[0]);
    m_c64keys[0x38] = C64Key("8","KEY_8",0x38 , row[3], column[3]);
    m_c64keys[0x39] = C64Key("9","KEY_9",0x39 , row[4], column[0]);

    m_c64keys[0xF1] = C64Key("F1","KEY_F1",0xF1 , row[0], column[4]);
    m_c64keys[0xF3] = C64Key("F3","KEY_F3",0xF3 , row[0], column[5]);
    m_c64keys[0xF5] = C64Key("F5","KEY_F5",0xF5 , row[0], column[6]);
    m_c64keys[0xF7] = C64Key("F7","KEY_F7",0xF7 , row[0], column[3]);

    m_c64keys[0x2b] = C64Key("+","KEY_PLUS",0x2b , row[5], column[0]);
    m_c64keys[0x1c] = C64Key("£","KEY_POUND",0x1c , row[6], column[0]);
    m_c64keys[0xF0] = C64Key("ENTER","KEY_ENTER",0xF0 , row[0], column[1]);
    m_c64keys[0x2a] = C64Key("*","KEY_ASTERIX",0x2a , row[6], column[1]);
    m_c64keys[0x3b] = C64Key(";","KEY_SEMI",0x3b , row[6], column[2]);
    m_c64keys[0xEF] = C64Key("HOME","KEY_HOME",0xEF , row[6], column[3]);
    m_c64keys[0x20] = C64Key("SPACE","KEY_SPACE",0x20 , row[7], column[4]);
    m_c64keys[0xEE] = C64Key("COMMODORE","KEY_COMMODORE",0xEE , row[7], column[5]);
    m_c64keys[0x3a] = C64Key(":","KEY_COLON",0x3a , row[5], column[5]);
    m_c64keys[0x3d] = C64Key("=","KEY_EQUALS",0x3d , row[6], column[5]);

}


