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

void AsmMOS6502::DeclareArray(QString name, QString type, int count, QStringList data)
{
    QString t = byte;
    if (type.toLower()=="integer")
        t = word;
    if (type.toLower()=="byte")
        t = byte;


    if (data.count()==0) {
        Write(name +"\t" + t + "\t ");
        Asm("org "+name+"+" +QString::number(count));
    }
    else {
        Write(name);

        ClearTerm();
        Term(".byte ");
        for (int i=0;i<data.count();i++) {
            Term(data[i]);
            if (i%8==7) {
                Term();
                Term(".byte ");
            }
            else Term(", ");

        }
    }
    Term();
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
        t = word;
    if (type.toLower()=="byte")
        t = byte;

    Write(name +"\t" + t);

}

void AsmMOS6502::BeginBlock()
{
    Nl();
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

void AsmMOS6502::Comment(QString s)
{
    Asm("; "+ s) ;
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

    if (t == TokenType::MINUS) {
        Asm("sec");
        m_term = "sbc ";
    }
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
/*    m_term += v;
    return;
*/

    if (m_term=="")
        m_term = "lda ";
    m_term+=v;
  /*  if (endTerm()) {
        Asm(m_term);
        ClearTerm();
    }*/
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
    m_labelStack["forLoopFix"].push();
    m_labelStack["forLoopDone"].push();
    QString label2 = getLabel("forLoopFix");
    QString labelDone = getLabel("forLoopDone");

    Asm("inc " + m_stack["for"].current());
    Asm("lda "+m_stack["for"].current());

//    if (Syntax::s.isNumeric(endVal))
//        endVal = "#" + endVal;
    Asm("cmp " + endVal);
    Asm("bne "+label2);
    Asm("jmp "+labelDone);
    Label(label2);
    Asm("jmp " + getLabel("for"));

    Label(labelDone);
    m_labelStack["for"].pop();
    m_labelStack["forLoopFix"].pop();
    m_labelStack["forLoopDone"].pop();

 //   qDebug() << label2;
  //  qDebug() << labelDone;



 //   qDebug() << "loop: " << m_stack["for"].current();

}

void AsmMOS6502::Optimise()
{
    OptimisePassStaLda();
}

void AsmMOS6502::OptimisePassStaLda()
{
    m_removeLines.clear();
    int j;
    for (int i=0;i<m_source.count()-1;i++) {
        QString l0 = getLine(i);



        if (l0.contains("sta")) {
            QString l1 = getNextLine(i,j);
            if (l0==l1) {
                m_removeLines.append(j);
                continue;
            }



            QString var = getToken(l0,1);
            if (getToken(l1,1)==var && getToken(l1,0)=="lda") {

                m_removeLines.append(j);
                i++;
                continue;
            }


        }
    }
    RemoveLines();
}

QString AsmMOS6502::getLine(int i)
{
    QString s = m_source[i].trimmed().toLower().simplified();
    return s;
}

QString AsmMOS6502::getNextLine(int i, int &j)
{
    bool ok = false;
    i=i+1;
    QString line ="";
    while (i<m_source.count() && getLine(i)=="") {
        i++;
    }
    j=i;
    return getLine(i);

}

QString AsmMOS6502::getToken(QString s, int t)
{
    QStringList lst = s.split(" ");
    if (t>=lst.count())
        return "";
    return lst[t];
}

void AsmMOS6502::RemoveLines()
{
    int k=0;
    for (int i: m_removeLines) {
        qDebug() << "Removing line " << (i) << " : " << getLine(i-k);
        m_source.removeAt(i-k);
        k++;
    }
    m_removeLines.clear();
}



