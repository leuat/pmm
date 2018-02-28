#ifndef NODEASSIGN_H
#define NODEASSIGN_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"


class NodeAssign : public Node {
public:
    NodeAssign(Node* left, Token t, Node* r) {
        m_right = r;
        m_op = t;
        m_left = left;
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        ErrorHandler::e.DebugLow("Calling Assign",level);
        level = lvl+1;

        QString varName = ((NodeVar*)m_left)->value;
        ErrorHandler::e.DebugHigh("Defining new variable : " + varName,level);
        Symbol* s = symTab->Lookup(varName);
        s->m_value = new PVar(m_right->Execute(symTab, level));

        //Syntax::s.globals[varName] = new PVar(m_right->Execute(symTab, level));
        //symTab->Define(new Symbol new PVar(m_right->Execute(symTab, level));
        return *s->m_value;

    }
    QString Build(Assembler* as) {
        NodeVar* v = (NodeVar*)m_left;
        as->ClearTerm();

        //m_right->Build(as);
        //as->EndAssignVariable(v->value);
        //as->ApplyTerm();
        as->ClearTerm();
        as->Term("lda ");
        m_right->Build(as);
        as->Term();
        as->Term("sta " + v->value,1);

        return v->value;

    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = ((NodeVar*)m_left)->value;
        Symbol* varSymbol = symTab->Lookup(varName);
        m_right->ExecuteSym(symTab);

    }


};

#endif // NODEASSIGN_H
