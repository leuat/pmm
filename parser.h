#ifndef PARSER_H
#define PARSER_H

#include "ast.h"


/*class Procedure {
public:
    QString m_name;
    Node* m_block;

};
*/
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
    Node* ExecuteInternalFunction(TokenType::Type t, Node* text, Node* block);
    Node* TypeSpec();



};


#endif // PARSER_H
