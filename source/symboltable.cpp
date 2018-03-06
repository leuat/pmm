#include "symboltable.h"
#include <qmath.h>
bool SymbolTable::isInitialized = false;
QMap<QString, Symbol*> SymbolTable::m_constants;

SymbolTable::SymbolTable()
{
    InitBuiltins();
    Initialize();
}

void SymbolTable::Initialize()
{
    if (isInitialized)
        return;
    m_constants["PI"] = new Symbol("PI","REAL", M_PI);
    m_constants["SCREEN_BACKGROUND_COLOR"] = new Symbol("53280","ADDRESS", 53280);
    m_constants["SCREEN_FOREGROUND_COLOR"] = new Symbol("53281","ADDRESS", 53281);
    m_constants["SCREEN_LOCATION1"] = new Symbol("$0400","ADDRESS", 0x0400+200);
    m_constants["SCREEN_LOCATION2"] = new Symbol("$0400","ADDRESS", 0x0400+400);
    m_constants["SCREEN_LOCATION3"] = new Symbol("$0400","ADDRESS", 0x0400+600);
    m_constants["SCREEN_LOCATION4"] = new Symbol("$0400","ADDRESS", 0x0400+800);
    m_constants["SCREEN_LOCATION5"] = new Symbol("$0400","ADDRESS", 0x0400);
    m_constants["RASTERLINE_POS"] = new Symbol("$D012","ADDRESS", 0xd012);
    m_constants["BLACK"] = new Symbol("#0","BYTE", 0);
    m_constants["WHITE"] = new Symbol("#1","BYTE", 1);
    m_constants["RED"] = new Symbol("#2","BYTE", 2);
    m_constants["CYAN"] = new Symbol("#3","BYTE", 3);
    m_constants["PURPLE"] = new Symbol("#4","BYTE", 4);
    m_constants["GREEN"] = new Symbol("#5","BYTE", 5);
    m_constants["BLUE"] = new Symbol("#6","BYTE", 6);
    m_constants["YELLOW"] = new Symbol("#7","BYTE", 7);
    m_constants["ORANGE"] = new Symbol("#8","BYTE", 8);
    m_constants["BROWN"] = new Symbol("#9","BYTE", 9);
    m_constants["LIGHT_RED"] = new Symbol("#10","BYTE", 10);
    m_constants["DARK_GREY"] = new Symbol("#11","BYTE", 11);
    m_constants["GREY"] = new Symbol("#12","BYTE", 12);
    m_constants["LIGHT_GREEN"] = new Symbol("#13","BYTE", 13);
    m_constants["LIGHT_BLUE"] = new Symbol("#14","BYTE", 14);
    m_constants["LIGHT_GREY"] = new Symbol("#15","BYTE", 15);

    m_constants["SPRITE_POS"] = new Symbol("$D000","ADDRESS", 0xD000);
    m_constants["SPRITE_DATA_LOC"] = new Symbol("$07f8", "ADDRESS", 0x07f8);
    m_constants["SPRITE_BITMASK"] = new Symbol("$d015", "ADDRESS", 0xd015);
    m_constants["SPRITE_COLOR"] = new Symbol("53287","ADDRESS", 0xD027);
    m_constants["SPRITE_DATA"] = new Symbol("$0340","ADDRESS", 0x0340);
    m_constants["SID"] = new Symbol("54272","ADDRESS", 54272);

    m_constants["SIDFILE_1_INIT"] = new Symbol("","ADDRESS", 0);
    m_constants["SIDFILE_2_INIT"] = new Symbol("","ADDRESS", 0);
    m_constants["SIDFILE_1_PLAY"] = new Symbol("","ADDRESS", 0);
    m_constants["SIDFILE_2_PLAY"] = new Symbol("","ADDRESS", 0);

}

void SymbolTable::InitBuiltins()
{

    Define(new BuiltInTypeSymbol("INTEGER",""));
    Define(new BuiltInTypeSymbol("REAL",""));
    Define(new BuiltInTypeSymbol("BYTE",""));
    Define(new BuiltInTypeSymbol("STRING",""));
    Define(new BuiltInTypeSymbol("ARRAY",""));
    Define(new BuiltInTypeSymbol("INCBIN",""));
    Define(new BuiltInTypeSymbol("INCSID",""));

    Define(new Symbol("return",""));
    Define(new Symbol("sine", "address"));
    Define(new Symbol("joystickvalue", "address"));
}

