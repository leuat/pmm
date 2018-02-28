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
    bool m_isWhileLoop;


    NodeConditional(Token op, Node* a, Node* b, Node* block, bool isWhile) {
        m_a = a;
        m_b = b;
        m_block = block;
        m_op = op;
        m_isWhileLoop = isWhile;
    }
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

    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void ExecuteSym(SymbolTable* symTab) override {
       m_block->ExecuteSym(symTab);
    }

    QString Build(Assembler *as) override;

};

#endif // NODECONDITIONAL_H
