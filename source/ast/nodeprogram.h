#ifndef NODEPROGRAM_H
#define NODEPROGRAM_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

#include "source/ast/nodeblock.h"

class NodeProgram : public Node {
public:
    QString m_name;
    NodeBlock* m_NodeBlock;
    NodeProgram(QString n, NodeBlock* b) {
        m_NodeBlock = b;
        m_name = n;
    }

    void Delete() override {
        if (m_NodeBlock) {
            m_NodeBlock->Delete();
            delete m_NodeBlock;
            m_NodeBlock = nullptr;
        }
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
        m_NodeBlock->ExecuteSym(symTab);
    }

};

#endif // NODEPROGRAM_H
