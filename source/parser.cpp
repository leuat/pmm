#include "parser.h"
#include "source/data_pmm.h"
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
        if (m_currentToken.m_type==TokenType::PREPROCESSOR && m_pass==1)
            HandlePreprocessorInParsing();

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
    InitBuiltinFunction(QStringList()<< "*", "initeightbitmul");
    InitBuiltinFunction(QStringList()<< "*", "init16x8mul");
    InitBuiltinFunction(QStringList()<< "*", "init8x8div");
    InitBuiltinFunction(QStringList()<< "*", "init16x8div");
    InitBuiltinFunction(QStringList()<< "rand", "initrandom");
    InitBuiltinFunction(QStringList()<< "sine", "initsinetable");
    InitBuiltinFunction(QStringList()<< "moveto", "initmoveto");
    InitBuiltinFunction(QStringList()<< "printstring" << "printnumber", "initprintstring");
    InitBuiltinFunction(QStringList()<< "joystick" , "initjoystick");
//    InitBuiltinFunction(QStringList()<< "zeropage" << "inczp" , "initzeropage");
 }

void Parser::InitBuiltinFunction(QStringList methodName, QString builtinFunctionName)
{
    QString txt = m_lexer->m_text.toLower();
    for (QString s: methodName)
     if (txt.contains(s)) {
        m_procedures[builtinFunctionName] = new NodeProcedureDecl(Token(TokenType::PROCEDURE, builtinFunctionName), builtinFunctionName);
        return;
     }

}

void Parser::VerifyToken(Token t)
{
    //if (Syntax::s.globals.contains(t.m_value))
    //    return;

    // ErrorHandler::e.Error("Does not recognize '"+t.m_value + "'");
}

void Parser::PreprocessIfDefs(bool ifdef)
{
    Eat();
    QString key = m_currentToken.m_value;
    Eat();

  /*  for (QString k : m_preprocessorDefines.keys())
        qDebug() << " key : " << k;
*/
//    qDebug() << key << " " << m_preprocessorDefines.contains(key);
    if (ifdef && m_preprocessorDefines.contains(key))

        return; // K

    if (!ifdef && !m_preprocessorDefines.contains(key))
        return;

    // Remove everything!

    while (!m_lexer->m_finished) {
        m_pass = 0;
        Eat(); // OM NOM NOM
        m_pass = 1;
        if (m_currentToken.m_type==TokenType::PREPROCESSOR) {
            if (m_currentToken.m_value=="endif") {
                Eat();
                return; // Finish
            }
        }
    }


}

int Parser::findPage()
{
    int forcePage = 0;

    if (m_currentToken.m_type==TokenType::OFFPAGE) {
        forcePage = 1;
        Eat();
    }
    else
    if (m_currentToken.m_type==TokenType::ONPAGE) {
        forcePage = 2;
        Eat();
    }

    return forcePage ;
}


void Parser::HandlePreprocessorInParsing()
{
    if (m_currentToken.m_value=="define") {
        Eat();
        Eat();
        Eat();
        return;
    }
    if (m_currentToken.m_value=="userdata") {
        Eat();
        Eat();
        Eat();
        Eat();
        return;
    }
    if (m_currentToken.m_value=="include") {
        Eat();
        Eat();
    }
    if (m_currentToken.m_value=="endif") {
        Eat();
        return;
    }
    if (m_currentToken.m_value=="ifdef") {
        PreprocessIfDefs(true);
        return;
    }

    if (m_currentToken.m_value=="ifndef") {
        PreprocessIfDefs(false);
        return;
    }

}



