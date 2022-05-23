#include "mainwindow.h"
#include "mstack.h"
#include <QApplication>

int main()
{
    mStack < int > a;
    for (int i = 1; i <= 5; i++){
        a.push(i);
        cout << a.top() << endl;
    }
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}
