#include "symboltable.h"

SymbolTable::SymbolTable()
{
    InitBuiltins();
}

void SymbolTable::InitBuiltins()
{
    Define(new BuiltInTypeSymbol("INTEGER",""));
    Define(new BuiltInTypeSymbol("REAL",""));
    Define(new BuiltInTypeSymbol("STRING",""));
}
