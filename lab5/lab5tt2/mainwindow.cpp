#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
list < char > code, buf;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::ifstream in("C:\\Users\\Lenovo\\Documents\\lab5tt2\\mainwindow.cpp");
    while(!in.eof()){
        char c = in.get();
        code.add(c);
    }
    ui->textEdit->setText(QString::fromStdString(code.get_string()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QTextCursor c = ui->textEdit->textCursor();
    QString s = c.selectedText();
    for (int i = 0; i < s.size(); i++){
        buf.add(s[i].toLatin1());
    }
    ui->textEdit_2->setText(QString::fromStdString(buf.get_string()));
}


void MainWindow::on_pushButton_2_clicked()
{
    QTextCursor c = ui->textEdit->textCursor();
    int tekPos = c.position();
    QString s = ui->textEdit->toPlainText();
    int y = 0;
    for (int i = 0; i < s.size(); i++){
        if (i == tekPos){
            break;
        }
        if (s[i] == '\n'){
            y++;
        }
    }
    int fPos = 0;
    for (int i = 0; i < code.size(); i++){
        if (code.getItem(i) == '\n'){
            fPos++;
        }
        if (fPos == y){
            int p = i;
            while(buf.size()){
                char c = buf.getItem(0);
                buf.delItem(0);
                code.insertItem(code.getNode(p), c);
                p++;
            }
        }
    }
    ui->textEdit->setText(QString::fromStdString(code.get_string()));
    ui->textEdit_2->clear();
}

