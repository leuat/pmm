#include "token.h"

QString TokenType::types[33] = { "INTEGER", "PLUS", "MINUS", "MUL", "DIV", "LPAREN",
            "RPAREN", "TEOF", "ID", "ASSIGN", "BEGIN",
            "END", "SEMI", "DOT", "VAR", "REAL",
            "PROGRAM", "COLON", "COMMA", "INTEGER_CONST", "REAL_CONST", "PROCEDURE, WRITELN",
            "STRING", "IF", "THEN", "EQUALS", "NOTEQUALS", "GREATER", "LESS",
            "FOR", "TO","DO", "NADA"};

Token::Token()
{

}
