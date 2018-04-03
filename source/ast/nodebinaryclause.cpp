#include "nodebinaryclause.h"
#include "nodevar.h"
#include "nodenumber.h"




void NodeBinaryClause::BuildToCmp(Assembler *as)
{
    QString b="";

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


}

void NodeBinaryClause::BuildSimple(Assembler *as, QString lblFailed)
{

    as->Comment("Binary clause Simplified: " + m_op.getType());
//    as->Asm("pha"); // Push that baby

    BuildToCmp(as);

    if (m_op.m_type==TokenType::EQUALS)
        as->Asm("bne " + lblFailed);
    if (m_op.m_type==TokenType::NOTEQUALS)
        as->Asm("beq " + lblFailed);
    if (m_op.m_type==TokenType::GREATER)
        as->Asm("bcc " + lblFailed);
    if (m_op.m_type==TokenType::LESS)
        as->Asm("bcs " + lblFailed);



}

void NodeBinaryClause::BinaryClause(Assembler *as)
{

    as->Comment("Binary clause: " + m_op.getType());

    BuildToCmp(as);

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


void NodeBinaryClause::BinaryClauseInteger(Assembler *as)
{

    as->Comment("Binary clause INTEGER: " + m_op.getType());
//    as->Asm("pha"); // Push that baby

    NodeVar* varb = dynamic_cast<NodeVar*>(m_right);

    NodeNumber* numb = dynamic_cast<NodeNumber*>(m_right);


    NodeVar* vara = dynamic_cast<NodeVar*>(m_left);

    if (vara==nullptr)
        ErrorHandler::e.Error("Integer comparison: only pure integer variable is supported");

    QString lbl1 = as->NewLabel("binaryclauseintegerlbl1");
    QString lbl2 = as->NewLabel("binaryclauseintegerlbl2"); // failed
    QString lbl3 = as->NewLabel("binaryclauseintegerfinished"); // failed

    QString lo = "";
    QString hi = "";

    if (numb!=nullptr) {
        lo = "#" + QString::number(((int)numb->m_val) & 255);
        hi = "#" + QString::number(((int)numb->m_val>>8) & 255);
    }
    if (varb!=nullptr) {
        lo = varb->value;
        hi = varb->value+ "+1";
    }

    m_left->Build(as);
    as->Term();

    if (numb!=nullptr || varb!=nullptr) {
        if (m_op.m_type==TokenType::GREATER) {
            as->Comment("Compare INTEGER with pure num / var optimization");
            as->Asm("lda " + vara->value + "+1   ; compare high bytes");
            as->Asm("cmp " + hi);
            as->Asm("bcc " + lbl2);
            as->Asm("bne " + lbl1);
            as->Asm("lda " + vara->value);
            as->Asm("cmp " + lo);
            as->Asm("bcc " + lbl2);
        }
        if (m_op.m_type==TokenType::LESS) {
            as->Comment("Compare INTEGER with pure num / var optimization");
            as->Asm("lda " + vara->value + "+1   ; compare high bytes");
            as->Asm("cmp " + hi);
            as->Asm("bcc " + lbl1);
            as->Asm("bne " + lbl2);
            as->Asm("lda " + vara->value);
            as->Asm("cmp " + lo);
            as->Asm("bcs " + lbl2);
        }
        as->Label(lbl1); // ok
        as->Asm("lda #1");
        as->Asm("jmp " + lbl3);
        as->Label(lbl2); // failed
        as->Asm("lda #2");

        as->Label(lbl3); // DONE


        // Now all is ok
    }
    else {
        ErrorHandler::e.Error("Comparison of integer only works with number or variable");
    }




/*
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
*/
    as->PopLabel("binaryclauseintegerlbl1");
    as->PopLabel("binaryclauseintegerlbl2");
    as->PopLabel("binaryclauseintegerfinished");
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
    Node::Build(as);

    // First, check the byte
    if (m_op.m_type==TokenType::AND || m_op.m_type == TokenType::OR)
        LogicalClause(as);
    else
    if (m_op.m_type==TokenType::LESS || m_op.m_type == TokenType::GREATER ||
            m_op.m_type==TokenType::EQUALS || m_op.m_type == TokenType::NOTEQUALS) {
        if (m_left->getType(as)==TokenType::INTEGER)
            BinaryClauseInteger(as);
        else
            //qDebug() << "COMPARING INTEGER WITH " << TokenType::types[m_left->getType(as)];
            BinaryClause(as);
    }
    else
        ErrorHandler::e.Error("Binary clause: Unknown compare token : " + m_op.getType());

    return "";

}
