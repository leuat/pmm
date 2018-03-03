#ifndef NODEVARARRAY_H
#define NODEVARARRAY_H

#include "node.h"
#include "source/symboltable.h"
#include "nodeVar.h"

class NodeVarArray : public Node
{
public:
    NodeVar* m_var;
    Node* m_expr;

    NodeVarArray();

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        return PVar();
    }

    QString Build(Assembler *as) override {
        m_expr->Build(as);
        as->Asm("tax");
        as->Term("lda ");
        m_var->Build(as);
        as->Term(",x",true);
        return "";
    }

    void StoreAcc(Assembler* as) {
        as->Asm("tay");
        m_expr->Build(as);
        as->Asm("tax");
        as->Asm("tya");
        as->Term("sta ");
        m_var->Build(as);
        as->Term(",x",true);



    }


    void ExecuteSym(SymbolTable* symTab) {
        m_var->ExecuteSym(symTab);
        m_expr->ExecuteSym(symTab);

    }


};

#endif // NODEVARARRAY_H
