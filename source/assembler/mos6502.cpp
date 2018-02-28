#include "mos6502.h"
#include "source/syntax.h"

AsmMOS6502::AsmMOS6502()
{
//    m_stack["for"] = new Stack();
}

void AsmMOS6502::Program(QString programName)
{
    Asm("processor 6502");
    Nl();
    Asm("ORG $0801");
    Asm(".byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33");
    Asm(".byte    $30, $34, $29, $00, $00, $00");
    Nl();
    Asm("ORG $0900");
    Nl();
    Label(programName);
}

void AsmMOS6502::EndProgram()
{
    Asm("rts");
}

void AsmMOS6502::VarDeclHeader()
{
    m_labelStack["block"].push();
    Asm("jmp "+ getLabel("block"));
}

void AsmMOS6502::DeclareVariable(QString name, QString type)
{
    QString t = byte;
    if (type.toLower()=="integer")
        t = byte;

    Write(name +"\t" + t);

}

void AsmMOS6502::BeginBlock()
{
    Nl();
    Label(getLabel("block"));
}

void AsmMOS6502::EndBlock()
{
    Nl();
    m_labelStack["block"].pop();
}

void AsmMOS6502::ApplyTerm()
{
    //Asm("sta " + m_currentVar);

    m_currentVar = "";
}

void AsmMOS6502::Number(QString n)
{

    m_term +=n;
    return;

    if (m_term=="")
        m_term = "lda ";

//    if (m_term.contains("sta"))
        m_term +=n;
  //  else
    //    m_term+="\#" + n;
    if (endTerm()) {
        Asm(m_term);
        ClearTerm();
    }

    //Asm(m_term + n);

}

void AsmMOS6502::String(QString s)
{
    m_term +="\"" + s.toUpper() + "\"";
}

void AsmMOS6502::AssignVariable(QString v)
{
    m_currentVar = v;
    m_term="lda ";
}

void AsmMOS6502::EndAssignVariable(QString variable)
{
    Asm(m_term);
    Asm("sta " + variable);
}

void AsmMOS6502::BinOP(TokenType::Type t)
{
    if (t == TokenType::PLUS)
        m_term = "adc ";

    if (t == TokenType::MINUS)
        m_term = "sbc ";
}

void AsmMOS6502::Poke(bool start)
{
    //if (start)
     //   m_term = "lda ";
    if (!start)
       m_term = "sta ";
}

void AsmMOS6502::Peek(bool start)
{
    if (start)
        m_term = "lda ";
   else m_term = "sta ";

}

void AsmMOS6502::Writeln()
{
    m_labelStack["writeln"].push();
    QString l = "L" + getLabel("writeln");
    Asm("LDY #$00");
    Label(l+"0");
    Asm("LDA "+l+"1,Y");
    Asm("CMP #0");
    Asm("BEQ "+l+"2");
    Asm("JSR $FFD2");
    Asm("INY");
    Asm("JMP "+l+"0");
    Label(l+"1");
    m_term = ".byte ";

}

void AsmMOS6502::EndWriteln()
{
    Asm(m_term + ",0");
    Label("L"+getLabel("writeln")+"2");
    m_labelStack["writeln"].pop();

}

void AsmMOS6502::LoadVariable(QString var)
{
    Asm("lda "+ var);
}

void AsmMOS6502::Variable(QString v)
{
    m_term += v;
    return;


    if (m_term=="")
        m_term = "lda ";
    m_term+=v;
    if (endTerm()) {
        Asm(m_term);
        ClearTerm();
    }
}

void AsmMOS6502::WriteBuiltinWriteln()
{

}

void AsmMOS6502::StartPrint()
{
    /*
    LDY #$00
 L0
     LDA L1,Y
     CMP #0
     BEQ L2
     JSR $FFD2
     INY
     JMP L0
 L1
     .byte "hello world",0
 L2
 */
}


void AsmMOS6502::StartForLoop(QString var, QString startVal)
{
    m_stack["for"].push(var);
    m_labelStack["for"].push();
    //m_currentLoopVar = var;
    //Asm("lda " + startVal);
    //Asm("sta " + var);
    Label(getLabel("for"));
}

void AsmMOS6502::EndForLoop(QString endVal)
{
    m_stack["for"].pop();
    Asm("inc " + m_stack["for"].current());
    Asm("lda "+m_stack["for"].current());

//    if (Syntax::s.isNumeric(endVal))
//        endVal = "#" + endVal;
    Asm("cmp " + endVal);
    Asm("bne "+getLabel("for"));
    m_labelStack["for"].pop();

    qDebug() << "loop: " << m_stack["for"].current();

}



