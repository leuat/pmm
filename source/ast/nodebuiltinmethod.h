#ifndef NODEBUILTINMETHOD_H
#define NODEBUILTINMETHOD_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeBuiltinMethod : public Node {
public:
    QString m_procName;
    QVector<Node*> m_params;
    NodeBuiltinMethod(QString m, QVector<Node*> params) {
        m_procName = m;
        m_params = params;
    }

    void Delete() override {
        for (Node* n: m_params) {
            n->Delete();
            delete n;
        }
    }

    QString Build(Assembler *as) override;

    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {

    }
};


#endif // NODEBUILTINMETHOD_H
