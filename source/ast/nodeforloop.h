#ifndef NODEFORLOOP_H
#define NODEFORLOOP_H

#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodeassign.h"
#include "source/ast/nodevar.h"


class NodeForLoop : public Node {
public:

    Node* m_a, *m_b;
    Node* m_block;


    NodeForLoop(Node* a, Node* b, Node* block) {
        m_a = a;
        m_b = b;
        m_block = block;
//        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void ExecuteSym(SymbolTable* symTab) override {
        m_block->ExecuteSym(symTab);
    }


};
#endif // NODEFORLOOP_H
