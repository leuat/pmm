#include "token.h"

QString TokenType::types[30] = { "INTEGER", "PLUS", "MINUS", "MUL", "DIV", "LPAREN",
            "RPAREN", "TEOF", "ID", "ASSIGN", "BEGIN",
            "END", "SEMI", "DOT", "VAR", "REAL",
            "PROGRAM", "COLON", "COMMA", "INTEGER_CONST", "REAL_CONST", "PROCEDURE, WRITELN",
            "STRING", "IF", "THEN", "EQUALS", "NOTEQUALS", "GREATER", "LESS"};

Token::Token()
{

}
