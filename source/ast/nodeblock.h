#ifndef NODEBLOCK_H
#define NODEBLOCK_H



#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"
#include "source/ast/nodevardecl.h"


class NodeBlock : public Node {
public:
    QVector<Node*> m_decl;
    Node* m_compoundStatement = nullptr;
    SymbolTable* m_symTab = nullptr;
    bool m_useOwnSymTab;

    NodeBlock(Token t, QVector<Node*> decl, Node* comp, bool useOwnSymTab = true) {
        m_compoundStatement = comp;
        m_decl = decl;
        m_op = t;
        m_useOwnSymTab = useOwnSymTab;
    }

    void SetParameter(QString name, PVar var) {
        Symbol* s = m_symTab->Lookup(name);
        if (s==nullptr)
            ErrorHandler::e.Error("Could not find variable :" + name,m_op.m_lineNumber);

        s->m_value = new PVar(var);
    }
    void Delete() override {
        Node::Delete();
        if (m_useOwnSymTab && m_symTab!=nullptr) {
            m_symTab->Delete();
        }
        if (m_compoundStatement!=nullptr) {
            m_compoundStatement->Delete();
            m_compoundStatement = nullptr;
        }
        for (Node* n : m_decl) {
            n->Delete();
            delete n;
        }
        m_decl.clear();

    }

   QString Build(Assembler* as) {
       //as->VarDeclHeader();

       as->PushCounter();

       QString label = as->NewLabel("block");
       as->Asm("jmp " + label);
       bool blockLabel = false;
        for (Node* n: m_decl) {
            if (!blockLabel)
                if (dynamic_cast<NodeVarDecl*>(n)==nullptr) {
                    as->Label(label);
                    blockLabel = true;
                }
            n->Build(as);
        }
        as->VarDeclEnds();

        if (!blockLabel)
            as->Label(label);
        if (m_compoundStatement!=nullptr)
            m_compoundStatement->Build(as);


        as->PopCounter(m_op.m_lineNumber-1);

        //qDebug() << "Adding at linenumber: " << m_op.m_lineNumber << "  cycles " << m_cycleCounter;
        return "";

    }

    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void ExecuteSym(SymbolTable* symTab) override;


};

#endif // NODEBLOCK_H
