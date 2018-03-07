#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>

#include "source/interpreter.h"
#include "source/lexer.h"
#include "source/ast/ast.h"
#include "source/errorhandler.h"
#include <QFile>
#include <QTextStream>


/*void TestSingleLine() {
    QTextStream s(stdin);
    QString text = "";
    while (text!="q") {
        text = s.readLine();
        QStringList lst;
        Lexer lexer = Lexer(text, lst);
        Parser parser = Parser(lexer);

        Interpreter interpreter = Interpreter(parser);

        interpreter.Interpret();
        //qDebug() << result;
    }

}
*/
QString ReadFile(QString fileName, QStringList& lst) {
    if (!QFile::exists(fileName)) {
        qDebug() << "Cannot open file: " << fileName;
        exit(1);
    }
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QString text = "";
    while(!in.atEnd()) {
        QString t = in.readLine();
        text += t;
        lst<<t;
    }

    file.close();
    return text;

}


/*void ParseFile(QString fileName) {
    QStringList lst;
    QString text = ReadFile(fileName, lst);
    Lexer lexer = Lexer(text, lst);
    Parser parser = Parser(&lexer);
    Interpreter interpreter = Interpreter(&parser);
    interpreter.Interpret();

}
*/
int main(int argc, char *argv[])
{
    ErrorHandler::e.m_level = ErrorHandler::e.DEBUG_LOW;
    ErrorHandler::e.m_level = ErrorHandler::e.ERROR_ONLY;
    //ParseFile("..\\pmm\\pmm\\test.ras");
}
