#include "ast.h"

AST::AST()
{

}

Parser::Parser()
{

}

void Parser::Eat(TokenType::Type t)
{
    if (m_currentToken.m_type == t) {
        m_currentToken = m_lexer.GetNextToken();
    }
    else
        Error("Parser::Eat : Could not find token type '" + QString::number(t) + "'");
}

Node *Parser::Variable()
{
    Node* n = new Var(m_currentToken);
    Eat(TokenType::ID);
    return n;
}

Node *Parser::Empty()
{
    return new NoOp();
}

Node *Parser::AssignStatement()
{
    Node* left = Variable();
    Token token = m_currentToken;
    Eat(TokenType::ASSIGN);
    Node* right = Expr();
    Node* node = new Assign(left, token, right);
    return node;

}

Node *Parser::Statement()
{
    Node *node = nullptr;

    if (m_currentToken.m_type == TokenType::BEGIN)
        node = CompoundStatement();
    else if (m_currentToken.m_type == TokenType::ID)
        node = AssignStatement();
    else node = Empty();

    return node;


}

QVector<Node*> Parser::StatementList()
{
    Node* node = Statement();
    QVector<Node*> results;
    results.append(node);

    while (m_currentToken.m_type == TokenType::SEMI) {
        Eat(TokenType::SEMI);
        Node* n = Statement();
        results.append(n);

    }
    if (m_currentToken.m_type==TokenType::ID)
        Error("Parser::Statementlist : Token should not be ID");


    return results;

}

Node *Parser::CompoundStatement()
{
    Eat(TokenType::BEGIN);
    QVector<Node*> nodes = StatementList();
    Eat(TokenType::END);
    Compound* root = new Compound();
    for (Node* n: nodes)
        root->children.append(n);


    return root;

}

Node *Parser::Program()
{
    Node* n = CompoundStatement();
    Eat(TokenType::DOT);
    return n;
}



Node* Parser::Factor()
{
    Token t = m_currentToken;
    if (t.m_type == TokenType::INTEGER) {
        Eat(TokenType::INTEGER);
        return new NodeNumber(t, t.m_intVal);
    }

    if (t.m_type == TokenType::PLUS || t.m_type==TokenType::MINUS) {
        Eat(t.m_type);
        return new UnaryOpNode(t, Factor());
    }


    if (t.m_type == TokenType::LPAREN) {
        Eat(TokenType::LPAREN);
        Node* node = Expr();
        Eat(TokenType::RPAREN);
        return node;

    }
    //if (t.m_type == TokenType::ID)
       return Variable();
}

Node* Parser::Term()
{
    Node* node = Factor();
    while (m_currentToken.m_type == TokenType::Type::MUL || m_currentToken.m_type == TokenType::Type::DIV) {
        Token t = m_currentToken;
        Eat(m_currentToken.m_type);

        node = new NodeBinOP(node, t, Factor());

    }
    return node;
}

Node* Parser::Parse()
{
    Node* root = Program();
    if (m_currentToken.m_type!=TokenType::TEOF)
        Error("End of file error");

    return root;
}

Node* Parser::Expr()
{
    Node* node = Term();

    while (m_currentToken.m_type == TokenType::Type::PLUS || m_currentToken.m_type == TokenType::Type::MINUS) {
        Token t = m_currentToken;
        Eat(m_currentToken.m_type);

        node = new NodeBinOP(node, t, Term());

    }
    return node;
}

