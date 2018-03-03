#ifndef NODENUMBER_H
#define NODENUMBER_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"


class NodeNumber : public Node {
public:
    float m_val;
    NodeNumber(Token op, int val) {
        m_op = op;
        m_val = val;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
    }

    bool isPureNumeric() override {
        return true;
    }

    void LoadVariable(Assembler* as) override {
        as->ClearTerm();
        as->Term("lda ");
        Build(as);
        as->Term();
    }

    QString Build(Assembler *as) override {
        QString val = "";
        if (m_op.m_type==TokenType::INTEGER)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::INTEGER_CONST)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::ADDRESS) {
            val = "$" + QString::number((int)m_val,16);
        }
        //as->Number(val);
        if (as->m_term=="")
            as->Asm("lda " + val);
        else
            as->Term(val);
        return val;
    }


};

#endif // NODENUMBER_H
