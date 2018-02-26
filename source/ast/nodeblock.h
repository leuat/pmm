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
    Node* m_compoundStatement;
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


    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void ExecuteSym(SymbolTable* symTab) override;


};

#endif // NODEBLOCK_H
