#ifndef AST_H
#define AST_H

#include "token.h"
#include "lexer.h"
#include "symboltable.h"
#include <QDebug>
#include "errorhandler.h"

class Node {
public:
    Token m_op;
    uint level = 0;
    Node* m_left = nullptr, *m_right = nullptr;
    virtual PVar Execute(SymbolTable* symTab, uint lvl) = 0;
    virtual void ExecuteSym(SymbolTable* symTab) = 0;
};




class NodeBinOP : public Node {
public:
    NodeBinOP(Node* left, Token op, Node* right) {
        m_right = right;
        m_left = left;
        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;

        ErrorHandler::e.DebugLow("Calling BinOP",level);

        if (m_op.m_type==TokenType::PLUS)
            return m_left->Execute(symTab, level) + m_right->Execute(symTab, level);
        if (m_op.m_type==TokenType::MINUS)
            return m_left->Execute(symTab, level) - m_right->Execute(symTab, level);

        if (m_op.m_type==TokenType::DIV)
           return m_left->Execute(symTab, level) / m_right->Execute(symTab, level);
        if (m_op.m_type==TokenType::MUL)
           return m_left->Execute(symTab, level) * m_right->Execute(symTab, level);
        return PVar();
    }
    void ExecuteSym(SymbolTable* symTab) override {
        m_left->ExecuteSym(symTab);
        m_right->ExecuteSym(symTab);
    }

};

class NodeNumber : public Node {
public:
    float m_val;
    NodeNumber(Token op, int val) {
        m_op = op;
        m_val = val;
    }
    PVar  Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl +1;
        return PVar(m_val);
    }
    void ExecuteSym(SymbolTable* symTab) override {
    }
};
class NodeString : public Node {
public:
    QString m_val;
    NodeString(Token op, QString val) {
        m_op = op;
        m_val = val;
    }
    PVar  Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl +1;
        return PVar(m_val);
    }
    void ExecuteSym(SymbolTable* symTab) override {
    }
};

class UnaryOpNode : public Node {
public:
    UnaryOpNode(Token t, Node* right) {
        m_op = t;
        m_right = right;
        m_left = nullptr;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Unary Op Node",level);

        if (m_op.m_type==TokenType::PLUS)
            return m_right->Execute(symTab, level)*1;
        if (m_op.m_type==TokenType::MINUS)
            return m_right->Execute(symTab, level)*-1;
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        m_right->ExecuteSym(symTab);
    }

};

class Compound : public Node {
public:
    QVector<Node*> children;
    Compound() {
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        for (Node* n: children)
            n->Execute(symTab, level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        for (Node* n:children) {
            ErrorHandler::e.DebugLow("Calling Compound Node",level);
            n->ExecuteSym(symTab);
        }
    }


};
class Var : public Node {
public:
    QString value;
    Var(Token t) {
        m_op = t;
        value = t.m_value;
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Var Node",level);

        if (symTab->Lookup(value)==nullptr) {
            ErrorHandler::e.Error("Error: Could not find variable '" +value +"'");
        }
        PVar v = *symTab->Lookup(value)->m_value;
       return v;

    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = m_op.m_value;
        Symbol* varSymbol = symTab->Lookup(varName);

    }

};

class NoOp : public Node {
    public:
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        return PVar();
    }
    void ExecuteSym(SymbolTable* symTab) override {

    }
};

class Assign : public Node {
public:
    Assign(Node* left, Token t, Node* r) {
        m_right = r;
        m_op = t;
        m_left = left;
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        ErrorHandler::e.DebugLow("Calling Assign",level);
        level = lvl+1;

        QString varName = ((Var*)m_left)->value;
        ErrorHandler::e.DebugHigh("Defining new variable : " + varName,level);
        Symbol* s = symTab->Lookup(varName);
        s->m_value = new PVar(m_right->Execute(symTab, level));

        //Syntax::s.globals[varName] = new PVar(m_right->Execute(symTab, level));
        //symTab->Define(new Symbol new PVar(m_right->Execute(symTab, level));
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString varName = ((Var*)m_left)->value;
        Symbol* varSymbol = symTab->Lookup(varName);
        m_right->ExecuteSym(symTab);

    }


};
class VarDecl : public Node {
public:
    Node* m_varNode = nullptr;
    Node* m_typeNode;
    VarDecl(Node* varNode, Node* typeNode) {
        m_varNode = varNode;
        m_typeNode = typeNode;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling VarDecl",level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString typeName = ((Var*)m_typeNode)->value;
        Symbol* typeSymbol = symTab->Lookup(typeName);
        QString varName = ((Var*)m_varNode)->value;
        ErrorHandler::e.DebugLow("Typename define : " + typeName + "  variable " + varName);

        Symbol* varSymbol = new VarSymbol(varName, typeSymbol->m_name);
        symTab->Define(varSymbol);
    }


};



class BlockNode : public Node {
public:
    QVector<Node*> m_decl;
    Node* m_compoundStatement;
    SymbolTable* m_symTab = nullptr;
    bool m_useOwnSymTab;
    BlockNode(QVector<Node*> decl, Node* comp, bool useOwnSymTab = true) {
        m_compoundStatement = comp;
        m_decl = decl;
        m_useOwnSymTab = useOwnSymTab;
    }

