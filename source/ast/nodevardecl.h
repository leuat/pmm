#ifndef NODEVARDECL_H
#define NODEVARDECL_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"
#include "source/ast/nodevartype.h"
#include "source/misc/sidfile.h"

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


    void IncSid(Assembler* as) {
        NodeVar* v = (NodeVar*)m_varNode;
        NodeVarType* t = (NodeVarType*)m_typeNode;

        SidFile sid;
        sid.Load(t->m_filename, as->m_projectDir);
        sid.Convert();

        as->m_symTab->DefineSid(sid.m_initAddress, sid.m_playAddress);

        as->Appendix("org $" +QString::number(sid.m_loadAddress,16),1);
        as->Appendix(v->value,0);
        as->Appendix("incbin \"" + as->m_projectDir + sid.m_outFile + "\"",1);

    }

    void IncBin(Assembler* as) {
        NodeVar* v = (NodeVar*)m_varNode;
        NodeVarType* t = (NodeVarType*)m_typeNode;
        QString filename = as->m_projectDir + "/" + t->m_filename;
        if (!QFile::exists(filename))
            ErrorHandler::e.Error("Could not locate sid file for inclusion :" +filename);



        if (t->m_position=="") {
            as->Label(v->value);
            as->Asm("incbin \"" + filename + "\"");
        }
        else {
            as->Appendix("org " +t->m_position,1);
            as->Appendix(v->value,0);
            as->Appendix("incbin \"" + filename + "\"",1);
        }
    }



    QString Build(Assembler* as) {

        ExecuteSym(as->m_symTab);

        NodeVar* v = (NodeVar*)m_varNode;
        NodeVarType* t = (NodeVarType*)m_typeNode;
        if (t->m_op.m_type==TokenType::ARRAY) {
            qDebug() << "Declaring array: " <<v->value;
            as->DeclareArray(v->value, t->m_arrayVarType.m_value, t->m_op.m_intVal, t->m_data, t->m_position);
            //qDebug() << "IS: " << TokenType::types[as->m_symTab->Lookup(v->value)->getTokenType()];
            as->m_symTab->Lookup(v->value)->m_type="address";
        }
        else
            if (t->m_op.m_type==TokenType::INCBIN)
                IncBin(as);
            else if (t->m_op.m_type==TokenType::INCSID)
                IncSid(as);
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
        QString varName = ((NodeVar*)m_varNode)->value;
        if (symTab->Lookup(varName)!=nullptr)
                ErrorHandler::e.Error("Variable '" + varName +"' is already defined!",m_op.m_lineNumber);


        Symbol* typeSymbol = symTab->Lookup(typeName);
        if (typeSymbol==nullptr)
            ErrorHandler::e.Error("Could not find type symbol :" + typeName,m_op.m_lineNumber);

        ErrorHandler::e.DebugLow("Typename define : " + typeName + "  variable " + varName);




        Symbol* varSymbol = new VarSymbol(varName, typeSymbol->m_name);
        symTab->Define(varSymbol);

    }


};



#endif // NODEVARDECL_H
