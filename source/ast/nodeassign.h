#ifndef NODEASSIGN_H
#define NODEASSIGN_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"
#include "source/ast/nodevararray.h"


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

    QString AssignVariable(Assembler* as) {
        NodeVar* v = (NodeVar*)m_left;
        m_right->LoadVariable(as);
        //v->LoadVariable(as);
        as->Term("sta " + v->value,1);
        return v->value;
    }
    QString AssignVariableArray(Assembler* as) {
        NodeVarArray* v = (NodeVarArray*)m_left;
        m_right->Build(as);
        as->Term();
        v->StoreAcc(as);
        return ((NodeVar*)v->m_var)->value;
    }

    QString Build(Assembler* as) {
        if (dynamic_cast<NodeVar*>(m_left)!=nullptr) {
            return AssignVariable(as);

        }
        if (dynamic_cast<NodeVarArray*>(m_left)!=nullptr) {
            return AssignVariableArray(as);
        }

        ErrorHandler::e.Error("Unknown assignment type!");

        return "";
    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = ((NodeVar*)m_left)->value;
        Symbol* varSymbol = symTab->Lookup(varName);
        m_right->ExecuteSym(symTab);

    }


};

#endif // NODEASSIGN_H
