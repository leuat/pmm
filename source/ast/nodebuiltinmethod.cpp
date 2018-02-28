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

    if (m_procName.toLower()=="memcpy") {
        //as->ClearTerm();
        as->m_labelStack["memcpy"].push();
        QString lbl = as->getLabel("memcpy");
        as->Asm("ldx #0");
        as->Label(lbl);
        as->Term("lda ");
        m_params[0]->Build(as);
        as->Term(",x",true);
        as->Term("sta ");
        m_params[1]->Build(as);
        as->Term(",x",true);
        as->Asm("inx");
        as->Term("cpx ");
        m_params[2]->Build(as);
        as->Term();
        as->Asm("bne " + lbl);

        as->m_labelStack["memcpy"].pop();

    }
    if (m_procName.toLower()=="rand") {
        as->Term("lda ");
        m_params[0]->Build(as);
        as->Term();
        as->Asm("sta lowerRandom");
        as->Term("lda ");
        m_params[1]->Build(as);
        as->Term();
        as->Asm("sta upperRandom");
        as->Asm("jsr callRandom");
        as->Term("sta ");
        m_params[2]->Build(as);
        as->Term();

    }
    if (m_procName.toLower()=="initrandom") {
        as->Asm ("; init random");
        as->Asm("LDA #$FF");
        as->Asm("STA $D40E");
        as->Asm("STA $D40F");
        as->Asm("LDA #$80");
        as->Asm("STA $D412");
        as->Asm("jmp continueRandom");
        as->DeclareVariable("upperRandom", "byte");
        as->DeclareVariable("lowerRandom", "byte");
        as->Label("callRandom");
        as->Asm("lda upperRandom");
        as->Asm("sbc lowerRandom");
        as->Asm("sta upperRandom");
        as->Label("RandomLoop");
        as->Asm("LDA $D41B ; get random value");
        as->Asm("CMP upperRandom  ; compare to");
        as->Asm("BCS RandomLoop   ; branch if value >");
        as->Asm("ADC lowerRandom");
        as->Asm("RTS");
        as->Label("continueRandom");
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
