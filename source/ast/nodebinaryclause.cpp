#include "nodebinaryclause.h"
#include "nodevar.h"
#include "nodenumber.h"




void NodeBinaryClause::BinaryClause(Assembler *as)
{
    QString b="";

    as->Comment("Binary clause: " + m_op.getType());
//    as->Asm("pha"); // Push that baby

    NodeVar* varb = dynamic_cast<NodeVar*>(m_right);
    if (varb!=nullptr)
        b = varb->value;

    NodeNumber* numb = dynamic_cast<NodeNumber*>(m_right);
    if (numb!=nullptr)
        b = numb->StringValue();

    m_left->Build(as);
    as->Term();
    if (b!="") {
        as->Comment("Compare with pure num / var optimization");
        as->Asm("cmp " + b);
    }
    else {
        // Perform a full compare : create a temp variable
        QString tmpVar = as->StoreInTempVar("binary_clause_temp");
        m_right->Build(as);
        as->Term();
        as->Asm("cmp " + tmpVar);
    }

    QString lblFailed = as->NewLabel("binaryclausefailed");
    QString lblFinished = as->NewLabel("binaryclausefinished");


    if (m_op.m_type==TokenType::EQUALS)
        as->Asm("bne " + lblFailed);
    if (m_op.m_type==TokenType::NOTEQUALS)
        as->Asm("beq " + lblFailed);
    if (m_op.m_type==TokenType::GREATER)
        as->Asm("bcc " + lblFailed);
    if (m_op.m_type==TokenType::LESS)
        as->Asm("bcs " + lblFailed);

    as->Asm("lda #1; success");
    as->Asm("jmp " + lblFinished);
    as->Label(lblFailed);
    as->Asm("lda #0 ; failed state");
    as->Label(lblFinished);

    as->PopLabel("binaryclausefailed");
    as->PopLabel("binaryclausefinished");
   // as->PopLabel("binary_clause_temp_var");
  //  as->PopLabel("binary_clause_temp_lab");

}

void NodeBinaryClause::LogicalClause(Assembler *as)
{
    if (dynamic_cast<NodeBinaryClause*>(m_left)==nullptr)
        ErrorHandler::e.Error("Logical clause: left hand term must be binary clause");

    if (dynamic_cast<NodeBinaryClause*>(m_right)==nullptr)
        ErrorHandler::e.Error("Logical clause: right hand term must be binary clause");

    m_left->Build(as);
    QString tmpVar = as->StoreInTempVar("logical_class_temp");
    m_right->Build(as);
    if (m_op.m_type==TokenType::AND)
        as->Asm("and " + tmpVar);

    if (m_op.m_type==TokenType::OR)
        as->Asm("ora " + tmpVar);

    //as->Asm("lda " + tmpVar);

    // Done comparing!
}

QString NodeBinaryClause::Build(Assembler *as)
{
    // First, check the byte
    if (m_op.m_type==TokenType::AND || m_op.m_type == TokenType::OR)
        LogicalClause(as);
    else
    if (m_op.m_type==TokenType::LESS || m_op.m_type == TokenType::GREATER ||
            m_op.m_type==TokenType::EQUALS || m_op.m_type == TokenType::NOTEQUALS)
        BinaryClause(as);
    else
        ErrorHandler::e.Error("Binary clause: Unknown compare token : " + m_op.getType());

    return "";

}
