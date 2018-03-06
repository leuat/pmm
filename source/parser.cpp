#include "parser.h"
Parser::Parser()
{

}

void Parser::Delete()
{
    for (QString val : m_procedures.keys()) {
        Node* s = m_procedures[val];
           // if (s!=nullptr) {
            //s->Delete();
            delete s;
//        }
    }
    m_procedures.clear();

}

void Parser::Eat(TokenType::Type t)
{
    if (m_currentToken.m_type == t) {
        m_currentToken = m_lexer->GetNextToken();

    }
    else {
        QString warning = "\nDid you forget a semicolon (;) ?";
        ErrorHandler::e.Error("Expected '" + TokenType::getType(t) + "' but found '" +m_currentToken.m_value+"'" + warning,m_currentToken.m_lineNumber);
    }
/*    if (m_currentToken.m_type==TokenType::TEOF) {
        qDebug() << m_currentToken.getType();
        ErrorHandler::e.Error("Syntax errror", m_currentToken.m_lineNumber);
    }
*/
}

void Parser::Eat()
{
    Eat(m_currentToken.m_type);
}

int Parser::findSymbolLineNumber(QString symbol)
{
    int i=1;
    for (QString& s: m_lexer->m_lines) {
        i++;
        if (s.contains(symbol))
            return i;
    }
    return 1;
}

void Parser::InitBuiltinFunctions()
{
    InitBuiltinFunction(QStringList()<< "rand", "initrandom");
    InitBuiltinFunction(QStringList()<< "sine", "initsinetable");
    InitBuiltinFunction(QStringList()<< "*", "initeightbitmul");
    InitBuiltinFunction(QStringList()<< "moveto", "initmoveto");
    InitBuiltinFunction(QStringList()<< "printstring" << "printnumber", "initprintstring");
    InitBuiltinFunction(QStringList()<< "joystick" , "initjoystick");
 }

void Parser::InitBuiltinFunction(QStringList methodName, QString builtinFunctionName)
{
    QString txt = m_lexer->m_text.toLower();
    for (QString s: methodName)
     if (txt.contains(s)) {
        m_procedures[builtinFunctionName] = new NodeProcedureDecl(builtinFunctionName);
        return;
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
    Node* n = nullptr;
    if (SymbolTable::m_constants.contains(m_currentToken.m_value)) {
        Symbol* s = SymbolTable::m_constants[m_currentToken.m_value];
        if (s->m_type=="ADDRESS") m_currentToken.m_type=TokenType::ADDRESS;
        if (s->m_type=="INTEGER") m_currentToken.m_type=TokenType::INTEGER;
        if (s->m_type=="BYTE") m_currentToken.m_type=TokenType::BYTE;
        if (s->m_type=="STRING") m_currentToken.m_type=TokenType::STRING;
        n = new NodeNumber(m_currentToken, s->m_value->m_fVal);
        Eat(m_currentToken.m_type);

    }
    else {
        Token t = m_currentToken;
        if (m_currentToken.m_type==TokenType::STRING) {
           n = String();
           Eat(m_currentToken.m_type);
           return n;

        }

        Eat(m_currentToken.m_type);
        if (m_currentToken.m_type!=TokenType::LBRACKET) {

            n = new NodeVar(t);
        }
        else
            {
                Eat(TokenType::LBRACKET);
                Node* expr = Expr();
                Eat(TokenType::RBRACKET);
                n = new NodeVar(t, expr);


        }
    }
    if (n==nullptr) {
        ErrorHandler::e.Error("Could not assign variable!");
    }
    return n;
}

Node *Parser::Empty()
{
    return new NoOp();
}

Node *Parser::AssignStatement()
{
    Node* arrayIndex = nullptr;
    Token t = m_currentToken;
    Node* left = Variable();
    Token token = m_currentToken;


    if (m_currentToken.m_type!=TokenType::ASSIGN) {
        ErrorHandler::e.Error("Could not find variable or procedure '" + t.m_value+  "'", t.m_lineNumber);
    }
    Eat(TokenType::ASSIGN);
    Node* right = Expr();
    return new NodeAssign(left, token, right);


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
            node = BuiltinFunction();
//        if (node==nullptr)
//            node = Constant();
        if (node==nullptr)
            node = AssignStatement();

    }
/*    else if (m_currentToken.m_type==TokenType::WRITELN) {
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
    }*/
    else if (m_currentToken.m_type == TokenType::IF) {
        Eat(TokenType::IF);
        node = Conditional();
    }
    else if (m_currentToken.m_type == TokenType::FOR) {
        node = ForLoop();
    }
    else if (m_currentToken.m_type == TokenType::WHILE) {
        Eat(TokenType::WHILE);
        node = Conditional(true);
    }
    else if (m_currentToken.m_type == TokenType::ASM) {
        return InlineAssembler();

    }

    else {
        //ErrorHandler::e.Error("Unknown method " + m_currentToken.getType());
        return Empty();
    }



    return node;


}
Node *Parser::Conditional(bool isWhileLoop)
{
    Node* a = Expr();

    Token compareToken = m_currentToken;
    Eat(compareToken.m_type);

    Node* b= Expr();

    Eat(m_currentToken.m_type);

    Node* block = Block(false);

    return new NodeConditional(compareToken, a,b,block, isWhileLoop);
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
    NodeCompound* root = new NodeCompound();
    for (Node* n: nodes)
        root->children.append(n);


    return root;

}

