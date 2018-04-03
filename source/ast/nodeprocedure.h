#ifndef NODEPROCEDURE_H
#define NODEPROCEDURE_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodeproceduredecl.h"
#include "source/ast/nodevar.h"

class NodeProcedure : public Node {
public:
    NodeProcedureDecl* m_procedure;
    QVector<Node*> m_parameters;

    NodeProcedure(NodeProcedureDecl* proc, QVector<Node*> params, Token t ) {
        m_parameters = params;
        m_procedure = proc;
        m_op = t;
    }

    void Delete() {
        ErrorHandler::e.DebugLow("Memory: Deleting in NodeProcedure", level);
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
        ErrorHandler::e.DebugLow("Memory DONE: Deleting in NodeProcedure", level);
    }


    QString Build(Assembler* as) override {
        Node::Build(as);

        if (m_parameters.count()!=m_procedure->m_paramDecl.count())
            ErrorHandler::e.Error("Procedure '" + m_procedure->m_procName+"' requires "
            + QString::number(m_procedure->m_paramDecl.count()) +" parameters, not "
            + QString::number(m_parameters.count()) + ".", m_op.m_lineNumber);

        for (int i=0; i<m_parameters.count();i++) {
            m_parameters[i]->LoadVariable(as);
            NodeVarDecl* vd = (NodeVarDecl*)m_procedure->m_paramDecl[i];
            vd->m_varNode->StoreVariable(as);
        }

        as->Asm("jsr " + m_procedure->m_procName);
        return "";
    }

    PVar Execute(SymbolTable *symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
        m_procedure ->ExecuteSym(symTab);
    }

};


#endif // NODEPROCEDURE_H
