#ifndef NODEVARDECL_H
#define NODEVARDECL_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"
#include "source/ast/nodevartype.h"

class NodeVarDecl : public Node {
public:
    Node* m_varNode = nullptr;
    Node* m_typeNode;
    NodeVarDecl(Node* varNode, Node* typeNode) {
        m_varNode = varNode;
        m_typeNode = typeNode;
    }

    void Delete() override {
        if (m_varNode) {
            m_varNode->Delete();
            delete m_varNode;
        }
        if (m_typeNode) {
            m_typeNode->Delete();
            delete m_typeNode;
        }

    }

    QString Build(Assembler* as) {

        ExecuteSym(as->m_symTab);

        NodeVar* v = (NodeVar*)m_varNode;
        NodeVarType* t = (NodeVarType*)m_typeNode;
        if (t->m_op.m_type==TokenType::ARRAY) {
            as->DeclareArray(v->value, t->m_arrayVarType.m_value, t->m_op.m_intVal, t->m_data);
        }
        else
            if (t->m_op.m_type==TokenType::INCBIN) {
                if (t->m_position=="") {
                    as->Label(v->value);
                    as->Asm("incbin \"" + t->m_filename + "\"");
                }
                else {
                    as->Appendix("org " +t->m_position,1);
                    as->Appendix(v->value,0);
                    as->Appendix("incbin \"" + t->m_filename + "\"",1);
                }
            }
            else
                as->DeclareVariable(v->value, t->value);
        return "";
    }


    PVar Execute(SymbolTable* symTab, uint lvl) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling VarDecl",level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {

        QString typeName = ((NodeVar*)m_typeNode)->value;
        Symbol* typeSymbol = symTab->Lookup(typeName);
        if (typeSymbol==nullptr)
            ErrorHandler::e.Error("Could not find type symbol :" + typeName,m_op.m_lineNumber);

        QString varName = ((NodeVar*)m_varNode)->value;
        ErrorHandler::e.DebugLow("Typename define : " + typeName + "  variable " + varName);

        Symbol* varSymbol = new VarSymbol(varName, typeSymbol->m_name);
        symTab->Define(varSymbol);

    }


};



#endif // NODEVARDECL_H
