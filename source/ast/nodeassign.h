#ifndef NODEASSIGN_H
#define NODEASSIGN_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"
#include "source/ast/nodestring.h"
#include "source/ast/nodevararray.h"


class NodeAssign : public Node {
public:
    Node* m_arrayIndex = nullptr;
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
    void AssignString(Assembler *as) {

        NodeString* right = (NodeString*)dynamic_cast<const NodeString*>(m_right);
        NodeVar* left = (NodeVar*)dynamic_cast<const NodeVar*>(m_left);
        QString lbl = as->NewLabel("stringassign");
        QString str = as->NewLabel("stringassignstr");
        QString lblCpy=as->NewLabel("stringassigncpy");
        as->Asm("jmp " + lbl);
        as->Label(str + "\t.dc \"" + right->m_op.m_value + "\",0");
        as->Label(lbl);
        as->Asm("ldx #0");
        as->Label(lblCpy);
        as->Asm("lda " + str+",x");
        as->Asm("sta "+left->value +",x");
        as->Asm("inx");
        as->Asm("cmp #0");
        as->Asm("bne " + lblCpy);

        as->PopLabel("stringassign");
        as->PopLabel("stringassignstr");
        as->PopLabel("stringassigncpy");

    }

    void AssignPointer(Assembler* as) {
        NodeVar* bVar = dynamic_cast<NodeVar*>(m_right);
        NodeNumber* bNum = dynamic_cast<NodeNumber*>(m_right);
        NodeVar* aVar = dynamic_cast<NodeVar*>(m_left);

        if (bVar==nullptr && bNum== nullptr)
            ErrorHandler::e.Error("Error assigning pointer: right-hand must be variable or number");

        if (bVar!=nullptr) {

            if (bVar->getType(as)!=TokenType::POINTER) {
                as->Asm("lda #<" + bVar->value);
                as->Asm("ldx #>" + bVar->value);
                as->Asm("sta " + aVar->value);
                as->Asm("stx "+ aVar->value+"+1");
            }
            else
            {
                as->Asm("lda " + bVar->value);
                as->Asm("ldx " + bVar->value + "+1");
                as->Asm("sta " + aVar->value);
                as->Asm("stx "+ aVar->value+"+1");
            }
        }
        if (bNum!=nullptr) {
            as->Asm("lda #" + QString::number(((int)bNum->m_val) & 255));
            as->Asm("ldx #" + QString::number(((int)(bNum->m_val)>>8) & 255) );
            as->Asm("sta " + aVar->value);
            as->Asm("stx "+ aVar->value+"+1");
        }
    }

    QString AssignVariable(Assembler* as) {
        NodeVar* v = (NodeVar*)dynamic_cast<const NodeVar*>(m_left);
        if (v==nullptr)
           ErrorHandler::e.Error("Left value not variable! ");

        as->Comment("Assigning single variable : " + v->value);
        Symbol* s = as->m_symTab->Lookup(v->value);
        if (s==nullptr)
            ErrorHandler::e.Error("Could not find variable :" + v->value,m_op.m_lineNumber);

        TokenType::Type t = s->getTokenType();

        if (m_left->getType(as)==TokenType::POINTER && v->m_expr==nullptr) {
            AssignPointer(as);
            return v->value;
        }

       if ((NodeString*)dynamic_cast<const NodeString*>(m_right))
        {
            AssignString(as);
            return v->value;
        }
        if (m_right==nullptr)
            ErrorHandler::e.Error("Node assign: right hand must be expression", m_op.m_lineNumber);
        if (m_left->getType(as)==TokenType::INTEGER)
            as->Asm("ldy #0");
        m_right->Build(as);
        as->Term();
        v->StoreVariable(as);
        return v->value;
    }

    QString Build(Assembler* as) {
        return AssignVariable(as);

    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = ((NodeVar*)m_left)->value;
        Symbol* varSymbol = symTab->Lookup(varName);
        m_right->ExecuteSym(symTab);

    }


};

#endif // NODEASSIGN_H
