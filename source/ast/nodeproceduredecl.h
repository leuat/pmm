#ifndef NODEPROCEDUREDECL_H
#define NODEPROCEDUREDECL_H

#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodeblock.h"
#include "source/ast/nodevardecl.h"

class NodeProcedureDecl : public Node {
public:
    QString m_procName;
    QVector<Node*> m_paramDecl;
    bool m_isInterrupt;
    Node* m_block = nullptr;


    NodeProcedureDecl(Token t, QString m) {
        m_op = t;
        m_procName = m;
        m_isInterrupt = false;
    }


    NodeProcedureDecl(Token t, QString m, QVector<Node*> paramDecl, Node* block, bool isInterrupt=false);

    void Delete() override {
        ErrorHandler::e.DebugLow("Memory: Deleting in NodeProcedureDecl", level);

        for (Node* n: m_paramDecl) {
            n->Delete();
            delete n;
        }
        m_paramDecl.clear();
        if (m_block) {
            m_block->Delete();
            delete m_block;
            m_block = nullptr;
        }
        ErrorHandler::e.DebugLow("Memory DONE: Deleting in NodeProcedureDecl", level);
    }

    void SetParametersValue(QVector<PVar>& lst);


    QString Build(Assembler* as) override;

    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override;
};

#endif // NODEPROCEDUREDECL_H
