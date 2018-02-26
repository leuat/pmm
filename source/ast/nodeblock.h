#ifndef NODEBLOCK_H
#define NODEBLOCK_H



#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"


class NodeBlock : public Node {
public:
    QVector<Node*> m_decl;
    Node* m_compoundStatement = nullptr;
    SymbolTable* m_symTab = nullptr;
    bool m_useOwnSymTab;

    NodeBlock(QVector<Node*> decl, Node* comp, bool useOwnSymTab = true) {
        m_compoundStatement = comp;
        m_decl = decl;
        m_useOwnSymTab = useOwnSymTab;
    }

    void SetParameter(QString name, PVar var) {
        Symbol* s = m_symTab->Lookup(name);
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

    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void ExecuteSym(SymbolTable* symTab) override;


};

#endif // NODEBLOCK_H
