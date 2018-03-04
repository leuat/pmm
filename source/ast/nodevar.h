#ifndef NODEVAR_H
#define NODEVAR_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodenumber.h"

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
        // Optimizer: if expression is number, just return direct
        NodeNumber* number = dynamic_cast<NodeNumber*>(m_expr);
        if (number!=nullptr) { // IS NUMBER optimize}
            as->Asm("lda " + value + "+"+ QString::number(number->m_val));
        }
        else {
            as->ClearTerm();
            m_expr->Build(as);
            as->Term();
            as->Asm("tax");
            as->Asm("lda " + value+",x");
        }
    }

    void LoadVariable(Assembler* as) override {

        TokenType::Type t = as->m_symTab->Lookup(value)->getTokenType();
        qDebug() << value << " " << TokenType::getType(t);
        if (t==TokenType::ADDRESS) {
            LoadByteArray(as);
            return;
        }

        if (t==TokenType::BYTE) {
            if (m_expr!=nullptr)
                LoadByteArray(as);
            else {
                as->Asm("lda " +value);
            }
            return;
        }
        if (t == TokenType::INTEGER) {
            qDebug() << "ASSIGN INTEGER";
            as->Asm("Integer assignment in nodevar WTF");
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
            NodeNumber* number = dynamic_cast<NodeNumber*>(m_expr);
            if (number!=nullptr) { // IS NUMBER optimize}
                as->Asm("sta " + value + "+"+ QString::number(number->m_val));
            }
            else {
                as->Asm("tay");
                as->ClearTerm();
                m_expr->Build(as);
                as->Term();
                as->Asm("tax");
                as->Asm("tya");
                as->Asm("sta " + value+",x");
            }
            return;
        }
        else {
            if (as->m_symTab->Lookup(value)->getTokenType() == TokenType::BYTE) {
                as->Asm("sta " + value);
                return;
            }
            if (as->m_symTab->Lookup(value)->getTokenType() == TokenType::INTEGER) {
                qDebug() << "NodeVar::Storevariable integer";
                as->Asm("sta " + value);
                as->Asm("txa " );
                as->Asm("sta " + value + "+1");
                return;
            }

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
        Pmm::Data::d.lineNumber = m_op.m_lineNumber;
        Symbol* s = as->m_symTab->LookupVariables(value);
        if (s==nullptr) {
            ErrorHandler::e.Error("Could not find variable '" + value +"'.\nDid you mispell?", m_op.m_lineNumber);
        }
        if (m_expr!=nullptr) {
            as->ClearTerm();
            LoadByteArray(as);
        }
        else {
            bool isOK = true;
            as->Variable(val, isOK);
        }
        return val;
    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = m_op.m_value;
        Symbol* varSymbol = symTab->Lookup(varName);

    }

};

#endif // NODEVAR_H
