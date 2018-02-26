#ifndef NODEPROCEDURE_H
#define NODEPROCEDURE_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodeproceduredecl.h"

class NodeProcedure : public Node {
public:
    NodeProcedureDecl* m_procedure;
    QVector<Node*> m_parameters;

    NodeProcedure(NodeProcedureDecl* proc, QVector<Node*> params ) {
        m_parameters = params;
        m_procedure = proc;
    }

    void Delete() {
        if (m_procedure) {
            //m_procedure->Delete();
            //delete m_procedure;
            //m_procedure = nullptr;
        }
        for (Node* n : m_parameters) {
            n->Delete();
            delete n;
        }
        m_parameters.clear();
    }

    PVar Execute(SymbolTable *symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
        m_procedure ->ExecuteSym(symTab);
    }

};


#endif // NODEPROCEDURE_H
