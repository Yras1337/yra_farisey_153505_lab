#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mStack.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <fstream>
#include <iostream>
#include <QString>
using namespace std;
QString global_file_name;
struct mData{
    char type;
    int xPos, yPos;
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    global_file_name = QFileDialog::getOpenFileName(this, "Выберите", QDir::currentPath());
    QMessageBox::information(this, "debug", global_file_name);
    if(global_file_name==nullptr) return;
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ifstream file(filePath);
    string s;
    QString str;
    while (!file.eof()){
        getline(file, s);
        str += QString::fromStdString(s);
        str +='\n';
    }
    cout << str.toStdString() << endl;
    ui->textEdit->setText(str);
}


void MainWindow::on_pushButton_clicked()
{
    string str = ui->textEdit->toPlainText().toStdString();
    bool isCh = 0;
    bool isStr = 0;
    int x = 1;
    int y = 1;
    mStack < mData > Stack1;
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            x++;
            y = 1;
            continue;
        }
        if (str[i] == '\'' && isStr == 0){
            isCh^=1;
        }
        if (str[i] == '"' && isCh == 0){
            isStr^=1;
        }
        if (isCh && isStr){
            y++;
            continue;
        }
        if (str[i] == '{'){
            Stack1.push({'{', x, y});
        }
        if (str[i] == '('){
            Stack1.push({'(', x, y});
        }
        if (str[i] == '['){
            Stack1.push({'[', x, y});
        }
        if (!Stack1.empty()){
        //    cout << Stack1.top().type << endl;
        }
        if (str[i] == '}'){
            if (Stack1.empty() || Stack1.top().type != '{'){
            //    cout << Stack1.top().type << endl;
                QMessageBox::information(this, "info", "{ error" + QString::number(x) + " " + QString::number(y));
                return;
            }
            else{
                Stack1.pop();
            }
        }

        if (str[i] == ')'){
            if (Stack1.empty() || Stack1.top().type != '('){
                QMessageBox::information(this, "info", "( error" + QString::number(x) + " " + QString::number(y));
                return;
            }
            else{
              //  cout << Stack1.top().type << endl;
                Stack1.pop();
            }
        }
        if (str[i] == ']'){
            if (Stack1.empty() || Stack1.top().type != '['){
                QMessageBox::information(this, "info", "[ error" + QString::number(x) + " " + QString::number(y));
                return;
            }
            else{
                Stack1.pop();
            }
        }
        y++;
    }
    if (!Stack1.empty()){
        QMessageBox::information(this, "info", "В коде не хватает закрывающих скобок");
    }
    else{
        QMessageBox::information(this, "info", "все правильно");
    }
}

