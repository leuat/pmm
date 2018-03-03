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
    Node* m_expr = nullptr;


    NodeVar(Token t) {
        m_op = t;
        value = t.m_value;
    }

    NodeVar(Token t, Node* expr) {
        m_op = t;
        value = t.m_value;
        m_expr = expr;
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

    void LoadByteArray(Assembler *as) {
        as->ClearTerm();
        m_expr->Build(as);
        as->Term();
        as->Asm("tax");
        as->Asm("lda " + value+",x");
    }

    void LoadVariable(Assembler* as) override {

        TokenType::Type t = as->m_symTab->Lookup(value)->getTokenType();

        if (t==TokenType::ADDRESS) {
            LoadByteArray(as);
            return;
        }

        if (t==TokenType::BYTE) {
            if (m_expr!=nullptr)
                LoadByteArray(as);
            else
                as->Asm("lda " +value);
            return;
        }
        if (t == TokenType::INTEGER) {
            as->Asm("lda " +value);
            as->Asm("tax");
            as->Asm("lda " +value+"+1");
            return;

        }
        ErrorHandler::e.Error(TokenType::getType(t) + " assignment not supported yet for exp: " + value);
        return;
    }

    void StoreVariable(Assembler* as) {
        if (m_expr != nullptr) {
            as->Asm("tay");
            as->ClearTerm();
            m_expr->Build(as);
            as->Term();
            as->Asm("tax");
            as->Asm("tya");
            as->Asm("sta " + value+",x");
            return;
        }
        else {
            as->Asm("sta " + value);

        }

    }

    QString Build(Assembler *as) override {
        QString  val = value;
      /*  Symbol* s= as->m_symTab->LookupConstants(value);
        if (s!=nullptr) {
            val = "$" + QString::number((int)s->m_value->m_fVal,16);
            if (!(s->m_type.toLower()=="address"))
                val = "#" + val;
        }
        if (s==nullptr) {*/

        Symbol* s = as->m_symTab->LookupVariables(value);
        if (s==nullptr) {
            ErrorHandler::e.Error("Could not find variable '" + value +"'.\nDid you mispell?");
        }
        if (m_expr!=nullptr) {
            as->ClearTerm();
            LoadByteArray(as);
        }
        else

        as->Variable(val);
        return val;
    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = m_op.m_value;
        Symbol* varSymbol = symTab->Lookup(varName);

    }

};

#endif // NODEVAR_H
