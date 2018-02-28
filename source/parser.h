#ifndef PARSER_H
#define PARSER_H

#include "source/ast/ast.h"
#include "source/lexer.h"

#include "source/ast/nodebinop.h"
#include "source/ast/nodenumber.h"
#include "source/ast/nodestring.h"
#include "source/ast/nodeunaryop.h"
#include "source/ast/nodecompound.h"
#include "source/ast/nodevar.h"
#include "source/ast/nodeassign.h"
#include "source/ast/nodevardecl.h"
#include "source/ast/nodeblock.h"
#include "source/ast/nodeprogram.h"
#include "source/ast/nodevartype.h"
#include "source/ast/nodeproceduredecl.h"
#include "source/ast/nodeprocedure.h"
#include "source/ast/nodeconditional.h"
#include "source/ast/nodeforloop.h"
#include "source/ast/nodebuiltinmethod.h"


class Parser {
public:

    QMap<QString, Node*> m_procedures;

    Lexer m_lexer;
    Token m_currentToken;
    Parser();
    Parser(Lexer l) {
        m_lexer = l;
        m_currentToken = m_lexer.GetNextToken();
    }
    ~Parser() {
        Delete();
    }

    void Delete();

    void Eat(TokenType::Type t);

    void VerifyToken(Token t);

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
    Node* FindProcedure();
    Node* Block(bool useOwnSymTab);
    QVector<Node*> Parameters();
    Node* ForLoop();
    Node* String();
    Node* Conditional();
//    QVector<Node*> Procedure();
    QVector<Node*> Declarations();
    QVector<Node*> VariableDeclarations();
    Node* TypeSpec();
    Node* BuiltinFunction();


};


#endif // PARSER_H
