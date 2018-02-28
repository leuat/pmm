#ifndef NODEVAR_H
#define NODEVAR_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeVar : public Node {
public:
    QString value;
    NodeVar(Token t) {
        m_op = t;
        value = t.m_value;
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        ErrorHandler::e.DebugLow("Calling Var Node",level);
        if (symTab->Lookup(value)==nullptr) {
            ErrorHandler::e.Error("Could not find variable '" +value +"'");
        }
        if (symTab->Lookup(value)->m_value==nullptr)
            ErrorHandler::e.Error("Variable '" +value +"' not initialized before use.");


        PVar v = *symTab->Lookup(value)->m_value;
       return v;

    }

    QString Build(Assembler *as) override {
        QString  val = value;
        Symbol* s= as->m_symTab->LookupConstants(value);
        if (s!=nullptr) {
            val = QString::number(s->m_value->m_fVal);
            if (!(s->m_type.toLower()=="address"))
                val = "#" + val;
        }
        if (s==nullptr) {
            s = as->m_symTab->LookupVariables(value);
            if (s==nullptr) {
                ErrorHandler::e.Error("Could not find variable '" + value +"'.\nDid you mispell?");
            }
        }

        as->Variable(val);
        return val;
    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = m_op.m_value;
        Symbol* varSymbol = symTab->Lookup(varName);

    }

};

#endif // NODEVAR_H
