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
    Node* m_block;

    NodeProcedureDecl(QString m, QVector<Node*> paramDecl, Node* block);

    void Delete() override {
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
    }

    void SetParametersValue(QVector<PVar>& lst);

    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override;
};

#endif // NODEPROCEDUREDECL_H
