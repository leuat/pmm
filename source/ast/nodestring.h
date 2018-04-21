#ifndef NODESTRING_H
#define NODESTRING_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeString : public Node {
public:
    QStringList m_val;
    NodeString(Token op, QStringList val) {
        m_op = op;
        m_val = val;
    }
    PVar  Execute(SymbolTable* symTab, uint lvl) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        level = lvl +1;
        return PVar();
    }

    QString Build(Assembler *as) override {
       Node::Build(as);

       as->String(m_val);
       return "";
    }

    void ExecuteSym(SymbolTable* symTab) override {
    }
};

#endif // NODESTRING_H
