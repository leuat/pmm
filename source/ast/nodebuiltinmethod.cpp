#include "nodebuiltinmethod.h"


QString NodeBuiltinMethod::Build(Assembler *as) {
    if (m_procName.toLower()=="writeln") {
        if (m_params.count()!=2)
            ErrorHandler::e.Error("Writeln requires 2 parameters");
        as->Writeln();

        m_params[0]->Build(as);
        as->EndWriteln();
    }
    if (m_procName.toLower()=="poke") {
        if (m_params.count()!=2)
            ErrorHandler::e.Error("Poke requires 2 parameters");

        as->ClearTerm();
        QString varb = m_params[1]->Build(as);
        QString vara = m_params[0]->Build(as);
        as->ClearTerm();

        as->Poke(vara, varb);

    }

    if (m_procName.toLower()=="print") {
        QString s = "";
        if (m_params.count()!=4)
            ErrorHandler::e.Error("Print requires 4 parameters");

        as->StartPrint();
        m_params[0]->Build(as);
        m_params[0]->Build(as);
//        if (m_params[1]!=nullptr)
  //          s+=m_params[1]->Execute(symTab, level).toString();

    }
    return "";
}

PVar NodeBuiltinMethod::Execute(SymbolTable *symTab, uint lvl) {
    ErrorHandler::e.DebugLow("Calling Builtin",level);
    level = lvl+1;

    if (m_procName.toLower()=="writeln") {
        QString s = "";
        if (m_params[0]!=nullptr)
            s+=m_params[0]->Execute(symTab, level).toString();
        if (m_params[1]!=nullptr)
            s+=m_params[1]->Execute(symTab, level).toString();

        ErrorHandler::e.OutputText(s);
    }

    return PVar();

}
