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
        symTab->Lookup(var->value)->m_value->m_fVal = i;
        m_block->Execute(symTab, level);
    }

    return PVar();

}

QString NodeForLoop::Build(Assembler *as) {
    //QString m_currentVar = ((NodeAssign*)m_a)->m_
    QString var = m_a->Build(as);
    //QString to = m_b->Build(as);
    QString to = "";
    if (dynamic_cast<const NodeNumber*>(m_b) != nullptr)
        to = QString::number(((NodeNumber*)m_b)->m_val);
    if (dynamic_cast<const NodeVar*>(m_b) != nullptr)
        to = ((NodeVar*)m_b)->value;
    as->StartForLoop(var, to);
    m_block->Build(as);

    as->EndForLoop(to);
    return "";
}
