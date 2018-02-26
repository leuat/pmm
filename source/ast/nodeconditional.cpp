#include "nodeconditional.h"


PVar NodeConditional::Execute(SymbolTable *symTab, uint lvl) {
    Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
    level = lvl+1;
    ErrorHandler::e.DebugLow("Calling Conditional Node",level);
    PVar a = m_a->Execute(symTab, level);
    PVar b = m_b->Execute(symTab, level);
    ErrorHandler::e.DebugHigh("Comparing " + a.toString() + " to " + b.toString() + " with comparator " +m_op.m_value ,level);

    if (m_op.m_type==TokenType::EQUALS)
        if (a==b)
            m_block->Execute(symTab, level);

    if (m_op.m_type==TokenType::NOTEQUALS)
        if (!(a==b))
            m_block->Execute(symTab, level);

    if (m_op.m_type==TokenType::GREATER)
        if ((a>b))
            m_block->Execute(symTab, level);

    if (m_op.m_type==TokenType::LESS)
        if ((a<b))
            m_block->Execute(symTab, level);

    return PVar();

}
