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
#include "source/ast/nodewhileloop.h"
#include "source/ast/nodeasm.h"
#include "source/ast/nodebinaryclause.h".h"




class Parser {
public:

    QMap<QString, Node*> m_procedures;
    QMap<QString, QString> m_preprocessorDefines;
    QVector<Node*> m_proceduresOnly;
    Lexer* m_lexer;
    Token m_currentToken;
    int m_pass = 0;
    SymbolTable* m_symTab;
    Parser();
    Parser(Lexer* l) {
        m_lexer = l;
    }
    ~Parser() {
        Delete();
    }

    void Delete();

    void Eat(TokenType::Type t);
    void VerifyToken(Token t);

    void HandlePreprocessorInParsing();
    void Preprocess();
    void PreprocessReplace();
    void PreprocessIfDefs(bool ifdef);

    int findPage();

    Node* Parse();
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
    Node* FindProcedure();
    Node* BinaryClause();
    //Node* LogicalClause();
    Node* Block(bool useOwnSymTab);
    QVector<Node*> Parameters();
    Node* ForLoop();
//    Node* WhileLoop();
    Node* String();

    Node* Conditional(bool isWhileLoop=false);
//    QVector<Node*> Procedure();
    QVector<Node*> Declarations(bool isMain);
    QVector<Node*> VariableDeclarations();
    Node* TypeSpec();
    Node* BuiltinFunction();
    Node* Constant();
    Node* InlineAssembler();
    void Eat();


    int findSymbolLineNumber(QString symbol);


    void InitBuiltinFunctions();


    void InitBuiltinFunction(QStringList methodName, QString builtinFunctionName);

};


#endif // PARSER_H
