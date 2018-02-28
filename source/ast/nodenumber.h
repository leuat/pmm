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

    QString Build(Assembler *as) override {
        QString val = "";
        if (m_op.m_type==TokenType::INTEGER)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::INTEGER_CONST)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::ADDRESS) {
            val = "$" + QString::number((int)m_val,16);
        }
        as->Number(val);
        return val;
    }


};

#endif // NODENUMBER_H
