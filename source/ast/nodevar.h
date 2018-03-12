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
      //  if (m_op.m_type==TokenType::INTEGER)
       //     m_isWord = true;

    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        ErrorHandler::e.DebugLow("Calling Var Node",level);
        if (symTab->Lookup(value)==nullptr)
            ErrorHandler::e.Error("Could not find variable '" +value +"'.");

        if (symTab->Lookup(value)->m_value==nullptr)
            ErrorHandler::e.Error("Variable '" +value +"' not initialized before use.");


        PVar v = *symTab->Lookup(value)->m_value;
       return v;

    }


    TokenType::Type getType(Assembler* as) override {
        if (as->m_symTab->Lookup(value)!=nullptr)
            return as->m_symTab->Lookup(value)->getTokenType();
        return m_op.m_type;
    }

    void LoadByteArray(Assembler *as) {
        // Optimizer: if expression is number, just return direct
        as->Comment("Load Byte array");
        NodeNumber* number = dynamic_cast<NodeNumber*>(m_expr);
        if (number!=nullptr) { // IS NUMBER optimize}
            QString v = value + "+"+ QString::number(number->m_val);
            if (as->m_term=="")
                as->Asm("lda " + v);
            else as->Term(v);
        }
        else {
            QString m = as->m_term;

            as->ClearTerm();
            as->Asm("pha");
            m_expr->Build(as);
            as->Term();
            as->Asm("tax");
            as->Asm("pla");

            if (m=="")
                m="lda ";
            as->Asm(m+  value+",x");

        }
    }

    void LoadVariable(Assembler* as) override {

        if (as->m_symTab->Lookup(value)==nullptr)
            ErrorHandler::e.Error("Could not find variable '" +value +"' for storing.",m_op.m_lineNumber);

        TokenType::Type t = as->m_symTab->Lookup(value)->getTokenType();
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
            m_isWord = true;
            as->Comment("Integer assignment in nodevar");
            as->Asm("ldx " +value);
            as->Asm("lda " +value+"+1");
            return;
        }
        if (t == TokenType::POINTER) {
            LoadByteArray(as);
            return;
        }
        ErrorHandler::e.Error(TokenType::getType(t) + " assignment not supported yet for exp: " + value);
        return;
    }

    void StoreVariable(Assembler* as) override {
        as->Comment("VarNode StoreVariable");
        if (as->m_symTab->Lookup(value)==nullptr)
            ErrorHandler::e.Error("Could not find variable '" +value +"' for storing.", m_op.m_lineNumber);

        if (m_expr != nullptr) {
            NodeNumber* number = dynamic_cast<NodeNumber*>(m_expr);
            if (number!=nullptr) { // IS NUMBER optimize}
                as->Asm("sta " + value + "+"+ QString::number(number->m_val));
            }
            else {
                as->Asm("pha");
                as->ClearTerm();
                m_expr->Build(as);
                as->Term();
                as->Asm("tax");
                as->Asm("pla");
                as->Asm("sta " + value+",x");
            }
            return;
        }
        else {
            // Not array
            if (as->m_symTab->Lookup(value)->getTokenType() == TokenType::BYTE) {

                as->Asm("sta " + value);
                return;
            }
            if (as->m_symTab->Lookup(value)->getTokenType() == TokenType::INTEGER) {
                as->Asm("sta " + value);
                as->Asm("txa " );
                as->Asm("sta " + value + "+1");
                return;
            }

        }

    }

    QString Build(Assembler *as) override {
        QString  val = value;
        Pmm::Data::d.lineNumber = m_op.m_lineNumber;
        Symbol* s = as->m_symTab->LookupVariables(value);
        if (s==nullptr) {
            ErrorHandler::e.Error("Could not find variable '" + value +"'.\nDid you mispell?", m_op.m_lineNumber);
        }
        if (m_expr!=nullptr) {

            LoadByteArray(as);
        }
        else {
            bool isOK = true;
            if (s->getTokenType()==TokenType::INTEGER)
                isOK = false;
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
