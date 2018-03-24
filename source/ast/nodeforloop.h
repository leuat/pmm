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
    void Delete() override {
        if (m_a) {
            m_a->Delete();
            delete m_a;
            m_a = nullptr;
        }
        if (m_b) {
            m_b->Delete();
            delete m_b;
            m_b = nullptr;
        }
        if (m_block) {
            m_block->Delete();
            delete m_block;
            m_block = nullptr;
        }


    }
    void ExecuteSym(SymbolTable* symTab) override {
        m_block->ExecuteSym(symTab);
    }


    void LargeLoop(Assembler* as);
    void SmallLoop(Assembler* as);

    QString Build(Assembler *as) override;

};
#endif // NODEFORLOOP_H
