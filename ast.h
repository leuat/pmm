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
    static SymbolTable m_symTab;
    virtual PVar Execute(uint lvl) = 0;
    virtual void ExecuteSym() = 0;
};




class NodeBinOP : public Node {
public:
    NodeBinOP(Node* left, Token op, Node* right) {
        m_right = right;
        m_left = left;
        m_op = op;
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;

        ErrorHandler::e.DebugLow("Calling BinOP",level);

        if (m_op.m_type==TokenType::PLUS)
            return m_left->Execute(level) + m_right->Execute(level);
        if (m_op.m_type==TokenType::MINUS)
            return m_left->Execute(level) - m_right->Execute(level);

        if (m_op.m_type==TokenType::DIV)
           return m_left->Execute(level) / m_right->Execute(level);
        if (m_op.m_type==TokenType::MUL)
           return m_left->Execute(level) * m_right->Execute(level);
        return PVar();
    }
    void ExecuteSym() override {
        m_left->ExecuteSym();
        m_right->ExecuteSym();
    }

};

class NodeNumber : public Node {
public:
    float m_val;
    NodeNumber(Token op, int val) {
        m_op = op;
        m_val = val;
    }
    PVar  Execute(uint lvl) override {
        level = lvl +1;
        return PVar(m_val);
    }
    void ExecuteSym() override {
    }
};
class NodeString : public Node {
public:
    QString m_val;
    NodeString(Token op, QString val) {
        m_op = op;
        m_val = val;
    }
    PVar  Execute(uint lvl) override {
        level = lvl +1;
        return PVar(m_val);
    }
    void ExecuteSym() override {
    }
};

class UnaryOpNode : public Node {
public:
    UnaryOpNode(Token t, Node* right) {
        m_op = t;
        m_right = right;
        m_left = nullptr;
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Unary Op Node",level);

        if (m_op.m_type==TokenType::PLUS)
            return m_right->Execute(level)*1;
        if (m_op.m_type==TokenType::MINUS)
            return m_right->Execute(level)*-1;
        return PVar();

    }
    void ExecuteSym() override {
        m_right->ExecuteSym();
    }

};

class Compound : public Node {
public:
    QVector<Node*> children;
    Compound() {
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;
        for (Node* n: children)
            n->Execute(level);
        return PVar();

    }
    void ExecuteSym() override {
        for (Node* n:children) {
            ErrorHandler::e.DebugLow("Calling Compound Node",level);
            n->ExecuteSym();
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

    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Var Node",level);

        if (!Syntax::s.globals.contains(value)) {
            ErrorHandler::e.Error("Error: Could not find variable '" +value +"'");
        }
        PVar v = *Syntax::s.globals[value];
       return v;

    }
    void ExecuteSym() override {
        QString varName = m_op.m_value;
        Symbol* varSymbol = m_symTab.Lookup(varName);

    }

};

class NoOp : public Node {
    public:
    PVar Execute(uint lvl) override {
        level = lvl+1;
        return PVar();
    }
    void ExecuteSym() override {

    }
};

class Assign : public Node {
public:
    Assign(Node* left, Token t, Node* r) {
        m_right = r;
        m_op = t;
        m_left = left;
    }

