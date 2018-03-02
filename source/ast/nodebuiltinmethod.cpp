#include "nodebuiltinmethod.h"


QMap<QString, bool> NodeBuiltinMethod::m_isInitialized;

QString NodeBuiltinMethod::Build(Assembler *as) {
    if (m_procName.toLower()=="writeln") {
        if (m_params.count()!=2)
            ErrorHandler::e.Error("Writeln requires 2 parameters");
        as->Writeln();

        m_params[0]->Build(as);
        as->EndWriteln();
    }
    if (m_procName.toLower()=="poke")
        Poke(as);

    if (m_procName.toLower()=="peek")
        Peek(as);

    if (m_procName.toLower()=="memcpy")
        MemCpy(as);

    if (m_procName.toLower()=="rand")
        Rand(as);
    if (m_procName.toLower() == "scroll")
       Scroll(as);
    if (m_procName.toLower() == "incscreenx")
            IncScreenX(as);

    if (m_procName.toLower()=="fill")
        Fill(as);

    if (m_procName.toLower()=="initrandom")
        InitRandom(as);

    if (m_procName.toLower()=="moveto")
        MoveTo(as);

    if (m_procName.toLower()=="pokescreen") {
        PokeScreen(as, 0);
    }

    if (m_procName.toLower()=="printchar") {
        as->ClearTerm();
        m_params[1]->Build(as);
        int x = as->m_term.toInt();
        as->ClearTerm();
        m_params[2]->Build(as);
        int y = as->m_term.toInt();
        as->ClearTerm();
        int pos = y*40 +x;



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

void NodeBuiltinMethod::Poke(Assembler* as)
{
    LoadVar(as,1);
    as->Asm("tax");
    LoadVar(as,2);
    SaveVar(as,0,"x");

}

void NodeBuiltinMethod::Peek(Assembler* as)
{
    LoadVar(as, 1);
    as->Asm("tax");
    LoadVar(as,0,"x");
    SaveVar(as,2);

}

void NodeBuiltinMethod::MemCpy(Assembler* as)
{
    //as->ClearTerm();
    as->m_labelStack["memcpy"].push();
    QString lbl = as->getLabel("memcpy");
    as->Asm("ldx #0");
    as->Label(lbl);
    LoadVar(as, 0, "x");
    SaveVar(as, 1, "x");
    as->Asm("inx");
    as->Term("cpx ");
    m_params[2]->Build(as);
    as->Term();
    as->Asm("bne " + lbl);

    as->m_labelStack["memcpy"].pop();

}

void NodeBuiltinMethod::Rand(Assembler* as)
{
    if (!m_isInitialized["rand"])
        ErrorHandler::e.Error("Please decaler InitRandom() before using Rand();");
    LoadVar(as, 0);
    as->Asm("sta lowerRandom");
    LoadVar(as, 1);
    as->Asm("sta upperRandom");
    as->Asm("jsr callRandom");
    SaveVar(as,2);

}

void NodeBuiltinMethod::InitMoveto(Assembler *as)
{
    as->m_labelStack["moveto"].push();
    QString lbl = as->getLabel("moveto");
    as->Asm("jmp " + lbl);
    as->Label("screenMemory = $fb ");
    as->Label("screen_x .byte 0 ");
    as->Label("screen_y .byte 0 ");

    as->Label("SetScreenPosition");
    //as->Asm("lda #4");
    as->Asm("sta screenMemory+1");
    as->Asm("lda #0");
    as->Asm("sta screenMemory");
    as->Asm("ldy screen_y");
    as->Asm("cpy #0");
    as->Asm("beq sydone");
    as->Label("syloop");
    as->Asm("clc");
    as->Asm("adc #40");
    as->Asm("bcc sskip");
    as->Asm("inc screenMemory+1");
    as->Label("sskip");
    as->Asm("dey");
    as->Asm("cpy #$00");
    as->Asm("bne syloop");
    as->Label("sydone");
    as->Asm("ldx screen_x");
    as->Asm("cpx #0");
    as->Asm("beq sxdone");
    as->Asm("clc");
    as->Asm("adc screen_x");
    as->Asm("bcc sxdone");
    as->Asm("inc screenMemory+1");
    as->Label("sxdone");
    as->Asm("sta screenMemory");
    as->Asm("rts");
    as->Label(lbl);

    as->m_labelStack["moveto"].pop();

}

void NodeBuiltinMethod::MoveTo(Assembler *as)
{
    if (!m_isInitialized["moveto"]) {
        m_isInitialized["moveto"]=true;
        InitMoveto(as);
    }
    LoadVar(as, 0);
    as->Asm("sta screen_x");
    LoadVar(as, 1);
    as->Asm("sta screen_y");
    LoadVar(as, 2);
    as->Asm("jsr SetScreenPosition");
}

void NodeBuiltinMethod::InitRandom(Assembler *as)
{
    m_isInitialized["rand"] = true;
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

void NodeBuiltinMethod::PokeScreen(Assembler *as, int shift)
{

    LoadVar(as, 0);
    as->Asm("ldy #0");
    as->Asm("sta (screenMemory),y");
}

void NodeBuiltinMethod::Fill(Assembler *as)
{
    as->m_labelStack["fill"].push();
    QString lbl = as->getLabel("fill");
    LoadVar(as,1);
    as->Asm("ldx #0");
    as->Label(lbl);
    as->Term("sta ");
    m_params[0]->Build(as);
    as->Term(",x", true);
    as->Asm("inx");
    as->Term("cpx ");
    m_params[2]->Build(as);
    as->Term();
    as->Asm("bne "+lbl);

}

void NodeBuiltinMethod::Scroll(Assembler *as)
{
    LoadVar(as, 0);
   // as->Asm("dec $d019");
    as->Asm("lda $d016  ");
    as->Asm("and #$F8");
    as->Asm("clc");
    as->Term("adc ");
    m_params[0]->Build(as);
    as->Term();
    as->Asm("sta $d016");

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

void NodeBuiltinMethod::IncScreenX(Assembler *as)
{
    as->m_labelStack["incscreenx"].push();
    QString lbl = as->getLabel("incscreenx");

    as->Term("lda ");
    m_params[0]->Build(as);
    as->Term();
    as->Asm("sta screen_x");
    as->Asm("lda screenMemory");
    as->Asm("cpx #0");
    as->Asm("beq " + lbl);
    as->Asm("clc");
    as->Asm("adc screen_x");
    as->Asm("bcc " + lbl);
    as->Asm("inc screenMemory+1");
    as->Label(lbl);
    as->Asm("sta screenMemory");


    as->m_labelStack["incscreenx"].pop();

}

void NodeBuiltinMethod::LoadVar(Assembler *as, int paramNo, QString reg)
{
    as->ClearTerm();
    as->Term("lda ");
    m_params[paramNo]->Build(as);
    if (reg!="")
        reg = "," + reg;
    as->Term(reg, true);

}

void NodeBuiltinMethod::LoadVar(Assembler *as, int paramNo)
{
    LoadVar(as, paramNo, "");
}

void NodeBuiltinMethod::SaveVar(Assembler *as, int paramNo)
{
    SaveVar(as, paramNo, "");
}

void NodeBuiltinMethod::SaveVar(Assembler *as, int paramNo, QString reg)
{
    as->ClearTerm();
    as->Term("sta ");
    m_params[paramNo]->Build(as);
    if (reg!="")
        reg = "," + reg;
    as->Term(reg, true);

}
