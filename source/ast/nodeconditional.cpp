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
    as->m_labelStack["branchProblem"].push();
    as->m_labelStack["branchProblem2"].push();
    QString label = as->getLabel("branch");
    QString labelOutside = as->getLabel("while");
    QString labelb1 = as->getLabel("branchProblem");
    QString labelb2 = as->getLabel("branchProblem2");

    if (m_isWhileLoop)
        as->Label(labelOutside);

    as->ClearTerm();
    m_b->Build(as);
    as->Term();
    as->Term("cmp ");
    m_a->Build(as);
    as->Term();

    if (m_op.m_type==TokenType::NOTEQUALS)
        as->Asm("bne " + labelb1);
    if (m_op.m_type==TokenType::EQUALS)
        as->Asm("beq " + labelb1);
    if (m_op.m_type==TokenType::GREATER)
        as->Asm("bcc " + labelb1);
    if (m_op.m_type==TokenType::LESS)
        as->Asm("bcs " + labelb1);

    as->Asm("jmp " + label);
    /*

    as->Asm("jmp " + labelb2);
    as->Label(labelb1); // This means skip inside
    as->Asm("jmp " + label);
    as->Label(labelb2);

    */
    as->Label(labelb1); // This means skip inside

    m_block->Build(as);

    if (m_isWhileLoop)
        as->Asm("jmp " + labelOutside);

    as->Label(label);

    as->m_labelStack["while"].pop();
    as->m_labelStack["branch"].pop();
    as->m_labelStack["branchProblem"].pop();
    as->m_labelStack["branchProblem2"].pop();

    return "";
}
