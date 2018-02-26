#ifndef NODESTRING_H
#define NODESTRING_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeString : public Node {
public:
    QString m_val;
    NodeString(Token op, QString val) {
        m_op = op;
        m_val = val;
    }
    PVar  Execute(SymbolTable* symTab, uint lvl) override {
        Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        level = lvl +1;
        return PVar(m_val);
    }
    void ExecuteSym(SymbolTable* symTab) override {
    }
};

#endif // NODESTRING_H
