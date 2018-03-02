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

    QString Build(Assembler *as) override {

        // First check if both are consants:

        if (isPureNumeric()) {
            NodeNumber *a = (NodeNumber*)dynamic_cast<const NodeNumber*>(m_left);
            NodeNumber *b = (NodeNumber*)dynamic_cast<const NodeNumber*>(m_right);
            //BothConstants(as);

            m_left->Build(as);
            if (m_op.m_type==TokenType::PLUS)
                as->Term("+");
            if (m_op.m_type==TokenType::MINUS)
                as->Term("-");
            if (m_op.m_type==TokenType::DIV)
                as->Term("/");
            if (m_op.m_type==TokenType::MUL)
                as->Term("*");

            m_right->Build(as);

            return "";
        }



        m_left->Build(as);
        as->Term();
        bool isWord = false;
        QString varName="";

        if ( dynamic_cast<const NodeVar*>(m_left) != nullptr) {
            NodeVar* v= (NodeVar*)m_left;
            varName = v->value;
            Symbol* s = as->m_symTab->Lookup(varName);

            if (s->m_type.toLower()=="integer") isWord=true;
        }

        // check if both are constant values:


        if (!isWord) {
            qDebug() << "FACTOR";
            as->BinOP(m_op.m_type);
            m_right->Build(as);
            as->Term();
        }
        else {
            as->m_labelStack["wordAdd"].push();
            QString lbl = as->getLabel("wordAdd");
            as->Asm("clc");
            as->Asm("lda " +varName);
            as->ClearTerm();
            as->BinOP(m_op.m_type);
            m_right->Build(as);
            as->Term();
            as->Asm("sta " + varName);
            as->Asm("bcc "+lbl);
            as->Asm("inc " +varName + "+1");
            as->Label(lbl);
            as->m_labelStack["wordAdd"].pop();
        }
        return "";
    }

};


#endif // NODEBINOP_H