    PVar Execute(uint lvl) override {
        ErrorHandler::e.DebugLow("Calling Assign",level);
        level = lvl+1;

        QString varName = ((Var*)m_left)->value;
        ErrorHandler::e.DebugHigh("Defining new variable : " + varName,level);
        Syntax::s.globals[varName] = new PVar(m_right->Execute(level));
        return PVar();

    }
    void ExecuteSym() override {
        QString varName = ((Var*)m_left)->value;
        Symbol* varSymbol = m_symTab.Lookup(varName);
        m_right->ExecuteSym();

    }


};


class BlockNode : public Node {
public:
    QVector<Node*> m_decl;
    Node* m_compoundStatement;
    BlockNode(QVector<Node*> decl, Node* comp) {
        m_compoundStatement = comp;
        m_decl = decl;
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling BlockNode",level);

        for (Node* n: m_decl)
            n->Execute(level);
        ErrorHandler::e.DebugLow("Calling Compound" ,level);
        m_compoundStatement->Execute(level);
        return PVar();

    }
    void ExecuteSym() override {
        for (Node* n: m_decl)
        //for (int i=m_decl.count()-1;i>=0;i--)
        {
            //Node* n = m_decl[i];
            //qDebug() << "Executing BlockNode::nodes " << n->m_op.m_value;
            //if (dynamic_cast<const Var*>(n) != nullptr)
            //    qDebug() << "Is Var!";
            //if (dynamic_cast<const BlockNode*>(n) != nullptr)
            //    qDebug() << "Is BlockNode!";
            n->ExecuteSym();

        }
        m_compoundStatement->ExecuteSym();
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

    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Program Node",level);

        m_BlockNode->Execute(level);
        return PVar();

    }
    void ExecuteSym() override {
        m_BlockNode->ExecuteSym();
    }

};
class VarType : public Node {
public:
    QString value;
    VarType(Token t) {
        m_op = t;
        value = t.m_value;
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Vartype",level);
        return PVar();

    }
    void ExecuteSym() override {

    }

};

class VarDecl : public Node {
public:
    Node* m_varNode;
    Node* m_typeNode;
    VarDecl(Node* varNode, Node* typeNode) {
        m_varNode = varNode;
        m_typeNode = typeNode;
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling VarDecl",level);
        return PVar();

    }
    void ExecuteSym() override {
        QString typeName = ((Var*)m_typeNode)->value;
        Symbol* typeSymbol = m_symTab.Lookup(typeName);
        QString varName = ((Var*)m_varNode)->value;
        Symbol* varSymbol = new VarSymbol(varName, typeSymbol->m_name);
        m_symTab.Define(varSymbol);
    }


};

class ProcedureDecl : public Node {
public:
    QString m_procName;
    Node* m_block;
    ProcedureDecl(QString m, Node* block) {
        m_procName = m;
        m_block = block;
    }
    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling ProcedureDecl Node",level);
        return PVar();

    }
    void ExecuteSym() override {

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
    PVar Execute(uint lvl) override {
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Conditional Node",level);
        PVar a = m_a->Execute(level);
        PVar b = m_b->Execute(level);
        ErrorHandler::e.DebugHigh("Comparing " + a.toString() + " to " + b.toString() + " with comparator " +m_op.m_value ,level);

        if (m_op.m_type==TokenType::EQUALS)
            if (a==b)
                m_block->Execute(level);

        if (m_op.m_type==TokenType::NOTEQUALS)
            if (!(a==b))
                m_block->Execute(level);

        if (m_op.m_type==TokenType::GREATER)
            if ((a>b))
                m_block->Execute(level);

        if (m_op.m_type==TokenType::LESS)
            if ((a<b))
                m_block->Execute(level);

        return PVar();

    }

    void ExecuteSym() override {

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
    PVar Execute(uint lvl) override {
        ErrorHandler::e.DebugLow("Calling Builtin",level);
        level = lvl+1;

        if (m_procName.toLower()=="writeln") {
            QString s = "";
            if (m_text!=nullptr)
                s+=m_text->Execute(level).toString();
            if (m_block!=nullptr)
                s+=m_block->Execute(level).toString();
            QTextStream out(stdout);
            out << s << endl;
        }
        return PVar();

    }
    void ExecuteSym() override {

    }
};

class SymbolTableBuilder {
public:
    SymbolTable m_symTab;

};


class Parser {
public:
    Lexer m_lexer;
    Token m_currentToken;
    Parser();
    Parser(Lexer l) {
        m_lexer = l;
        m_currentToken = m_lexer.GetNextToken();
    }
    void Error(QString s) {
        qDebug() << "Invalid syntax on line " << m_lexer.m_lineNumber << " : " <<s;
        m_lexer.Error("Parser error: ");
        exit(1);
    }

    void Eat(TokenType::Type t);

    Node* Variable();
    Node* Empty();
    Node* AssignStatement();
    Node* Statement();
    QVector<Node*> StatementList();
    Node* CompoundStatement();
    Node* Program();
    Node* Factor();
    Node* Expr();
    Node* Term();
    Node* Parse();
    Node* Block();
    Node* String();
    Node* Conditional();
//    QVector<Node*> Procedure();
    QVector<Node*> Declarations();
    QVector<Node*> VariableDeclarations();
    Node* ExecuteInternalFunction(TokenType::Type t, Node* text, Node* block);
    Node* TypeSpec();


};


class AST
{
public:
    AST();
};

#endif // AST_H