Node *Parser::Program()
{
//    Node* n = CompoundStatement();
    Eat(TokenType::PROGRAM);
    NodeVar* varNode = (NodeVar*)Variable();
    QString progName = varNode->value;
    Eat(TokenType::SEMI);
    NodeBlock* block = (NodeBlock*)Block(true);
    NodeProgram* program = new NodeProgram(progName, block);
    Eat(TokenType::DOT);

    return program;
}



Node* Parser::Factor()
{


    Token t = m_currentToken;

    if (t.m_type==TokenType::TEOF)
        ErrorHandler::e.Error("Syntax errror", m_currentToken.m_lineNumber);


    if (t.m_type == TokenType::INTEGER_CONST || t.m_type ==TokenType::REAL_CONST
            || t.m_type ==TokenType::ADDRESS) {
        Eat(t.m_type);
        return new NodeNumber(t, t.m_intVal);
    }

    if (t.m_type == TokenType::PLUS || t.m_type==TokenType::MINUS) {
        Eat(t.m_type);
        return new NodeUnaryOp(t, Factor());
    }




    if (t.m_type == TokenType::LPAREN) {
        Eat(TokenType::LPAREN);
        Node* node = Expr();
        Eat(TokenType::RPAREN);
        return node;

    }
    if (t.m_type == TokenType::ID) {
        Node* node = FindProcedure();
        if (node!=nullptr)
            return node;

    }
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
    m_lexer->Initialize();
    m_currentToken = m_lexer->GetNextToken();
    //qDebug() <<m_lexer->m_text[0];
    SymbolTable::Initialize();
    InitBuiltinFunctions();
    NodeProgram* root = (NodeProgram*)Program();

    // First add builtin functions
    for (QString s: m_procedures.keys())
        if (((NodeProcedureDecl*)m_procedures[s])->m_block==nullptr)
            root->m_NodeBlock->m_decl.append(m_procedures[s]);

    // Then add regular ones ORDERED BY DEFINITION
    //for (QString s: m_procedures.keys())
     //   if (((NodeProcedureDecl*)m_procedures[s])->m_block!=nullptr)
        for ( Node* n: m_proceduresOnly )
            root->m_NodeBlock->m_decl.append(n);


    if (m_currentToken.m_type!=TokenType::TEOF)
        ErrorHandler::e.Error("End of file error");

//    root->ExecuteSym(&SymbolTable::s);
    return root;
}

Node *Parser::FindProcedure()
{
    if (m_procedures.contains(m_currentToken.m_value)) {
        QString procName = m_currentToken.m_value;
        Token t = m_currentToken;
        Eat(TokenType::ID);
        Eat(TokenType::LPAREN);
        QVector<Node*> paramList;
        while (m_currentToken.m_type!=TokenType::RPAREN && !m_lexer->m_finished) {
            paramList.append(Expr());
            if (m_currentToken.m_type==TokenType::COMMA)
                Eat(TokenType::COMMA);
            //if (m_currentToken.m_type==TokenType::SEMI)
            //    ErrorHandler::e.Error("Syntax errror", m_currentToken.m_lineNumber);
        }
        if (!m_procedures.contains(procName))
            ErrorHandler::e.Error("Could not find procedure :" + procName, m_currentToken.m_lineNumber);

        NodeProcedureDecl* p = (NodeProcedureDecl*)m_procedures[procName];
        Eat(TokenType::RPAREN);

        //p->SetParameters(paramList);

        return new NodeProcedure(p, paramList, t);
    }
    //qDebug() << m_currentToken.getType() << " with value " << m_currentToken.m_value;
    return nullptr;
}

Node *Parser::Block(bool useOwnSymTab)
{

    if (m_currentToken.m_type!=TokenType::VAR  && m_currentToken.m_type!=TokenType::BEGIN)
        return nullptr;

    return new NodeBlock(Declarations(), CompoundStatement(), useOwnSymTab);
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
    return new NodeForLoop(a,b,block);

}

