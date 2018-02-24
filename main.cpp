#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>

#include "interpreter.h"
#include "lexer.h"
#include "ast.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    //return a.exec();
    qDebug() << "heisann";
    QTextStream s(stdin);
    QString text = "";
    while (text!="q") {
        text = s.readLine();

        Lexer lexer = Lexer(text);
        Parser parser = Parser(lexer);

        Interpreter interpreter = Interpreter(parser);

        int result = interpreter.Interpret();
        qDebug() << result;
    }


}
