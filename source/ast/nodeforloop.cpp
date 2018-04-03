#include "nodeforloop.h"
#include "nodenumber.h"

PVar NodeForLoop::Execute(SymbolTable *symTab, uint lvl) {
    Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
    level = lvl+1;
    ErrorHandler::e.DebugLow("Calling Forloop Node",level);
    PVar a = m_a->Execute(symTab, level);
    PVar b = m_b->Execute(symTab, level);
    NodeAssign* avar = (NodeAssign*)m_a;
    NodeVar* var = (NodeVar*)avar->m_left;

    //float val = symTab->Lookup(var->value)->m_value->m_fVal;

    for (float i = a.m_fVal;i<=b.m_fVal;i++) {
        symTab->Lookup(var->value, m_op.m_lineNumber)->m_value->m_fVal = i;
        m_block->Execute(symTab, level);
    }

    return PVar();

}

void NodeForLoop::LargeLoop(Assembler *as)
{
    QString loopForFix = as->NewLabel("forLoopFix");
    QString loopDone = as->NewLabel("forLoopDone");
    m_b->Build(as);
    as->Term();
    as->Asm("cmp " + as->m_stack["for"].current());
    as->Asm("bne "+loopForFix);
    as->Asm("jmp "+loopDone);
    as->Label(loopForFix);
    m_block->Build(as);
//    as->EndForLoop(m_b);
    as->m_stack["for"].pop();
    as->Asm("inc " + as->m_stack["for"].current());

    as->Asm("jmp " + as->getLabel("for"));

    as->Label(loopDone);

    as->m_labelStack["for"].pop();
    as->m_labelStack["forLoopFix"].pop();
    as->m_labelStack["forLoopDone"].pop();

}

void NodeForLoop::SmallLoop(Assembler *as)
{
    QString loopDone = as->NewLabel("forLoopDone");
    m_b->Build(as);
    as->Term();
    as->Asm("cmp " + as->m_stack["for"].current());
    as->Asm("beq "+loopDone);
    m_block->Build(as);
//    as->EndForLoop(m_b);
    as->m_stack["for"].pop();
    as->Asm("inc " + as->m_stack["for"].current());

    as->Asm("jmp " + as->getLabel("for"));

    as->Label(loopDone);

    as->m_labelStack["for"].pop();
    as->m_labelStack["forLoopDone"].pop();

}




QString NodeForLoop::Build(Assembler *as) {
    Node::Build(as);

    //QString m_currentVar = ((NodeAssign*)m_a)->m_
    QString var = m_a->Build(as);
    //QString to = m_b->Build(as);
    QString to = "";
    if (dynamic_cast<const NodeNumber*>(m_b) != nullptr)
        to = QString::number(((NodeNumber*)m_b)->m_val);
    if (dynamic_cast<const NodeVar*>(m_b) != nullptr)
        to = ((NodeVar*)m_b)->value;
  //  if (m_b->m_op.m_type==TokenType::INTEGER ||m_b->m_op.m_type==TokenType::INTEGER_CONST )
  //      to = "#" + to;
    as->StartForLoop(var, to);


    if (verifyBlockBranchSize(as, m_block))
        SmallLoop(as);
    else
        LargeLoop(as);

//    if (Syntax::s.isNumeric(endVal))
//        endVal = "#" + endVal;


 //   qDebug() << label2;
  //  qDebug() << labelDone;



 //   qDebug() << "loop: " << m_stack["for"].current();
    return "";
}
