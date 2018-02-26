#ifndef NODEVARTYPE_H
#define NODEVARTYPE_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"

class NodeVarType : public Node {
public:
    QString value;
    NodeVarType(Token t) {
        m_op = t;
        value = t.m_value;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {

    }

};
#endif // NODEVARTYPE_H
