#include "nodeproceduredecl.h"
#include "nodebuiltinmethod.h"
#include "source/syntax.h"


NodeProcedureDecl::NodeProcedureDecl(QString m, QVector<Node *> paramDecl, Node *block) {
    m_procName = m;
    m_block = block;
    m_paramDecl = paramDecl;
    NodeBlock* b = (NodeBlock*)block;
    for (int i=0;i<m_paramDecl.count();i++)
        b->m_decl.append(m_paramDecl[i]);

}

void NodeProcedureDecl::SetParametersValue(QVector<PVar> &lst) {
    if (lst.count()!=m_paramDecl.count())
        ErrorHandler::e.Error("Incorrect number of parameters calling procedure '" +
                              m_procName +"'. Requires "+QString::number(m_paramDecl.count()) +
                              " parameters but is called with "+QString::number(lst.count()));

    for (int i=0;i<m_paramDecl.count();i++) {
        NodeVarDecl* vd = (NodeVarDecl*)m_paramDecl[i];
        NodeVar* v= ((NodeVar*)vd->m_varNode);
        QString name = v->value;
        PVar val = lst[i];
        ((NodeBlock*)m_block)->SetParameter(name, val);

    }
    //        ((NodeBlock*)m_block)->SetParameters(lst, names);
}

QString NodeProcedureDecl::Build(Assembler *as)
{
    if (m_block==nullptr)  // Is builtin procedure
        m_block = new NodeBuiltinMethod(m_procName, QVector<Node*>());

    bool isInitFunction=false;
    bool isBuiltinFunction=false;
    if (Syntax::s.builtInFunctions.contains(m_procName)) {
        isBuiltinFunction = true;
        isInitFunction = Syntax::s.builtInFunctions[m_procName].m_initFunction;
    }


    as->Asm("");
    as->Asm("");
    as->Comment("***********  Defining procedure : " + m_procName);
    QString type = (isBuiltinFunction) ? "Built-in function" : "User-defined procedure";
    as->Comment("   Procedure type : " + type);
    if (isBuiltinFunction) {
        type = (isInitFunction) ? "yes" : "no";
        as->Comment("   Requires initialization : " + type);
    }
    as->Asm("");


    if (!isInitFunction) {
        as->Asm("jmp afterProc_" + m_procName);


        as->Label(m_procName);
    }
    m_block->Build(as);
    if (!isInitFunction) {
        as->Asm("rts");
      as->Label("afterProc_" + m_procName);
    }
    return 0;
}

PVar NodeProcedureDecl::Execute(SymbolTable *symTab, uint lvl) {
    Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);

    level = lvl+1;
    ErrorHandler::e.DebugLow("Calling ProcedureDecl Node",level);

    if (m_block!=nullptr) {
        return m_block->Execute(symTab, level);
    }
    return PVar();

}

void NodeProcedureDecl::ExecuteSym(SymbolTable *symTab) {
    m_block->ExecuteSym(symTab);
}
