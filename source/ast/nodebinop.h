#ifndef NODEBINOP_H
#define NODEBINOP_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodeVar.h"
#include "source/ast/nodenumber.h".h"

class NodeBinOP : public Node {
public:

    NodeBinOP(Node* left, Token op, Node* right) {
        m_right = right;
        m_left = left;
        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
        m_left->ExecuteSym(symTab);
        m_right->ExecuteSym(symTab);
    }

    QString BothConstants(Assembler* as) {
        NodeNumber *a = (NodeNumber*)dynamic_cast<const Node*>(m_left);
        NodeNumber *b = (NodeNumber*)dynamic_cast<const Node*>(m_right);
        int val = 0;
        if (m_op.m_type==TokenType::PLUS)
                val = a->m_val + b->m_val;
        if (m_op.m_type==TokenType::MINUS)
            val = a->m_val - b->m_val;

        if (m_op.m_type==TokenType::DIV)
            val = a->m_val / b->m_val;
        if (m_op.m_type==TokenType::MUL)
            val = a->m_val * b->m_val;

        QString str = "";
        if (a->m_op.m_type==TokenType::ADDRESS && b->m_op.m_type==TokenType::ADDRESS) {
            str = "$" + QString::number(val,16);
        }
        else
            if (a->m_op.m_type==TokenType::INTEGER && b->m_op.m_type==TokenType::INTEGER) {
                str = "#"+ QString::number(val);
            }
        if (a->m_op.m_type==TokenType::BYTE && b->m_op.m_type==TokenType::BYTE) {
            str = "#"+ QString::number(val);
        }
            else {
                ErrorHandler::e.Error("BinOp for constants must be numbers or addresses");
            }
        as->Term(str);

        return "";
    }

    bool isPureNumeric() override {
        if (m_left==nullptr || m_right==nullptr)
            return false;
        return (m_left->isPureNumeric() && m_right->isPureNumeric());
    }

    int getShiftCount(int i) {
        if (i==1) return 0;
        if (i==2) return 1;
        if (i==4) return 2;
        if (i==8) return 3;
        if (i==16) return 4;
        if (i==32) return 5;
        if (i==64) return 6;
        if (i==128) return 7;
        return -1;
    }






    void EightBitMul(Assembler* as) {
        as->Comment("8 bit mul");
        as->ClearTerm();
        as->Term("lda ");
        m_left->Build(as);
        as->Term();
        as->Term("ldx ");
        m_right->Build(as);
        as->Term();
        as->Asm("jsr multiply_eightbit");
        as->Asm("txa");


    }


    void LoadVariable(Assembler* as) override {
        Build(as);

    }


    QString Build(Assembler *as) override {

        // First check if both are consants:

        if (isPureNumeric()) {
            NodeNumber *a = (NodeNumber*)dynamic_cast<const NodeNumber*>(m_left);
            NodeNumber *b = (NodeNumber*)dynamic_cast<const NodeNumber*>(m_right);
            //BothConstants(as);
            as->Comment("Binop of two constant values");
            m_left->Build(as);
            if (m_op.m_type==TokenType::PLUS)
                as->Term("+");
            if (m_op.m_type==TokenType::MINUS)
                as->Term("-");
            if (m_op.m_type==TokenType::DIV)
                as->Term("/");
            if (m_op.m_type==TokenType::MUL)
                as->Term("*");
            if (m_op.m_type==TokenType::BITAND)
                as->Term("&");
            if (m_op.m_type==TokenType::BITOR)
                as->Term("|");

            m_right->Build(as);

            return "";
        }



        if (m_op.m_type==TokenType::MUL || m_op.m_type==TokenType::DIV) {
            if (m_right->isPureNumeric())  {
                int val = ((NodeNumber*)m_right)->m_val;



                //check power of two
                int cnt = getShiftCount(val);
                if (cnt == -1 ) {
                    if (m_op.m_type == TokenType::MUL)
                        EightBitMul(as);
                    else
                        ErrorHandler::e.Error("Binary operation / not implemented for this value yet ( " + QString::number(val) + ")");
                    return "";
                }
                as->Comment("8 bit mul of power 2");

                QString command = "";
                if (m_op.m_type == TokenType::DIV)
                    command = "lsr";
                if (m_op.m_type == TokenType::MUL)
                    command = "asl";


                as->Asm("");
                m_left->LoadVariable(as);
                for (int i=0;i<cnt;i++)
                    as->Asm(command);
                return "";

            }

            ErrorHandler::e.Error("Binary operation */ not implemented for this type yet...");
        }
        bool isWord = false;
        QString varName="";

        if ( dynamic_cast<const NodeVar*>(m_left) != nullptr) {
            NodeVar* v= (NodeVar*)m_left;
            varName = v->value;
            Symbol* s = as->m_symTab->Lookup(varName);
            if (s==nullptr)
                ErrorHandler::e.Error("Could not find variable :" + varName,m_op.m_lineNumber);

            if (s->m_type.toLower()=="integer") isWord=true;
        }

        // check if both are constant values:


        if (!isWord) {
            // Optimizing check: if right var is number, then cut losses

            if (dynamic_cast<const NodeNumber*>(m_right)!=nullptr) {
                as->Comment("Add/sub where right value is constant number");

                m_left->Build(as);
                as->Term();
                as->BinOP(m_op.m_type);
                m_right->Build(as);
                as->Term();
                as->Term(" ; end mul var with constant", true);

            }
            else {
                as->Comment("Add/sub right value is variable/expression");



                QString lbl = as->NewLabel("rightvar");
                QString lblJmp = as->NewLabel("jmprightvar");
                as->Asm("jmp " + lblJmp);
                as->Write(lbl +"\t.byte\t0");
                as->Label(lblJmp);
                as->ClearTerm();
                m_right->Build(as);
                as->Term();
                as->Asm("sta " +lbl);
                as->Term();
                /*if (dynamic_cast<NodeVar* >(m_left)!=nullptr) {
                    as->Term("lda ");
                    m_left->Build(as);
                    as->Term();
                }*/
                m_left->Build(as);
                as->Term();

                as->BinOP(m_op.m_type);
                as->Term(lbl,true);
                as->PopLabel("rightvar");
                as->PopLabel("jmprightvar");
            }
        }
        else {
            as->m_labelStack["wordAdd"].push();
            QString lblword = as->getLabel("wordAdd");

            QString lbl = as->NewLabel("rightvarInteger");
            QString lblJmp = as->NewLabel("jmprightvarInteger");

            NodeVar* v = (NodeVar*)m_left;

            as->Asm("jmp " + lblJmp);
            as->Write(lbl +"\t.byte\t0");
            as->Label(lblJmp);
            as->ClearTerm();
            qDebug() << " A: " << m_right->m_op.getType();

            m_right->Build(as);
            qDebug() << " B";
            as->Term();
            as->Asm("sta " +lbl);
            as->Term();

            as->Asm("clc");
            as->Variable(v->value, false);
            as->Term();
            as->ClearTerm();
            as->BinOP(m_op.m_type);
            as->Term(lbl,true);
    //        as->Asm("sta " + varName);
            if (m_op.m_type==TokenType::PLUS) {
                as->Asm("bcc "+lblword);
                as->Asm("inx");
            }
            else {
                as->Asm("bcs "+lblword);
                as->Asm("dex");
            }
            as->Label(lblword);

            as->PopLabel("wordAdd");

            as->PopLabel("rightvarInteger");
            as->PopLabel("jmprightvarInteger");
        }
        return "";
    }

};


#endif // NODEBINOP_H
