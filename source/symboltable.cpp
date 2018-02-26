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
    isInitialized = true;
}

void SymbolTable::InitBuiltins()
{

    Define(new BuiltInTypeSymbol("INTEGER",""));
    Define(new BuiltInTypeSymbol("REAL",""));
    Define(new BuiltInTypeSymbol("STRING",""));

    Define(new Symbol("return",""));
}

