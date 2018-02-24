#include "ast.h"

AST::AST()
{

}

Parser::Parser()
{

}

SymbolTable Node::m_symTab;

void Parser::Eat(TokenType::Type t)
{
    if (m_currentToken.m_type == t) {
        m_currentToken = m_lexer.GetNextToken();
    }
    else
        Error("Parser::Eat : Could not find token type '" + QString::number(t) + "'" + "with current "+QString::number(m_currentToken.m_type));
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
//    Node* n = CompoundStatement();
    Eat(TokenType::PROGRAM);
    Var* varNode = (Var*)Variable();
    QString progName = varNode->value;
    qDebug() << "Program name" << progName;
    Eat(TokenType::SEMI);
    BlockNode* block = (BlockNode*)Block();
    ProgramNode* program = new ProgramNode(progName, block);
    Eat(TokenType::DOT);

    return program;
}



Node* Parser::Factor()
{
    Token t = m_currentToken;
    if (t.m_type == TokenType::INTEGER_CONST || t.m_type ==TokenType::REAL_CONST) {
        Eat(t.m_type);
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

    root->ExecuteSym();
    return root;
}

Node *Parser::Block()
{
    return new BlockNode(Declarations(), CompoundStatement());
}

QVector<Node*> Parser::Declarations()
{
    QVector<Node*> decl;
    if (m_currentToken.m_type==TokenType::VAR) {
        Eat(TokenType::VAR);
        while (m_currentToken.m_type==TokenType::ID) {
            QVector<Node*> ns = VariableDeclarations();
            for (Node* n: ns)
                decl.append(n);
            Eat(TokenType::SEMI);
        }
    }
    return decl;
}

QVector<Node *> Parser::VariableDeclarations()
{
    QVector<Node*> vars;
    vars.append(new Var(m_currentToken));
    qDebug() << "   Adding new " << m_currentToken.m_value;
    Eat(TokenType::ID);

    while (m_currentToken.m_type == TokenType::COMMA) {
        Eat(TokenType::COMMA);
        qDebug() << "   Adding new " << m_currentToken.m_value;
        vars.append(new Var(m_currentToken));
        Eat(TokenType::ID);
    }
    Eat(TokenType::COLON);

    Node* typeNode = TypeSpec();



/*    for (Node* v: vars) {
        Syntax::s.globals[((Var*)v)->value] = 0;
    }*/

    QVector<Node*> var_decleratons;

//    vars.insert(0, VarDecl(varN));
    for (Node* n : vars) {
        qDebug() << "Value: " << ((Var*)n)->value;
        var_decleratons.append(new VarDecl(n, typeNode));
    }

//    return vars;
    return var_decleratons;
}

Node *Parser::TypeSpec()
{
    Token t = m_currentToken;
    if (m_currentToken.m_type == TokenType::INTEGER) {
        Eat(TokenType::INTEGER);
    }
    else
        Eat(TokenType::REAL);

    qDebug() << "Returning crap";

    return new VarType(t);

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