    void SetParameter(QString name, PVar var) {
        Symbol* s = m_symTab->Lookup(name);
        s->m_value = new PVar(var);
    }


    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling BlockNode",level);

        for (Node* n: m_decl)
            n->Execute(m_symTab, level);
        ErrorHandler::e.DebugLow("Calling Compound" ,level);
        m_compoundStatement->Execute(m_symTab, level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        if (m_useOwnSymTab) {
          if (m_symTab == nullptr)
              m_symTab = new SymbolTable();
        }
        else m_symTab = symTab;

        for (Node* n: m_decl)
        {
            n->ExecuteSym(m_symTab);
        }
        m_compoundStatement->ExecuteSym(m_symTab);
    }


};

class ProgramNode : public Node {
public:
    QString m_name;
    BlockNode* m_BlockNode;
    ProgramNode(QString n, BlockNode* b) {
        m_BlockNode = b;
        m_name = n;
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Program Node",level);

        m_BlockNode->Execute(symTab, level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        m_BlockNode->ExecuteSym(symTab);
    }

};
class VarType : public Node {
public:
    QString value;
    VarType(Token t) {
        m_op = t;
        value = t.m_value;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Vartype",level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {

    }

};

class ProcedureDecl : public Node {
public:
    QString m_procName;
    QVector<Node*> m_paramDecl;
    Node* m_block;

    ProcedureDecl(QString m, QVector<Node*> paramDecl, Node* block) {
        m_procName = m;
        m_block = block;
        m_paramDecl = paramDecl;
        BlockNode* b = (BlockNode*)block;
        for (int i=0;i<m_paramDecl.count();i++)
            b->m_decl.append(m_paramDecl[i]);

    }


    void SetParametersValue(QVector<Node*>& lst, SymbolTable* symTab) {
        if (lst.count()!=m_paramDecl.count())
            ErrorHandler::e.Error("Incorrect number of parameters calling procedure '" + m_procName +"'");

        for (int i=0;i<m_paramDecl.count();i++) {
            VarDecl* vd = (VarDecl*)m_paramDecl[i];
            Var* v= ((Var*)vd->m_varNode);
            QString name = v->value;
            PVar val = lst[i]->Execute(symTab,level);
            qDebug() << "Setting : " << name << " with value " << val.toString();
            ((BlockNode*)m_block)->SetParameter(name, val);

        }
//        ((BlockNode*)m_block)->SetParameters(lst, names);
    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling ProcedureDecl Node",level);

        if (m_block!=nullptr) {
            SetParametersValue(m_paramDecl, symTab);
            return m_block->Execute(symTab, level);
        }
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        m_block->ExecuteSym(symTab);
    }
};

class ConditionalNode : public Node {
public:

    Node* m_a, *m_b;
    Node* m_block;


    ConditionalNode(Token op, Node* a, Node* b, Node* block) {
        m_a = a;
        m_b = b;
        m_block = block;
        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Conditional Node",level);
        PVar a = m_a->Execute(symTab, level);
        PVar b = m_b->Execute(symTab, level);
        ErrorHandler::e.DebugHigh("Comparing " + a.toString() + " to " + b.toString() + " with comparator " +m_op.m_value ,level);

        if (m_op.m_type==TokenType::EQUALS)
            if (a==b)
                m_block->Execute(symTab, level);

        if (m_op.m_type==TokenType::NOTEQUALS)
            if (!(a==b))
                m_block->Execute(symTab, level);

        if (m_op.m_type==TokenType::GREATER)
            if ((a>b))
                m_block->Execute(symTab, level);

        if (m_op.m_type==TokenType::LESS)
            if ((a<b))
                m_block->Execute(symTab, level);

        return PVar();

    }

    void ExecuteSym(SymbolTable* symTab) override {
       m_block->ExecuteSym(symTab);
    }


};

class ForLoopNode : public Node {
public:

    Node* m_a, *m_b;
    Node* m_block;


    ForLoopNode(Node* a, Node* b, Node* block) {
        m_a = a;
        m_b = b;
        m_block = block;
//        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Forloop Node",level);
        PVar a = m_a->Execute(symTab, level);
        PVar b = m_b->Execute(symTab, level);

        Assign* avar = (Assign*)m_a;
        Var* var = (Var*)avar->m_left;

        float val = symTab->Lookup(var->value)->m_value->m_fVal;

        for (float i = val;i<=b.m_fVal;i++) {
            symTab->Lookup(var->value)->m_value->m_fVal = i;
            m_block->Execute(symTab, level);
        }

        return PVar();

    }

    void ExecuteSym(SymbolTable* symTab) override {
        m_block->ExecuteSym(symTab);
    }


};



class BuiltinMethod : public Node {
public:
    QString m_procName;
    Node* m_block = nullptr;
    Node* m_text = nullptr;
    BuiltinMethod(QString m, Node* text, Node* block) {
        m_procName = m;
        m_block = block;
        m_text = text;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        ErrorHandler::e.DebugLow("Calling Builtin",level);
        level = lvl+1;

        if (m_procName.toLower()=="writeln") {
            QString s = "";
            if (m_text!=nullptr)
                s+=m_text->Execute(symTab, level).toString();
            if (m_block!=nullptr)
                s+=m_block->Execute(symTab, level).toString();
            QTextStream out(stdout);
            out << s << endl;
        }
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {

    }
};




#endif // AST_H
