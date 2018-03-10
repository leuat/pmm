#include "nodebuiltinmethod.h"
#include "nodenumber.h"
#include "nodevar.h"
#include "nodestring.h"
#include "nodeprocedure.h"

QMap<QString, bool> NodeBuiltinMethod::m_isInitialized;

QString NodeBuiltinMethod::Build(Assembler *as) {
    if (m_procName.toLower()=="writeln") {
        as->Writeln();

        m_params[0]->Build(as);
        as->EndWriteln();
    }

    if (m_procName.toLower()=="kernelinterrupt")
        as->Asm("jmp $ea81        ; return to kernel interrupt routine");

    if (m_procName.toLower()=="loop")
        as->Asm("jmp * ; loop like (¤/%");

    if (m_procName.toLower()=="call") {
        Call(as);
    }
    if (m_procName.toLower() == "setspriteloc")
        SetSpriteLoc(as);

    if (m_procName.toLower()=="initsid") {
        InitSid(as);
    }

    if (m_procName.toLower()=="poke")
        Poke(as);

    if (m_procName.toLower()=="swap")
        Swap(as);

    if (m_procName.toLower()=="clearscreen")
        ClearScreen(as);

    if (m_procName.toLower()=="peek")
        Peek(as);

    if (m_procName.toLower() == "copyimagecolordata")
        CopyImageColorData(as);

    if (m_procName.toLower()=="waitforraster")
        WaitForRaster(as);

    if (m_procName.toLower() =="setmulticolormode") {
        as->Comment("Multicolor mode");
        as->Asm("lda #$18");
        as->Asm("sta $d016");

    }

    if (m_procName.toLower() =="settextmode") {
        as->Comment("Regular text mode ");
        as->Asm("lda $D011");
        as->Asm("lda #%11011111");
        as->Asm("sta $D011");
    }
    if (m_procName.toLower() =="setbank") {
        SetBank(as);
    }
    if (m_procName.toLower() =="setbitmapmode") {
        as->Comment("Bitmap mode ");
        as->Asm("lda #$3b");
        as->Asm("sta $d011");
    }

    if (m_procName.toLower() =="regularcolormode") {
        as->Comment("Regularcolor mode");
        as->Asm("lda #$4");
        as->Asm("sta $d016");

    }

    if (m_procName.toLower()=="waitnoraster")
        WaitNoRasterLines(as);

    if (m_procName.toLower()=="memcpy")
        MemCpy(as);

    if (m_procName.toLower()=="memcpylarge")
        MemCpyLarge(as);


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

    if (m_procName.toLower() == "spritepos")
            SetSpritePos(as);

    if (m_procName.toLower() == "initeightbitmul")
            InitEightBitMul(as);

    if (m_procName.toLower()=="fill")
        Fill(as);

    if (m_procName.toLower()=="initrandom")
        InitRandom(as);

    if (m_procName.toLower()=="enableinterrupts")
        EnableInterrupts(as);

    if (m_procName.toLower()=="initmoveto") {
        InitMoveto(as);
    }
    if (m_procName.toLower()=="initjoystick") {
        InitJoystick(as);
    }
    if (m_procName.toLower()=="joystick") {
        Joystick(as);
    }
    if (m_procName.toLower()=="playsound") {
        PlaySound(as);
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
    if (m_procName.toLower()=="pokescreencolor") {
        PokeScreenColor(as, 0);
    }
    if (m_procName.toLower()=="disableinterrupts")
        DisableInterrupts(as);

    if (m_procName.toLower()=="rasterirq")
        RasterIRQ(as);

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
    // Optimization : if parameter 1 is zero, drop the ldx / tax
    as->Comment("Poke");
    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[1]);
    if (num!=nullptr!=0 && num->m_val==0) {
        as->Comment("Optimization: shift is zero");
        LoadVar(as,2);
        SaveVar(as,0);
        return;
    }
    // Optimization #2 : if parameter is num AND parameter 2 is num, just add
    NodeNumber* num2 = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num2!=nullptr!=0 && num!=nullptr) {
        as->Comment("Optimization: both storage and shift are constant");
        LoadVar(as,2);
        //SaveVar(as,0);
        as->Asm("sta $" + QString::number((int)(num2->m_val + num->m_val),16));
        return;
    }

    LoadVar(as,1);
    as->Asm("tax");
    LoadVar(as,2);
    SaveVar(as,0,"x");

}

