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
        as->Number(m_val);
        return QString::number(m_val);
    }


};

#endif // NODENUMBER_H
