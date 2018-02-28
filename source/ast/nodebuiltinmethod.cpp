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

        as->ClearTerm();
        as->Term("lda ");
        m_params[1]->Build(as);
        as->Term();
        as->Asm("tax");
        as->Term("lda ");
        m_params[2]->Build(as);
        as->Term();
        as->Term("sta ");
        m_params[0]->Build(as);
        as->Term(",x", true);

    }
    if (m_procName.toLower()=="peek") {

        as->ClearTerm();
        as->Term("lda ");
        m_params[1]->Build(as);
        as->Term();
        as->Asm("tax");
        as->Term("lda ");
        m_params[0]->Build(as);
        as->Term(",x", true);
        as->Term("sta ");
        m_params[2]->Build(as);
        as->Term();
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