void NodeBuiltinMethod::Peek(Assembler* as)
{
    as->Comment("Peek");
    LoadVar(as, 1);
    as->Asm("tax");
    LoadVar(as,0,"x");
    SaveVar(as,2);

}

void NodeBuiltinMethod::MemCpy(Assembler* as)
{
    //as->ClearTerm();
    NodeVar* var = (NodeVar*)dynamic_cast<NodeVar*>(m_params[0]);
    if (var==nullptr) {
        ErrorHandler::e.Error("First parameter must be variable", m_op.m_lineNumber);
    }
    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[1]);
    if (num==nullptr) {
        ErrorHandler::e.Error("Second parameter must be pure numeric", m_op.m_lineNumber);
    }


    as->Comment("memcpy");
    QString lbl = as->NewLabel("memcpy");
    as->Asm("ldx #0");
    as->Label(lbl);
    //LoadVar(as, 0, "x");
    as->Asm("lda " + var->value + " + #" + num->HexValue() + ",x");
    SaveVar(as, 2, "x");
    as->Asm("inx");
    as->Term("cpx ");
    m_params[3]->Build(as);
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
    as->Label("multiplier .byte 0");
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
    as->Label("print_text = $fd");
    as->Label("print_number_text .dc \"    \",0");
    as->Label("printstring");
    as->Asm("ldy #0");
    as->Label("printstringloop");
    as->Asm("lda (print_text),y");
    as->Asm("cmp #0");
    as->Asm("beq printstring_done");
    as->Asm("cmp #64");
    as->Asm("bcc printstring_skip");

    as->Asm("sec");
    as->Asm("sbc #64");
//    as->Asm("cmp #28");
//    as->Asm("bcs printstring_skip");
    as->Label("printstring_skip");
    as->Asm("sta (screenMemory),y");
    as->Asm("iny");
    as->Asm("dex");
    as->Asm("cpx #0");
    as->Asm("beq printstring_done");

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
    as->Asm("sta print_number_text,x");
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
    as->Asm("sta print_number_text,x");
    as->Asm("inx");
    as->Asm("lda #0");
    as->Asm("sta print_number_text,x");

    as->Asm("ldx #0");

    as->Asm("lda #<print_number_text");
    as->Asm("ldy #>print_number_text");
    as->Asm("sta print_text+0");
    as->Asm("sty print_text+1");


    as->Asm("jsr printstring");

    as->PopLabel("printnumber_call");
}

void NodeBuiltinMethod::PrintString(Assembler *as)
{
    QString lbl= as->NewLabel("printstring_call");
    QString lbl2= as->NewLabel("printstring_text");
    NodeVar* var = (NodeVar*)dynamic_cast<NodeVar*>(m_params[0]);
    NodeString* str = (NodeString*)dynamic_cast<NodeString*>(m_params[0]);

    if (str==nullptr && var==nullptr)
        ErrorHandler::e.Error("PrintString must take variable or string constant");

    QString varName = "";
    if (var!=nullptr)
        varName = var->value;


    if (str!=nullptr) {
        as->Asm("jmp " + lbl);
        varName = lbl2;
        as->Label(varName + "\t.dc \"" + str->m_val+"\",0");
    }

    if (str!=nullptr)
        as->Label(lbl);
    as->Asm("clc");
    as->Comment("TEST");
    as->Asm("lda #<" +varName);
    as->Term("adc ");
    m_params[1]->Build(as);
    as->Term();
    as->Asm("ldy #>" +varName);
    as->Asm("sta print_text+0");
    as->Asm("sty print_text+1");


//    LoadVar(as, 1);
 //   as->Asm("tay");
    LoadVar(as, 2);
    as->Asm("tax");
    as->Asm("jsr printstring");

    as->PopLabel("printstring_call");
    as->PopLabel("printstring_text");

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

void NodeBuiltinMethod::PokeScreenColor(Assembler *as, int hiAddress)
{
    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[3]);
    if (num==nullptr)
        ErrorHandler::e.Error("PokeScreenColor: last parameter required to be pure constant number");



    LoadVar(as, 0);
    as->Term("ldy ");
    m_params[2]->Build(as);
    as->Term();
    as->Asm("sta (screenMemory),y");
    for (int i=0;i<num->m_val-1;i++) {
        as->Asm("iny");
        as->Asm("sta (screenMemory),y");
    }

    as->Asm("lda screenMemory+1");
    as->Asm("tax");
    as->Asm("adc #$D4");
    as->Asm("sta screenMemory+1");
    //LoadVar(as, 1);
   as->Asm("lda #$F2");
    as->Asm("sta (screenMemory),y");
    for (int i=0;i<num->m_val-1;i++) {
        as->Asm("dey");
        as->Asm("sta (screenMemory),y");
    }

    as->Asm("txa");
    as->Asm("sta screenMemory+1");
}

