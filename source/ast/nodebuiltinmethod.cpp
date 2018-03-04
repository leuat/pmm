#include "nodebuiltinmethod.h"


QMap<QString, bool> NodeBuiltinMethod::m_isInitialized;

QString NodeBuiltinMethod::Build(Assembler *as) {
    if (m_procName.toLower()=="writeln") {
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

    if (m_procName.toLower()=="and")
        BitOp(as,0);

    if (m_procName.toLower()=="or")
        BitOp(as,1);

    if (m_procName.toLower()=="rand")
        Rand(as);
    if (m_procName.toLower() == "scroll")
       Scroll(as);

    if (m_procName.toLower() == "incscreenx")
            IncScreenX(as);

    if (m_procName.toLower() == "initeightbitmul")
            InitEightBitMul(as);

    if (m_procName.toLower()=="fill")
        Fill(as);

    if (m_procName.toLower()=="initrandom")
        InitRandom(as);

    if (m_procName.toLower()=="initmoveto") {
        InitMoveto(as);
    }
    if (m_procName.toLower()=="initjoystick") {
        InitJoystick(as);
    }
    if (m_procName.toLower()=="joystick") {
        Joystick(as);
    }

    if (m_procName.toLower()=="initprintstring") {
        InitPrintString(as);
    }
    if (m_procName.toLower()=="printnumber") {
        PrintNumber(as);
    }

    if (m_procName.toLower()=="printstring") {
        PrintString(as);
    }

    /*    if (m_procName.toLower()=="definesinetable")
            InitSinusTable(as);
    */

    if (m_procName.toLower()=="initsinetable")
        InitSinusTable(as);

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
    QString lbl = as->NewLabel("memcpy");
    as->Asm("ldx #0");
    as->Label(lbl);
    LoadVar(as, 0, "x");
    SaveVar(as, 1, "x");
    as->Asm("inx");
    as->Term("cpx ");
    m_params[2]->Build(as);
    as->Term();
    as->Asm("bne " + lbl);

    as->PopLabel("memcpy");

}

void NodeBuiltinMethod::Rand(Assembler* as)
{
    VerifyInitialized("rand","InitRandom");
    LoadVar(as, 0);
    as->Asm("sta lowerRandom");
    LoadVar(as, 1);
    as->Asm("sta upperRandom");
    as->Asm("jsr callRandom");
    SaveVar(as,2);

}

void NodeBuiltinMethod::InitMoveto(Assembler *as)
{
    if (m_isInitialized["moveto"])
        return;

    QString lbl = as->NewLabel("moveto");
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

    as->PopLabel("moveto");
    m_isInitialized["moveto"]=true;

}

void NodeBuiltinMethod::InitEightBitMul(Assembler *as)
{
    if (m_isInitialized["eightbitmul"])
        return;

    m_isInitialized["eightbitmul"] = true;

    QString l = as->NewLabel("multiply_eightbit");
    as->Asm("jmp " + l);
    as->Label("multiplier	= $02 ; some zeropage adress");
    as->Label("multiply_eightbit");
    as->Asm("cpx #$00");
    as->Asm("beq mul_end");
    as->Asm("dex");
    as->Asm("stx mul_mod+1");
    as->Asm("lsr");
    as->Asm("sta multiplier");
    as->Asm("lda #$00");
    as->Asm("ldx #$08");
    as->Label("mul_loop");
    as->Asm("bcc mul_skip");
    as->Label("mul_mod");
    as->Asm("adc #$00");
    as->Label("mul_skip");
    as->Asm("ror");
    as->Asm("ror multiplier");
    as->Asm("dex");
    as->Asm("bne mul_loop");
    as->Asm("ldx multiplier");
    as->Asm("rts");
    as->Label("mul_end");
    as->Asm("txa");
    as->Asm("rts");
    as->Label(l);
    as->PopLabel("multiply_eightbit");
}

void NodeBuiltinMethod::InitPrintString(Assembler *as)
{
    if (m_isInitialized["initprintstring"])
        return;
    m_isInitialized["initprintstring"] = true;

    as->ClearTerm();
    as->Label("print_text dc \"HEISANN\",0");
    as->Asm("org print_text +#100");
    as->Label("printstring");
    as->Asm("ldy #0");
    as->Label("printstringloop");
    as->Asm("lda print_text,x");
    as->Asm("cmp #0");
    as->Asm("beq printstring_done");
    as->Asm("sec");
    as->Asm("sbc #64");
//    as->Asm("cmp #28");
//    as->Asm("bcs printstring_skip");
    as->Asm("sta (screenMemory),y");
 //   as->Label("printstring_skip");
    as->Asm("iny");
    as->Asm("inx");
    as->Asm("jmp printstringloop");
    as->Label("printstring_done");



}
void NodeBuiltinMethod::PrintNumber(Assembler *as)
{

    QString lbl= as->NewLabel("printnumber_call");
    as->Asm("ldx #0");

    as->ClearTerm();
    m_params[0]->Build(as);
    as->Term();

    as->Asm("tay");
    as->Asm("and #$0F");
    as->Asm("cmp #$0A");
    as->Asm("bcc printnumber_l1");
    as->Asm("sec");
    as->Asm("sbc #$39");
    as->Label("printnumber_l1");
    as->Asm("adc #$30 + #64");
    as->Asm("sta print_text,x");
    as->Asm("inx");
    as->Asm("tya");
    as->Asm("and #$F0");
    as->Asm("lsr");
    as->Asm("lsr ");
    as->Asm("lsr ");
    as->Asm("lsr ");

    as->Asm("cmp #$0A");
    as->Asm("bcc printnumber_l2");
    as->Asm("sec");
    as->Asm("sbc #$39");
    as->Label("printnumber_l2");

    as->Asm("adc #$30 + #64");
    as->Asm("sta print_text,x");
    as->Asm("inx");
    as->Asm("lda #0");
    as->Asm("sta print_text,x");

    as->Asm("ldx #0");
    as->Asm("jsr printstring");

    as->PopLabel("printnumber_call");
}

void NodeBuiltinMethod::PrintString(Assembler *as)
{
    QString lbl= as->NewLabel("printstring_call");

    as->Asm("ldx #0");
    as->Label(lbl);

    as->Term("lda ");
    m_params[0]->Build(as);
    as->Term(",x", true);
    as->Asm("sta print_text,x");
    as->Asm("inx");
    as->Asm("cmp #0");
    as->Asm("bne " + lbl);
    as->Term("");
    m_params[1]->Build(as);
    as->Term();
    as->Asm("tax");

    as->Asm("jsr printstring");

    as->PopLabel("printstring_call");

}


void NodeBuiltinMethod::MoveTo(Assembler *as)
{
    VerifyInitialized("moveto", "InitMoveto");
    LoadVar(as, 0);
    as->Asm("sta screen_x");
    LoadVar(as, 1);
    as->Asm("sta screen_y");
    LoadVar(as, 2);
    as->Asm("jsr SetScreenPosition");
}

void NodeBuiltinMethod::InitRandom(Assembler *as)
{
    if (m_isInitialized["rand"])
        return;
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
    as->Term("ldy ");
    m_params[1]->Build(as);
    as->Term();
    as->Asm("sta (screenMemory),y");
}

void NodeBuiltinMethod::Fill(Assembler *as)
{
    QString lbl = as->NewLabel("fill");
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
    as->PopLabel("fill");

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

void NodeBuiltinMethod::Joystick(Assembler *as)
{

}

void NodeBuiltinMethod::BitOp(Assembler *as, int type)
{
    as->ClearTerm();
    as->Term("lda ");
    m_params[0]->Build(as);
    as->Term();
    if (type==0)
        as->Term("and ");
    if (type==1)
        as->Term("ora ");
    m_params[1]->Build(as);
    as->Term();
    as->Term("sta ");
    m_params[0]->Build(as);
    as->Term();
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

void NodeBuiltinMethod::InitSinusTable(Assembler *as)
{
    if (m_isInitialized["sinetab"])
        return;
    as->Asm("jmp initsin_continue");
    as->Label("sine .byte 0 ");
    as->Asm("org sine +#255");

    as->Label("value .word 0");
    as->Label("delta .word 0");
    as->Label("initsin_continue");


    as->Asm("ldy #$3f");
    as->Asm("ldx #$00");
    as->Label("initsin_a");
    as->Asm("lda value");
    as->Asm("clc");
    as->Asm("adc delta");
    as->Asm("sta value");
    as->Asm("lda value+1");
    as->Asm("adc delta+1");
    as->Asm("sta value+1");

    as->Asm("sta sine+$c0,x");
    as->Asm("sta sine+$80,y");
    as->Asm("eor #$ff");
    as->Asm("sta sine+$40,x");
    as->Asm("sta sine+$00,y");

    as->Asm("lda delta");
    as->Asm("adc #$10   ; this value adds up to the proper amplitude");

    as->Asm("sta delta");
    as->Asm("bcc initsin_b");
    as->Asm("inc delta+1");
    as->Label("initsin_b");

    as->Asm("inx");
    as->Asm("dey");
    as->Asm("bpl initsin_a");


    m_isInitialized["sinetab"]=true;


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

void NodeBuiltinMethod::VerifyInitialized(QString method, QString initmethod)
{
    if (!m_isInitialized[method])
        ErrorHandler::e.Error("Please declare "+ initmethod+"() before using " + method+"();");

}

void NodeBuiltinMethod::InitJoystick(Assembler *as)
{
    /*start    lda $02
             cmp $dc00
             beq start      ; loop until the joystick register changes.

             lda $dc00      ; store new value in memory location 2.
             sta $02

    up       lda #%00000001 ; mask joystick up movement
             bit $dc00      ; bitwise AND with address 56320
             bne down       ; zero flag is not set -> skip to down
             inc $d020      ; border color + 1

    down     lda #%00000010 ; mask joystick down movement
             bit $dc00      ; bitwise AND with address 56320
             bne left       ; zero flag is not set -> skip to left
             dec $d020      ; border color- 1

    left     lda #%00000100 ; mask joystick left movement
             bit $dc00      ; bitwise AND with address 56320
             bne right      ; zero flag is not set -> skip to right
             inc $d021      ; background color + 1

    right    lda #%00001000 ; mask joystick right movement
             bit $dc00      ; bitwise AND with address 56320
             bne buton      ; zero flag is not set -> skip to buton
             dec $d021      ; background color - 1

    buton    lda #%00010000 ; mask joystick button push
             bit $dc00      ; bitwise AND with address 56320
             bne start      ; button not pressed -> enter loop again
             rts            ; back to basic

             */
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
