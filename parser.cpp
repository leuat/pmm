#include "parser.h"
Parser::Parser()
{

}

void Parser::Eat(TokenType::Type t)
{
    if (m_currentToken.m_type == t) {
        m_currentToken = m_lexer.GetNextToken();
        //qDebug() << "Next token: " << m_currentToken.getType();
    }
    else {
        QString warning = "\nDid you forget a semicolon (;) ?";
        ErrorHandler::e.Error("Expected '" + TokenType::getType(t) + "' but found '" +m_currentToken.m_value+"'" + warning);
    }
}

void Parser::VerifyToken(Token t)
{
    //if (Syntax::s.globals.contains(t.m_value))
    //    return;

   // ErrorHandler::e.Error("Does not recognize '"+t.m_value + "'");
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
    Token t = m_currentToken;
    Node* left = Variable();
    Token token = m_currentToken;
    if (m_currentToken.m_type!=TokenType::ASSIGN)
        ErrorHandler::e.Error("Could not find variable or procedure '" + t.m_value+  "'");
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
        node = FindProcedure();
        if (node==nullptr)
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
    else if (m_currentToken.m_type == TokenType::FOR) {
        node = ForLoop();
    }
    else {
        //ErrorHandler::e.Error("Unknown method " + m_currentToken.getType());
        return Empty();
    }



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

    Node* block = Block(false);

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
        ErrorHandler::e.Error("Parser::Statementlist : Token should not be ID");


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
    BlockNode* block = (BlockNode*)Block(true);
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
        ErrorHandler::e.Error("End of file error");

    root->ExecuteSym(nullptr);
    return root;
}

Node *Parser::FindProcedure()
{
    if (m_procedures.contains(m_currentToken.m_value)) {
        QString procName = m_currentToken.m_value;
        Eat(TokenType::ID);
        Eat(TokenType::LPAREN);
        QVector<Node*> paramList;
        while (m_currentToken.m_type!=TokenType::RPAREN) {
            paramList.append(Expr());
            if (m_currentToken.m_type==TokenType::COMMA)
                Eat(TokenType::COMMA);
        }

        Eat(TokenType::RPAREN);
        ProcedureDecl* p = (ProcedureDecl*)m_procedures[procName];
        //p->SetParameters(paramList);

        return new ProcedureNode(p, paramList);
    }
    //qDebug() << m_currentToken.getType() << " with value " << m_currentToken.m_value;
    return nullptr;
}

Node *Parser::Block(bool useOwnSymTab)
{
    return new BlockNode(Declarations(), CompoundStatement(), useOwnSymTab);
}

QVector<Node *> Parser::Parameters()
{
    QVector<Node*> decl;
    if (m_currentToken.m_type==TokenType::LPAREN) {
        Eat(TokenType::LPAREN);
        while (m_currentToken.m_type==TokenType::ID) {
            QVector<Node*> ns = VariableDeclarations();
            for (Node* n: ns)
                decl.append(n);

            Eat(m_currentToken.m_type);
        }
    }
    //Eat(TokenType::RPAREN);
    return decl;
}

Node *Parser::ForLoop()
{
    Eat(TokenType::FOR);
    Node* a = AssignStatement();
    Eat(TokenType::TO);
    Node* b = Expr();
    Eat(m_currentToken.m_type);
//    qDebug() << "Current: " << m_currentToken.getType();
//    Eat(TokenType::DO);
    Node* block = Block(false);

//    qDebug() << m_currentToken.getType();
  //  exit(1);
    return new ForLoopNode(a,b,block);

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
        //exit(1);
        QVector<Node*> paramDecl;
        if (m_currentToken.m_type==TokenType::LPAREN)
            paramDecl = Parameters();
        //qDebug()<< "current : " << m_currentToken.getType();
        // If no parameters
        if (m_currentToken.m_type==TokenType::RPAREN)
            Eat(TokenType::RPAREN);

        Eat(TokenType::SEMI);
        Node* block = Block(true);
        Node* procDecl = new ProcedureDecl(procName, paramDecl, block);
        //decl.append(procDecl);
        Eat(TokenType::SEMI);

        m_procedures[procName] = procDecl;

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