void NodeBuiltinMethod::SetSpritePos(Assembler *as)
{

    QString lbl = as->NewLabel("spritepos");
    QString lbl2 = as->NewLabel("spriteposcontinue");
    as->Comment("Setting sprite position");
    LoadVar(as, 2);

    as->Asm("tay");

    LoadVar(as, 0);
    as->Asm("sta $D000,y");
    m_params[0]->Build(as);
    as->Term("+1",true);
    as->Asm("cmp #0");
    as->Asm("beq " + lbl);


    as->Asm("lda $D010");
    as->Term("ora ");
    m_params[3]->Build(as);
    as->Term();
    as->Asm("sta $D010");
    as->Asm("jmp "+lbl2);
    as->Label(lbl);

    as->Asm("lda $D010");
    as->Term("and ");
    m_params[4]->Build(as);
    as->Term();
    as->Asm("sta $D010");

    as->Label(lbl2);

    as->Asm("iny");
    LoadVar(as, 1);
    as->Asm("sta $D000,y");

    as->PopLabel("spritepos");
    as->PopLabel("spriteposcontinue");
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
    as->Asm("jsr callJoystick");
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

void NodeBuiltinMethod::PlaySound(Assembler *as)
{
//    LoadVar(as, 0);
    NodeNumber *num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num==nullptr) {
        ErrorHandler::e.Error("First value must be constant - addresses chip");
    }
    QString add = " + " + num->HexValue();

    int SID = 54272;
    LoadVar(as, 1);
    as->Asm("sta 54272 +24" );
    LoadVar(as, 2);
    as->Asm("sta 54272 +1" + add);
    LoadVar(as, 3);
    as->Asm("sta 54272 +5"+add);
    LoadVar(as, 4);
    as->Asm("sta 54272 +6"+add);
    LoadVar(as, 5);
    as->Asm("sta 54272 +$4"+add);
    LoadVar(as, 6);
    as->Asm("sta 54272 +$4"+add);

    //    if (num->m_val==1) {
 //       as->
 //   }

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

void NodeBuiltinMethod::Call(Assembler *as)
{
    NodeNumber* num= (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num!=nullptr) {
        as->Term("jsr ");
        num->Build(as);
        as->Term();
        return;
    }
    ErrorHandler::e.Error("Call currently only supports constant values", m_op.m_lineNumber);
/*    NodeVar* num= (NodeVar*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num!=nullptr) {
        as->Asm("jsr $" + QString::number(num->m_val,16));
        return;
    }
*/
}

void NodeBuiltinMethod::InitSid(Assembler *as)
{
    NodeNumber* num= (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num!=nullptr) {
        as->Comment("initsid");
        as->Asm("lda #0");
        as->Asm("tax");
        as->Asm("tay");
        as->Term("jsr ");
        num->Build(as);
        as->Term();

        return;
    }
    ErrorHandler::e.Error("InitSid currently only supports constant values", m_op.m_lineNumber);

}

void NodeBuiltinMethod::DisableInterrupts(Assembler *as)
{
    as->Comment("Disable interrupts");
    as->Asm("sei ");
/*    as->Asm("ldy #$7f    ; $7f = %01111111");
    as->Asm("sta $dc0d");
    as->Asm("sta $dd0d");
    as->Asm("lda #$01");
    as->Asm("sta $d01a");
*/

    as->Asm("ldy #$7f    ; $7f = %01111111");
    as->Asm("sty $dc0d   ; Turn off CIAs Timer interrupts");
    as->Asm("sty $dd0d   ; Turn off CIAs Timer interrupts");
    as->Asm("lda $dc0d   ; cancel all CIA-IRQs in queue/unprocessed");
    as->Asm("lda $dd0d   ; cancel all CIA-IRQs in queue/unprocessed");

    as->Asm("");
}

void NodeBuiltinMethod::RasterIRQ(Assembler *as)
{
    NodeProcedure* addr = (NodeProcedure*)dynamic_cast<NodeProcedure*>(m_params[0]);
    if (addr==nullptr)
        ErrorHandler::e.Error("First parameter must be interrupt procedure!", m_op.m_lineNumber);

    QString name = addr->m_procedure->m_procName;

    as->Comment("Set raster interrupt pointing to : " +name);
    as->Asm("lda #$01    ; Set Interrupt Request Mask...");
    as->Asm("sta $d01a   ; ...we want IRQ by Rasterbeam");
    as->Asm("lda #<" + name);
    as->Asm("ldx #>"+ name);
    as->Asm("sta $314    ; store in $314/$315");
    as->Asm("stx $315");

    LoadVar(as,1);
    as->Asm("sta $d012");


}

void NodeBuiltinMethod::ClearScreen(Assembler *as)
{
    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[1]);
    if (num==nullptr)
        ErrorHandler::e.Error("ClearScreen: second parameter must be constant number", m_op.m_lineNumber);


    QString lbl = as->NewLabel("clearloop");
    QString shift = "$" + QString::number((int)num->m_val, 16);
    as->Comment("Clear screen with offset");
    as->Asm("lda #$00");
    as->Asm("tax");
    LoadVar(as, 0);
    as->Label(lbl);
    as->Asm("sta $0000+"+shift+",x");
    as->Asm("sta $0100+"+shift+",x");
    as->Asm("sta $0200+"+shift+",x");
    as->Asm("sta $0300+"+shift+",x");
    as->Asm("dex");
    as->Asm("bne "+lbl);
    as->PopLabel("clearloop");
}

