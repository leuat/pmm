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
        //qDebug() << "Next token: " << m_currentToken.getType();
    }
    else
        Error("Parser::Eat : Could not find token type '" + TokenType::getType(t) + "'" + " with current "+m_currentToken.getType());
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
    if (m_currentToken.m_type == TokenType::BEGIN) {
        node = CompoundStatement();
    }
    else if (m_currentToken.m_type == TokenType::ID) {
        node = AssignStatement();
    }
    else if (m_currentToken.m_type==TokenType::WRITELN) {
        Eat(TokenType::WRITELN);
        Eat(TokenType::LPAREN);
        NodeString* text = (NodeString*)String();
        Eat(TokenType::STRING);
        Node* block = nullptr;

        if (m_currentToken.m_type==TokenType::COMMA) {
            Eat(TokenType::COMMA);
            block = Expr();
        }

        Eat(TokenType::RPAREN);
        //Eat(TokenType::SEMI);
        node = ExecuteInternalFunction(TokenType::WRITELN, text, block);
    }
    else if (m_currentToken.m_type == TokenType::IF) {
        node = Conditional();
    }
    else node = Empty();



    return node;


}
Node *Parser::Conditional()
{
    Eat(TokenType::IF);
    Node* a = Expr();

    Token compareToken = m_currentToken;
    Eat(compareToken.m_type);

    Node* b= Expr();

    Eat(m_currentToken.m_type);

    Node* block = Block();

    return new ConditionalNode(compareToken, a,b,block);
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

Node *Parser::String()
{
    NodeString* node = new NodeString(m_currentToken, m_currentToken.m_value);
    return node;
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
    while (m_currentToken.m_type==TokenType::PROCEDURE) {
        Eat(TokenType::PROCEDURE);
        QString procName = m_currentToken.m_value;
        Eat(TokenType::ID);
        Eat(TokenType::SEMI);
        Node* block = Block();
        Node* procDecl = new ProcedureDecl(procName, block);
        decl.append(procDecl);
        Eat(TokenType::SEMI);
    }

    return decl;
}

QVector<Node *> Parser::VariableDeclarations()
{
    QVector<Node*> vars;
    vars.append(new Var(m_currentToken));
    Eat(TokenType::ID);

    while (m_currentToken.m_type == TokenType::COMMA) {
        Eat(TokenType::COMMA);
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
        var_decleratons.append(new VarDecl(n, typeNode));
    }

//    return vars;
    return var_decleratons;
}

Node *Parser::ExecuteInternalFunction(TokenType::Type t,  Node* text,Node* block)
{
    return new BuiltinMethod("writeln", text, block);
}

Node *Parser::TypeSpec()
{
    Token t = m_currentToken;
    if (m_currentToken.m_type == TokenType::INTEGER) {
        Eat(TokenType::INTEGER);
    }
    else
        Eat(TokenType::REAL);


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

