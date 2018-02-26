#ifndef NODECONDITIONAL_H
#define NODECONDITIONAL_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"


class NodeConditional : public Node {
public:

    Node* m_a, *m_b;
    Node* m_block;


    NodeConditional(Token op, Node* a, Node* b, Node* block) {
        m_a = a;
        m_b = b;
        m_block = block;
        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void ExecuteSym(SymbolTable* symTab) override {
       m_block->ExecuteSym(symTab);
    }


};

#endif // NODECONDITIONAL_H
