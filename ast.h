#ifndef AST_H
#define AST_H

#include "token.h"
#include "lexer.h"
#include <QDebug>

class Node {
public:
    Token m_op;
    bool m_isLeaf = false;
    Node* m_left = nullptr, *m_right = nullptr;

    virtual float Execute() = 0;
};




class NodeBinOP : public Node {
public:
    NodeBinOP(Node* left, Token op, Node* right) {
        m_right = right;
        m_left = left;
        m_op = op;
        m_isLeaf = false;
    }
    float Execute() override {
        if (m_op.m_type==TokenType::PLUS)
            return m_left->Execute() + m_right->Execute();
        if (m_op.m_type==TokenType::MINUS)
            return m_left->Execute() + m_right->Execute();

        if (m_op.m_type==TokenType::DIV)
            return m_left->Execute() / m_right->Execute();
        if (m_op.m_type==TokenType::MUL)
            return m_left->Execute() * m_right->Execute();
    }

};

class NodeNumber : public Node {
public:
    float m_val;
    NodeNumber(Token op, int val) {
        m_op = op;
        m_val = val;
        m_isLeaf = true;
    }
    float Execute() override {
        return m_val;
    }


};

class UnaryOpNode : public Node {
public:
    UnaryOpNode(Token t, Node* right) {
        m_op = t;
        m_right = right;
        m_left = nullptr;
    }
    float Execute() override {
        if (m_op.m_type==TokenType::PLUS)
            return +m_right->Execute();
        if (m_op.m_type==TokenType::MINUS)
            return -m_right->Execute();
    }

};

class Compound : public Node {
public:
    QVector<Node*> children;
    Compound() {
    }
    float Execute() override {
        for (Node* n: children)
            n->Execute();
    }

};
class Var : public Node {
public:
    QString value;
    Var(Token t) {
        m_op = t;
        value = t.m_value;
    }

    float Execute() override {
        if (!Syntax::s.globals.contains(value)) {
            qDebug() << "Error: Could not find variable '" << value <<"'";
            exit(1);
        }

       return Syntax::s.globals[value];

    }
};

class NoOp : public Node {
    public:
    float Execute() override {
        return 0;
    }
};

class Assign : public Node {
public:
    Assign(Node* left, Token t, Node* r) {
        m_right = r;
        m_op = t;
        m_left = left;
    }

    float Execute() override {
        QString varName = ((Var*)m_left)->value;
        Syntax::s.globals[varName] = m_right->Execute();
    }

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

};


class AST
{
public:
    AST();
};

#endif // AST_H
