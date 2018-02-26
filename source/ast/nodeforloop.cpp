#include "nodeforloop.h"


PVar NodeForLoop::Execute(SymbolTable *symTab, uint lvl) {
    Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
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