void NodeBuiltinMethod::WaitNoRasterLines(Assembler *as)
{
   /* QString var = "";
    QString lbl = as->NewLabel("waitnoraster");
    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num!=nullptr)
            var = "#" + num->HexValue();
    NodeVar* nvar = (NodeVar*)dynamic_cast<NodeVar*>(m_params[0]);
    if (nvar!=nullptr)
            var = nvar->value;

    if (var=="")
        ErrorHandler::e.Error("WaitNoRasterLines: parameter must be either constant or variable, not expression", m_op.m_lineNumber);

*/
    as->Comment("Wait for no of raster lines");
  //  as->Label(lbl);
    LoadVar(as, 0);
    as->Asm("clc ");
    as->Asm("adc $d012");
    //as->Asm("adc " + var);
    as->Asm("cmp $d012");
    as->Asm("bne *-3" );


//    as->PopLabel("waitnoraster");
}




void NodeBuiltinMethod::WaitForRaster(Assembler *as)
{
    as->Comment("wait for raster");
    LoadVar(as, 0,"", "ldx ");
//    as->Asm("lda $d012 ; raster line pos");
//    as->Asm("clc ; clear carry ");
 //   as->Label("lblTest");
    as->Asm("cpx $d012");
    as->Asm("bne *-3");

}

void NodeBuiltinMethod::SetSpriteLoc(Assembler *as)
{
    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[1]);
    if (num==nullptr)
        ErrorHandler::e.Error("SetSpriteLoc parameter 1 must be constant");

    NodeNumber* num2 = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[0]);
    if (num2==nullptr)
        ErrorHandler::e.Error("SetSpriteLoc parameter 0 must be constant");

    as->Comment("Set sprite location");
    LoadVar(as,0);
    as->Asm("tax");
    LoadVar(as,1);
//    SaveVar(as,0,"x");
    as->Asm("sta $07f8,x");

    int newLoc = 64*num->m_val;
    QString c = "SPRITE_LOC" +QString::number((int)num2->m_val+1);
    qDebug() << c;
    as->m_symTab->m_constants[c]->m_value->m_fVal = newLoc;
    as->m_symTab->m_constants[c]->m_value->m_strVal = "$" + QString::number((int)(newLoc),16);

}

void NodeBuiltinMethod::Swap(Assembler *as)
{
    NodeVar* vars[2];
    for (int i=0;i<2;i++) {
        NodeVar* var = (NodeVar*)dynamic_cast<NodeVar*>(m_params[i]);
        if (var==nullptr)
            ErrorHandler::e.Error("Swap error: both parameters must be variables");
        vars[i]=var;
    }
    as->Comment("Swap variables");
//    as->Asm("lda " + vars[0]->value);
    LoadVar(as, 0);
    as->Asm("tay ");
    LoadVar(as, 1);
//    SaveVar(as, 0);
    vars[0]->StoreVariable(as);
    LoadVar(as, 0);
    as->Asm("tya");
    vars[1]->StoreVariable(as);
    //as->Asm("sta " + vars[1]->value+ ",x");


}