Node *Parser::Variable()
{
    Node* n = nullptr;

    if (SymbolTable::m_constants.contains(m_currentToken.m_value)) {
        Symbol* s = SymbolTable::m_constants[m_currentToken.m_value];

      //  qDebug() << "looking for " << m_currentToken.m_value << " , found symbol: " << s->m_name << " with value " << s->m_value->m_fVal;

        if (s->m_type=="ADDRESS") m_currentToken.m_type=TokenType::ADDRESS;
        if (s->m_type=="INTEGER") m_currentToken.m_type=TokenType::INTEGER;
        if (s->m_type=="BYTE") m_currentToken.m_type=TokenType::BYTE;
        if (s->m_type=="STRING") m_currentToken.m_type=TokenType::STRING;
        if (s->m_type=="CSTRING") m_currentToken.m_type=TokenType::CSTRING;

        Token t = m_currentToken;
        Eat(m_currentToken.m_type);
        Node *expr = nullptr;
        if (m_currentToken.m_type==TokenType::LBRACKET) {
            Eat(TokenType::LBRACKET);
            expr = Expr();
            Eat(TokenType::RBRACKET);
         }

        if (t.m_type==TokenType::ADDRESS && expr!=nullptr) {
            t.m_value = "$"+QString::number( (int)s->m_value->m_fVal,16);
            n = new NodeVar(t,expr);
        }
        else
            n = new NodeNumber(t, s->m_value->m_fVal);

    }
    else {
        Token t = m_currentToken;
        if (m_currentToken.m_type==TokenType::STRING || m_currentToken.m_type==TokenType::CSTRING) {
           n = String();
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
//        qDebug() << m_currentToken;
        ErrorHandler::e.Error("Could not find '" + t.m_value+  "', did you forget a colon?" , token.m_lineNumber);
    }
    Eat(TokenType::ASSIGN);
    Node* right = Expr();
    return new NodeAssign(left, t, right);


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
    else if (m_currentToken.m_type == TokenType::ADDRESS) {
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

    if (node==nullptr)
        ErrorHandler::e.Error("CAAARGH  ",0);


    return node;


}

Node *Parser::BinaryClause()
{
    if (m_currentToken.m_type == TokenType::LPAREN) {
        // Logical clause AND OR
        Eat(TokenType::LPAREN);
        Node* a = BinaryClause();
        if (m_currentToken.m_type==TokenType::RPAREN) {
            Eat();
            return a;
        }
        Token logical = m_currentToken;
        Eat();
        Node* b = BinaryClause();
        Eat(TokenType::RPAREN);
        return new NodeBinaryClause(logical, a, b);
    }

    Node* a = Expr();
    Token comparetoken = m_currentToken;
    Eat();
    Node* b = Expr();

    return new NodeBinaryClause(comparetoken, a, b);

}



Node *Parser::Conditional(bool isWhileLoop)
{

    QVector<Node*> left, right;
    QVector<Token> compareTokens, conditionals;

    // Start
    Token t = m_currentToken;
    bool done=false;
    int linenum = m_currentToken.m_lineNumber;

    Node* clause = BinaryClause();

    int forcePage = findPage();

    if (m_currentToken.m_type==TokenType::THEN || m_currentToken.m_type==TokenType::DO)
        Eat(m_currentToken.m_type);
    else {
        ErrorHandler::e.Error("Expected THEN or DO after conditional", linenum);
    }

    Node* block = Block(false);

    Node* nodeElse = nullptr;
    if (m_currentToken.m_type==TokenType::ELSE) {
        Eat(TokenType::ELSE);
        nodeElse = Block(false);
    }

    return new NodeConditional(t, forcePage, clause, block, isWhileLoop, nodeElse);
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
//        ErrorHandler::e.Error("Parser::Statementlist SYNTAX ERROR : Token should not be ID", m_currentToken.m_lineNumber);
    ErrorHandler::e.Error("Did you forget a semicolon? (Token should not be ID in Parser)", m_currentToken.m_lineNumber);


    return results;

}

Node *Parser::CompoundStatement()
{
    if (m_currentToken.m_type!=TokenType::BEGIN) {
        // Single statement
        Node* n =  Statement();
  //      Eat(TokenType::SEMI);
    //    qDebug() << m_currentToken.getType();
      //  qDebug() << m_currentToken.m_value;

        return n;
    }
    Token t = m_currentToken;
    Eat(TokenType::BEGIN);
    QVector<Node*> nodes = StatementList();
    Eat(TokenType::END);
    NodeCompound* root = new NodeCompound(t);
    for (Node* n: nodes)
        root->children.append(n);

//    qDebug() << "from begin block : " +m_currentToken.getType();
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
        ErrorHandler::e.Error("Syntax error", m_currentToken.m_lineNumber);


    if (t.m_type == TokenType::INTEGER_CONST || t.m_type ==TokenType::REAL_CONST
            || t.m_type ==TokenType::ADDRESS) {
        Eat(t.m_type);
        //qDebug() << "parser: " <<t.m_value << t.m_intVal;
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
//        qDebug() << "FINDING PROCEDURE IN TERM: " << t.m_value;
        Node* node = FindProcedure();
        if (node!=nullptr)
            return node;
        node = BuiltinFunction();
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


void Parser::Preprocess()
{
    m_lexer->Initialize();
    m_lexer->m_ignorePreprocessor = false;
    m_currentToken = m_lexer->GetNextToken();
    m_preprocessorDefines.clear();
    while (m_currentToken.m_type!=TokenType::TEOF) {
        if (m_currentToken.m_type == TokenType::PREPROCESSOR) {
            if (m_currentToken.m_value.toLower()=="include") {
                Eat(TokenType::PREPROCESSOR);
                QString filename =m_lexer->m_path +"/"+ m_currentToken.m_value;

                QString text = m_lexer->loadTextFile(filename);
                int ln=m_lexer->getLineNumber(m_currentToken.m_value);
                m_lexer->m_text.insert(m_lexer->m_pos, text);
                int count = text.split("\n").count();

                m_lexer->m_includeFiles.append(
                            FilePart(filename,ln, ln+ count, count));

                Eat(TokenType::STRING);
                //Eat(TokenType::SEMI);
                //IncludeFile(filename);
            }
            else if (m_currentToken.m_value.toLower() =="define") {
                Eat(TokenType::PREPROCESSOR);
                QString key = m_currentToken.m_value;
                Eat();
                QString val = m_currentToken.m_value;
                if (val=="")
                    val = QString::number(m_currentToken.m_intVal);

                m_preprocessorDefines[key] = val;
            }
            else if (m_currentToken.m_value.toLower() =="userdata") {
                Eat(TokenType::PREPROCESSOR);
                QString from = m_currentToken.m_value;
                Eat();
                QString to = m_currentToken.m_value;
                Eat();
                QString name = m_currentToken.m_value;
                bool ok;
                m_userBlocks.append(MemoryBlock(from.remove("$").toInt(&ok,16), to.remove("$").toInt(&ok, 16),
                                                MemoryBlock::USER, name));

            }
        }

        Eat(m_currentToken.m_type);
    }

    // Afterwards, replace all preprocessor defines
//    PreprocessIfDefs();
    PreprocessReplace();
}

void Parser::PreprocessReplace()
{
    for (QString k: m_preprocessorDefines.keys()) {
        QString val = m_preprocessorDefines[k];
//        qDebug() << "Replacing: @" + k << "  with " << val;
        m_lexer->m_text = m_lexer->m_text.replace("@" +k, val);

    }
}

Node* Parser::Parse()
{
    // Call preprocessor for include files etc
    m_lexer->m_text = m_lexer->m_orgText;
    m_pass = 0;
    Preprocess();
    m_pass = 1;
    m_symTab = new SymbolTable();
    m_lexer->Initialize();
    m_lexer->m_ignorePreprocessor = true;
    m_currentToken = m_lexer->GetNextToken();
   /* qDebug() << m_lexer->m_pos;
    qDebug() << m_lexer->m_currentChar;
    qDebug() << m_currentToken.getType();
*/
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
    Token procToken = m_currentToken;
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

/*    if (m_currentToken.m_type!=TokenType::VAR  && m_currentToken.m_type!=TokenType::BEGIN)
        return nullptr;
*/
    if (m_currentToken.m_type==TokenType::PROCEDURE || m_currentToken.m_type==TokenType::INTERRUPT)
        return nullptr;
    return new NodeBlock(m_currentToken, Declarations(useOwnSymTab), CompoundStatement(), useOwnSymTab);
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
    int ln = m_currentToken.m_lineNumber;
    Eat(TokenType::FOR);
    Node* a = AssignStatement();
    Eat(TokenType::TO);
    Node* b = Expr();
    bool unroll = false;
    Node* step = nullptr;

    int forcePage = 0;
    int loopType = 0; // use var
    int curCnt=0;
    while (m_currentToken.m_type!=TokenType::DO) {
        if (m_currentToken.m_type==TokenType::ONPAGE || m_currentToken.m_type==TokenType::OFFPAGE)
            forcePage = findPage();
        if (m_currentToken.m_type==TokenType::STEP) {
            Eat();
            step = Expr();
            qDebug() << TokenType::getType(step->m_op.m_type);
        }
        if (m_currentToken.m_type==TokenType::LOOPX) {
            Eat();
            loopType = 1;
        }
        if (m_currentToken.m_type==TokenType::LOOPY) {
            Eat();
            loopType = 2;
        }
        if (m_currentToken.m_type==TokenType::UNROLL) {
            Eat();
            unroll = true;
        }
        if (curCnt++>15) {
            ErrorHandler::e.Error("For loop needs a 'DO' keyword", ln);
        }
    }


    Eat(m_currentToken.m_type);
//    qDebug() << "Current: " << m_currentToken.getType();
//    Eat(TokenType::DO);
    Node* block = Block(false);

//    qDebug() << m_currentToken.getType();
  //  exit(1);
    return new NodeForLoop(a,b,block, step, unroll, forcePage,loopType);

}

Node *Parser::String()
{

    if (m_currentToken.m_type==TokenType::STRING || m_currentToken.m_type==TokenType::CSTRING) {
        NodeString* node = new NodeString(m_currentToken,QStringList()<<m_currentToken.m_value,m_currentToken.m_type==TokenType::CSTRING);
        Eat();
        return node;
    }
    if (m_currentToken.m_type!=TokenType::LPAREN)
        ErrorHandler::e.Error("String declaration must be single string or paranthesis with multi values.", m_currentToken.m_lineNumber);

    Eat();
    Token token(TokenType::STRING, m_currentToken.m_value);
    //m_currentToken.m_type = TokenType::STRING;
    QStringList lst;
    bool done = false;
//    lst<<m_currentToken.m_value;
    int max=0;
    while (m_currentToken.m_type!=TokenType::RPAREN) {
        if (m_currentToken.m_value=="")
            m_currentToken.m_value = QString::number(m_currentToken.m_intVal);

        if (m_currentToken.m_value!="")
            lst<<m_currentToken.m_value;
        Eat();
        if (m_currentToken.m_type==TokenType::COMMA)
            Eat();
        if (max++>10000)
            ErrorHandler::e.Error("String error!", token.m_lineNumber);
    }
    Eat(); // RParen
//    qDebug() <<m_currentToken.getType();

    NodeString* node = new NodeString(token, lst, token.m_type==TokenType::CSTRING);
    return node;
}


QVector<Node*> Parser::Declarations(bool isMain)
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

/*
    while (m_currentToken.m_type==TokenType::ID || m_currentToken.m_type==TokenType::PROCEDURE ||
           m_currentToken.m_type==TokenType::INTERRUPT || m_currentToken.m_type == TokenType::VAR) {


    if (m_currentToken.m_type==TokenType::VAR) {
        Eat(TokenType::VAR);
        continue;
    }

    if (m_currentToken.m_type==TokenType::ID) {
            QVector<Node*> ns = VariableDeclarations();
            for (Node* n: ns)
                decl.append(n);
            Eat(TokenType::SEMI);
            continue;
     }


*/
    while (m_currentToken.m_type==TokenType::PROCEDURE || m_currentToken.m_type==TokenType::INTERRUPT) {
        bool isInterrupt= (m_currentToken.m_type==TokenType::PROCEDURE)?false:true;
        Token tok = m_currentToken;
        Eat(m_currentToken.m_type);
        QString procName = m_currentToken.m_value;
        //qDebug() << tok.m_value  << " : " << procName;
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
//        if (block==nullptr)
  //          qDebug() << "Procedure decl: " << procName;
        Node* procDecl = new NodeProcedureDecl(tok, procName, paramDecl, block, isInterrupt);
        //decl.append(procDecl);
        if (block!=nullptr)
            Eat(TokenType::SEMI);
        else {
            // Check if already defined

        }

        m_procedures[procName] = procDecl;
        if (block!=nullptr) {
            bool ok = true;
             // Check if procedure already declared
            for (Node* n: m_proceduresOnly) {
                NodeProcedureDecl* proc =(NodeProcedureDecl*)n;
                if (proc->m_procName==procName) ok = false;

            }
            if (!ok)
                ErrorHandler::e.Error("Procedure '"+ procName +"' already defined", tok.m_lineNumber);

            m_proceduresOnly.append(procDecl);
        }

    }
//    }
   // qDebug() << "Finally:" << m_currentToken.getType();
    if (m_currentToken.m_type!=TokenType::BEGIN && isMain)
        ErrorHandler::e.Error("After declarations, BEGIN is expected", m_currentToken.m_lineNumber);

    return decl;
}

QVector<Node *> Parser::VariableDeclarations()
{
    QVector<Node*> vars;
    vars.append(new NodeVar(m_currentToken));
    if (m_symTab->m_symbols.contains(m_currentToken.m_value))
        ErrorHandler::e.Error("Variable '" + m_currentToken.m_value + "' is already defined.", m_currentToken.m_lineNumber);
    m_symTab->Define(new Symbol(m_currentToken.m_value,""));
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

    for (Node* n : vars) {
        NodeVarDecl* decl = new NodeVarDecl(n, typeNode);
        var_decleratons.append(decl);
        if (typeNode->m_op.m_type == TokenType::INCSID) {
            decl->InitSid(m_lexer->m_path);
        }
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

        QString position = "";
        if (m_currentToken.m_type==TokenType::AT) {
            Eat(TokenType::AT);
            position = m_currentToken.m_value;
            Eat(m_currentToken.m_type);
        }

        t.m_intVal = count;
        return new NodeVarType(t,position, arrayType,data);

    }

    if (m_currentToken.m_type == TokenType::STRING || m_currentToken.m_type==TokenType::CSTRING) {
        Eat();
        QStringList initData;
        if (m_currentToken.m_type == TokenType::EQUALS) {
            Eat();
            NodeString* str = (NodeString*)String();
            initData = str->m_val;
        }
        return new NodeVarType(t,initData);
    }

    Eat();
    // Is regular single byte / pointer

    QString initVal = "";
    if (m_currentToken.m_type == TokenType::EQUALS) {
        Eat();
        initVal = m_currentToken.m_value;

        if (initVal=="") {
            initVal = QString::number(m_currentToken.m_intVal);
        }


        Eat(m_currentToken.m_type);

    }
   // qDebug() << "Type: " << t.m_value << " " << initVal;

    return new NodeVarType(t,initVal);

}

Node *Parser::BuiltinFunction()
{
    if (Syntax::s.builtInFunctions.contains(m_currentToken.m_value.toLower())) {
        QString procName = m_currentToken.m_value.toLower();
        int noParams = Syntax::s.builtInFunctions[procName].m_params.count();
        Eat(TokenType::ID);
        Eat(TokenType::LPAREN);
        QVector<Node*> paramList;
        QString prev;

        while (m_currentToken.m_type!=TokenType::RPAREN) {
            if (m_currentToken.m_type==TokenType::STRING) {
                paramList.append( String() );
            }
            else {
                QString pname = m_currentToken.m_value;
                try {
                    paramList.append(Expr());
                } catch (FatalErrorException fe) {
                    fe.message = "Could not find ID/procedure/variable! '" + prev + "'\n" + fe.message;
                    throw fe;
                }
                prev = pname;
            }

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

    while (m_currentToken.m_type == TokenType::Type::PLUS || m_currentToken.m_type == TokenType::Type::MINUS
            || m_currentToken.m_type == TokenType::Type::BITAND || m_currentToken.m_type == TokenType::Type::BITOR) {
        Token t = m_currentToken;

        Eat(m_currentToken.m_type);

        node = new NodeBinOP(node, t, Term());

    }
    return node;
}

