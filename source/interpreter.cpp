#include "interpreter.h"

Interpreter::Interpreter(Parser p)
{
    m_parser = p;
}

float Interpreter::Visit(Node* n)
{
    n->Execute(nullptr, 0);
    return 0;
}

float Interpreter::Interpret()
{
    Node* tree = nullptr;
    try {
        tree = m_parser.Parse();
    } catch (FatalErrorException e) {
        ErrorHandler::e.CatchError(e, "Error during parsing:");
    }
    if (tree!=nullptr)
        try {
        Visit(tree);
    } catch (FatalErrorException e) {
        ErrorHandler::e.CatchError(e, "Error during interpreting");
    }

 //   qDebug() << "\n\nDeleting...";
//    tree->Delete();
  //  qDebug() << "Done deleting";
    return 0;
}