Node *Parser::String()
{
    m_currentToken.m_type = TokenType::STRING;
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
    while (m_currentToken.m_type==TokenType::PROCEDURE || m_currentToken.m_type==TokenType::INTERRUPT) {

        bool isInterrupt= (m_currentToken.m_type==TokenType::PROCEDURE)?false:true;

        Eat(m_currentToken.m_type);
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
        if (block==nullptr)
            qDebug() << "Procedure decl: " << procName;
        Node* procDecl = new NodeProcedureDecl(procName, paramDecl, block, isInterrupt);
        //decl.append(procDecl);
        if (block!=nullptr)
            Eat(TokenType::SEMI);

        m_procedures[procName] = procDecl;
        if (block!=nullptr)
            m_proceduresOnly.append(procDecl);

    }

    return decl;
}

QVector<Node *> Parser::VariableDeclarations()
{
    QVector<Node*> vars;
    vars.append(new NodeVar(m_currentToken));
    Eat(TokenType::ID);

    while (m_currentToken.m_type == TokenType::COMMA) {
        Eat(TokenType::COMMA);
        vars.append(new NodeVar(m_currentToken));
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
        var_decleratons.append(new NodeVarDecl(n, typeNode));
    }

//    return vars;
    return var_decleratons;
}

Node *Parser::TypeSpec()
{
    Token t = m_currentToken;

    if (m_currentToken.m_type == TokenType::INCBIN || m_currentToken.m_type == TokenType::INCSID) {
        Eat();
        Eat(TokenType::LPAREN);
        QString binFile = m_currentToken.m_value;
        Eat();
        QString position ="";
        if (m_currentToken.m_type==TokenType::COMMA) {
            Eat();
            position = m_currentToken.m_value;
            Eat();
        }
        Eat(TokenType::RPAREN);

        return new NodeVarType(t,binFile, position);

    }


    if (m_currentToken.m_type == TokenType::ARRAY) {
        Eat(TokenType::ARRAY);
        Eat(TokenType::LBRACKET);
        float count =m_currentToken.m_intVal;
        Eat(m_currentToken.m_type);
        Eat(TokenType::RBRACKET);
        Eat(TokenType::OF);
        Token arrayType = m_currentToken;
        Eat(m_currentToken.m_type);
        QStringList data;
        // Contains constant init?
        if (m_currentToken.m_type==TokenType::EQUALS) {
            Eat();
            Eat(TokenType::LPAREN);
            while (m_currentToken.m_type!=TokenType::RPAREN) {
                data << QString::number(m_currentToken.m_intVal);
                Eat();
                if (m_currentToken.m_type==TokenType::COMMA)
                    Eat();
            }
            Eat(TokenType::RPAREN);
        }

        t.m_intVal = count;
        return new NodeVarType(t,arrayType,data);

    }

    Eat(m_currentToken.m_type);


    return new NodeVarType(t);

}

Node *Parser::BuiltinFunction()
{
    if (Syntax::s.builtInFunctions.contains(m_currentToken.m_value.toLower())) {
        QString procName = m_currentToken.m_value.toLower();
        int noParams = Syntax::s.builtInFunctions[procName].m_params.count();
        Eat(TokenType::ID);
        Eat(TokenType::LPAREN);
        QVector<Node*> paramList;
        while (m_currentToken.m_type!=TokenType::RPAREN) {
            if (m_currentToken.m_type==TokenType::STRING) {
                paramList.append( String() );
                Eat(TokenType::STRING);
            }
            else
                paramList.append(Expr());

            if (m_currentToken.m_type==TokenType::COMMA)
                Eat(TokenType::COMMA);
        }

        Eat(TokenType::RPAREN);

        //qDebug() << "Params count for " << procName << " :" << paramList.count();
        if (noParams!=paramList.count()) {
            QString s = "Error using builtin function " + procName + " \n";
            s += "Requires " + QString::number(noParams) + " parameters but has " + QString::number(paramList.count());

            ErrorHandler::e.Error(s, m_currentToken.m_lineNumber);
        }

        return new NodeBuiltinMethod(procName,paramList);
        //p->SetParameters(paramList);


    }
    return nullptr;

}

Node *Parser::Constant()
{
    QString id = m_currentToken.m_value;
    if (SymbolTable::m_constants.contains(id)) {
        Eat(m_currentToken.m_type);
        Symbol* s = SymbolTable::m_constants[id];
        Node* n =  new NodeNumber(Token(s->getTokenType(), s->m_value->m_fVal), s->m_value->m_fVal);
        return n;
    }
    return nullptr;
}

Node *Parser::InlineAssembler()
{
    Eat(TokenType::ASM);
    Eat(TokenType::LPAREN);
    if (m_currentToken.m_type!=TokenType::STRING)
        ErrorHandler::e.Error("Inline assembler must be enclosed as a string");
    Node* n = new NodeAsm(m_currentToken);
    Eat(TokenType::STRING);
    Eat(TokenType::RPAREN);
    return n;
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

