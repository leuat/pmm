#ifndef NODECOMPOUND_H
#define NODECOMPOUND_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeCompound : public Node {
public:
    QVector<Node*> children;
    NodeCompound(Token t) {
        m_op = t;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);

        level = lvl+1;
        for (Node* n: children)
            n->Execute(symTab, level);
        return PVar();

    }
    void Delete() override {
        for (Node* n: children) {
            n->Delete();
            delete n;
        }
        children.clear();
    }
    void ExecuteSym(SymbolTable* symTab) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        for (Node* n:children) {
            ErrorHandler::e.DebugLow("Calling Compound Node",level);
            n->ExecuteSym(symTab);
        }
    }

    QString Build(Assembler* as) {
        as->BeginBlock();
        for (Node* n: children)
            n->Build(as);
        as->EndBlock();
        return "";
    }

};
#endif // NODECOMPOUND_H