void NodeBuiltinMethod::MemCpyLarge(Assembler *as)
{
    /*as->Comment("Memory copy large > 255 bytes");

    NodeVar* var = (NodeVar*)dynamic_cast<NodeVar*>(m_params[0]);
    if (var==nullptr)
        ErrorHandler::e.Error("MemCpyLarge parameter 0 must be Variable location");


    NodeNumber* num = (NodeNumber*)dynamic_cast<NodeNumber*>(m_params[3]);
    if (num==nullptr)
        ErrorHandler::e.Error("MemCpyLarge parameter 4 must be constant");


    QString defs = as->NewLabel("memcpy_defs");
    QString counter = as->NewLabel("memcpy_counter");
    QString carry = as->NewLabel("memcpy_carry");

    as->Asm("lda <"+var->value);
    as->Asm("ldy >"+var->value);
    as->Asm("sta print_text+0");
    as->Asm("sty print_text+1");

    as->Asm("lda <"+var->value);
    as->Asm("ldy >"+var->value);
    as->Asm("sta print_text+0");
    as->Asm("sty print_text+1");


    as->Asm("jmp " + defs);
    as->Label(counter + "\t dc.w\t" + num->HexValue());
    as->Label(defs);
    as->




    as->PopLabel("memcpy_defs");
    as->PopLabel("memcpy_counter");
    as->PopLabel("memcpy_carry");
*/
/*    as->Comment("memcpy");
    QString lbl = as->NewLabel("memcpy");
    as->Asm("ldx #0");
    as->Label(lbl);
    //LoadVar(as, 0, "x");
    as->Asm("lda " + var->value + " + #" + num->HexValue() + ",x");
    SaveVar(as, 2, "x");
    as->Asm("inx");
    as->Term("cpx ");
    m_params[3]->Build(as);
    as->Term();
    as->Asm("bne " + lbl);
  */
}

void NodeBuiltinMethod::SetBank(Assembler *as)
{
    as->Comment("Set bank");
    as->Asm("lda $dd00");
    as->Asm("and #$fc");
    as->Term("ora ");
    m_params[0]->Build(as);
    as->Term();
    as->Asm("sta $dd00");
}

void NodeBuiltinMethod::CopyImageColorData(Assembler *as)
{
    NodeVar* var = dynamic_cast<NodeVar*>(m_params[0]);
    if (var==nullptr)
        ErrorHandler::e.Error("CopyImageColorData : parameter 0 must be a variable!");

    NodeNumber * bank = dynamic_cast<NodeNumber*>(m_params[1]);
    if (bank==nullptr)
        ErrorHandler::e.Error("CopyImageColorData : parameter 1 must be a constant number!");


    QString addBank="";
    if (bank->m_val==1)
        addBank="$4000";
    if (bank->m_val==2)
        addBank="$8000";
    if (bank->m_val==3)
        addBank="$c000";

    QString varName = var->value;
    QString lbl = as->NewLabel("copyimageloop");


    as->Comment("Copy image color data");
    as->Asm("lda "+varName);
    as->Asm("sta $d020 ; background");
    as->Asm("lda "+varName+"+1");
    as->Asm("sta $d021; foreground");
    as->Asm("ldx #$00");
    as->Label(lbl);
    as->Asm("lda "+varName+"+2,x");
    as->Asm("sta $0400 +"+addBank+",x");
    as->Asm("lda "+varName+" + $102,x");
    as->Asm("sta $0500+"+addBank+",x");
    as->Asm("lda "+varName+" + $202,x");
    as->Asm("sta $0600+"+addBank+",x");
    as->Asm("lda "+varName+" + $302,x");
    as->Asm("sta $0700+"+addBank+",x");

    as->Comment("color #2");
    as->Asm("lda "+varName+"+1002,x");
    as->Asm("sta $d800,x");
    as->Asm("lda "+varName+"+1002+ $100,x");
    as->Asm("sta $d900,x");
    as->Asm("lda "+varName+"+1002+ $200,x");
    as->Asm("sta $da00,x");
    as->Asm("lda "+varName+"+1002+ $300,x");
    as->Asm("sta $db00,x");

    as->Asm("inx");
    as->Asm("bne " + lbl);

    as->PopLabel("copyimageloop");

}

