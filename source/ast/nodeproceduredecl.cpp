#include "nodeproceduredecl.h"


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

PVar NodeProcedureDecl::Execute(SymbolTable *symTab, uint lvl) {
    Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);

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
