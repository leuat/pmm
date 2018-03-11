#include "nodeconditional.h"


QString NodeConditional::Build(Assembler *as) {
    QString labelStartOverAgain = as->NewLabel("while");
    QString lblstartTrueBlock = as->NewLabel("ConditionalTrueBlock");

    QString labelElse = as->NewLabel("elseblock");
    QString labelElseDone = as->NewLabel("elsedoneblock");
   // QString labelFailed = as->NewLabel("conditionalfailed");

    if (m_isWhileLoop)
        as->Label(labelStartOverAgain);

    // Test all binary clauses:
    m_binaryClause->Build(as);
    // Now, a should be either true or false

    as->Asm("cmp #1");
    as->Asm("beq " + lblstartTrueBlock); // All conditionals checked out!
    // Failed label
 //   as->Label(labelFailed);
    // Do we have an else block?
    if (m_elseBlock!=nullptr)
        as->Asm("jmp " + labelElse); // All conditionals false: skip to end (or else block)
    // If just plain conditional, jump to end
    as->Asm("jmp " + labelElseDone);
    // Start main block
    as->Label(lblstartTrueBlock); // This means skip inside

    m_block->Build(as);
    if (m_elseBlock!=nullptr)
        as->Asm("jmp " + labelElseDone);

    // If while loop, return to beginning of conditionals
    if (m_isWhileLoop)
        as->Asm("jmp " + labelStartOverAgain);

    // An else block?
    if (m_elseBlock!=nullptr) {
        as->Label(labelElse);
        m_elseBlock->Build(as);

    }
    as->Label(labelElseDone); // Jump here if not

    as->PopLabel("while");
    as->PopLabel("ConditionalTrueBlock");
    as->PopLabel("elseblock");
    as->PopLabel("elsedoneblock");
//    as->PopLabel("conditionalfailed");



    return "";
}







PVar NodeConditional::Execute(SymbolTable *symTab, uint lvl) {
/*    Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
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
*/
    return PVar();

}

/*void NodeConditional::ConditionalTryFail(Assembler* as, QString labelFailed, int i)
{
    as->ClearTerm();
    m_b[i]->Build(as);
    as->Term();
    as->Term("cmp ");
    m_a[i]->Build(as);
    as->Term();

    if (m_compares[i].m_type==TokenType::EQUALS)
        as->Asm("bne " + labelFailed);
    if (m_compares[i].m_type==TokenType::NOTEQUALS)
        as->Asm("beq " + labelFailed);
    if (m_compares[i].m_type==TokenType::LESS)
        as->Asm("bcc " + labelFailed);
    if (m_compares[i].m_type==TokenType::GREATER)
        as->Asm("bcs " + labelFailed);
}

void NodeConditional::ConditionalTrySuccess(Assembler* as, QString labelSuccess, int i)
{
    as->ClearTerm();
    m_b[i]->Build(as);
    as->Term();
    as->Term("cmp ");
    m_a[i]->Build(as);
    as->Term();

    if (m_compares[i].m_type==TokenType::NOTEQUALS)
        as->Asm("bne " + labelSuccess);
    if (m_compares[i].m_type==TokenType::EQUALS)
        as->Asm("beq " + labelSuccess);
    if (m_compares[i].m_type==TokenType::GREATER)
        as->Asm("bcc " + labelSuccess);
    if (m_compares[i].m_type==TokenType::LESS)
        as->Asm("bcs " + labelSuccess);
}



QString NodeConditional::Build(Assembler *as) {


    QString labelStartOverAgain = as->NewLabel("while");
    QString lblstartTrueBlock = as->NewLabel("ConditionalTrueBlock");

    QString labelElse = as->NewLabel("elseblock");
    QString labelElseDone = as->NewLabel("elsedoneblock");
    QString labelFailed = as->NewLabel("conditionalfailed");

    if (m_isWhileLoop)
        as->Label(labelStartOverAgain);

    // Loop through all conditionals

    if (m_conditionals.count()==0)
        ConditionalTryFail(as, labelFailed, 0);
    else
    {
    for (int i=0;i<m_conditionals.count();i++) {

        if (m_conditionals[i].m_type == TokenType::AND) {
            ConditionalTryFail(as, labelFailed, i);
            ConditionalTryFail(as, labelFailed, i+1);
        }
        if (m_conditionals[i].m_type == TokenType::OR) {
            ConditionalTrySuccess(as, lblstartTrueBlock, i);
            ConditionalTrySuccess(as, lblstartTrueBlock, i+1);
            if (i==m_conditionals.count()-1)
                as->Asm("jmp " + labelFailed);
        }
    }

    }
    // if all is OK, jump right to start block
    as->Asm("jmp " + lblstartTrueBlock); // All conditionals checked out!
    // Failed label
    as->Label(labelFailed);
    // Do we have an else block?
    if (m_elseBlock!=nullptr)
        as->Asm("jmp " + labelElse); // All conditionals false: skip to end (or else block)
    // If just plain conditional, jump to end
    as->Asm("jmp " + labelElseDone);
    // Start main block
    as->Label(lblstartTrueBlock); // This means skip inside

    m_block->Build(as);
    if (m_elseBlock!=nullptr)
        as->Asm("jmp " + labelElseDone);

    // If while loop, return to beginning of conditionals
    if (m_isWhileLoop)
        as->Asm("jmp " + labelStartOverAgain);

    // An else block?
    if (m_elseBlock!=nullptr) {
        as->Label(labelElse);
        m_elseBlock->Build(as);

    }
    as->Label(labelElseDone); // Jump here if not

    as->PopLabel("while");
    as->PopLabel("ConditionalTrueBlock");
    as->PopLabel("elseblock");
    as->PopLabel("elsedoneblock");
    as->PopLabel("conditionalfailed");



    return "";
}
*/

