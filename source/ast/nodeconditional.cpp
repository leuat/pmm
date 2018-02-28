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

QString NodeConditional::Build(Assembler *as) {

    as->m_labelStack["branch"].push();
    as->m_labelStack["while"].push();
    QString label = as->getLabel("branch");
    QString labelOutside = as->getLabel("while");
    if (m_isWhileLoop)
        as->Label(labelOutside);
    as->ClearTerm();
    as->Term("lda ");
    m_a->Build(as);
    as->Term();
    as->Term("cmp ");
    m_b->Build(as);
    as->Term();

    if (m_op.m_type==TokenType::EQUALS)
        as->Asm("bne " + label);
    if (m_op.m_type==TokenType::NOTEQUALS)
        as->Asm("beq " + label);
    if (m_op.m_type==TokenType::GREATER)
        as->Asm("bcc " + label);
    if (m_op.m_type==TokenType::LESS)
        as->Asm("bcs " + label);
    m_block->Build(as);
    if (m_isWhileLoop)
        as->Asm("jmp " + labelOutside);
//    as->Label(labelOutside);
    as->Label(label);
    as->m_labelStack["while"].pop();
    as->m_labelStack["branch"].pop();

    return "";
}