void NodeBuiltinMethod::EnableInterrupts(Assembler* as) {
  //  as->Asm("lda $dc0d");
  //  as->Asm("lda $dd0d");
//    as->Asm("asl $d019");

    as->Asm("lda $d011   ; Bit#0 of $d011 is basically...");
    as->Asm("and #$7f    ; ...the 9th Bit for $d012");
    as->Asm("sta $d011   ; we need to make sure it is set to zero ");

    as->Asm("cli");
}

void NodeBuiltinMethod::SaveVar(Assembler *as, int paramNo, QString reg, QString extra)
{
    as->ClearTerm();
    if (extra=="")
        as->Term("sta ");
    else
        as->Term(extra);
    m_params[paramNo]->Build(as);
    if (reg!="")
        reg = "," + reg;
    as->Term(reg, true);

}


void NodeBuiltinMethod::LoadVar(Assembler *as, int paramNo, QString reg, QString lda)
{
    as->ClearTerm();
    if (lda=="")
        as->Term("lda ");
    else
        as->Term(lda);
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

    as->Asm("jmp callJoystick");
    as->Label("joystickup .byte 0");
    as->Label("joystickdown .byte 0");
    as->Label("joystickleft .byte 0");
    as->Label("joystickright .byte 0");
    as->Label("joystickbutton .byte 0");
    as->Label("callJoystick");
/*

    as->Asm("lda $dc00 ;read joystick port 2");
    as->Asm("lsr       ;get switch bits");
    as->Asm("ror joystickup   ;switch_history = switch_history/2 + 128*current_switch_state");
    as->Asm("lsr       ;update the other switches' history the same way");
    as->Asm("ror joystickdown");
    as->Asm("lsr");
    as->Asm("ror joystickleft");
    as->Asm("lsr");
    as->Asm("ror joystickright");
    as->Asm("lsr");
    as->Asm("ror joystickbutton");
//    as->Asm("rts*/

/*    as->Asm("lda joystickvalue");
    as->Asm("cmp $dc00");
    as->Asm("beq callJoystick_end");
    as->Asm("lda  $dc00      ; store new value in memory location 2.");
    as->Asm("sta joystickvalue");
*/

    as->Asm("lda #0");
    as->Asm("sta joystickup");
    as->Asm("sta joystickdown");
    as->Asm("sta joystickleft");
    as->Asm("sta joystickright");
    as->Asm("sta joystickbutton");

    // UP
    as->Asm("lda #%00000001 ; mask joystick up movement");
    as->Asm("bit $dc00      ; bitwise AND with address 56320");
    as->Asm("bne joystick_down       ; zero flag is not set -> skip to down");
    as->Asm("lda #1");
    as->Asm("sta joystickup");

    as->Label("joystick_down");
    // DOWN

    as->Asm("lda #%00000010 ; mask joystick down movement");
    as->Asm("bit $dc00      ; bitwise AND with address 56320");
    as->Asm("bne joystick_left       ; zero flag is not set -> skip to down");
    as->Asm("lda #1");
    as->Asm("sta joystickdown");
    // LEFT

    as->Label("joystick_left");

    as->Asm("lda #%00000100 ; mask joystick left movement");
    as->Asm("bit $dc00      ; bitwise AND with address 56320");
    as->Asm("bne joystick_right       ; zero flag is not set -> skip to down");
    as->Asm("lda #1");
    as->Asm("sta joystickleft");

    // RIGHT
    as->Label("joystick_right");

    as->Asm("lda #%00001000 ; mask joystick up movement");
    as->Asm("bit $dc00      ; bitwise AND with address 56320");
    as->Asm("bne joystick_button       ; zero flag is not set -> skip to down");
    as->Asm("lda #1");
    as->Asm("sta joystickright");

    as->Label("joystick_button");
    // BUTTON

    as->Asm("lda #%00010000 ; mask joystick up movement");
    as->Asm("bit $dc00      ; bitwise AND with address 56320");
    as->Asm("bne callJoystick_end       ; zero flag is not set -> skip to down");
    as->Asm("lda #1");
    as->Asm("sta joystickbutton");


    as->Label("callJoystick_end");
    as->Asm("rts");

}

