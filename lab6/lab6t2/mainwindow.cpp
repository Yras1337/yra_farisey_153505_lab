#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hashMap.h"
#include <QString>
#include <iostream>
#include <string>
MyHashMap < int, int > a;
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

void MainWindow::upd(){
    QString buf;
    for (size_t i = 0; i < a.size(); i++){
        for (size_t j = 0; j < a[i]; j++){
            buf += QString::number(i);
            buf += " ";
        }
    }
    ui->textEdit->setText(buf);
}
bool is_val(std::string buf){
    if (buf.size() > 5 || buf.empty()){
        return 0;
    }
    for (int i = 0; i < buf.size(); i++){
        if (buf[i] < '0' || buf[i] > '9'){
            return 0;
        }
    }
    return 1;
}
void MainWindow::on_pushButton_clicked()
{
    std::string buf = ui->textEdit_2->toPlainText().toStdString();
    if (!is_val(buf)){
        return;
    }
    int x = stoi(buf);
    a[x]++;
    upd();
}


void MainWindow::on_pushButton_2_clicked()
{
    std::string buf = ui->textEdit_3->toPlainText().toStdString();
    if (!is_val(buf)){
        return;
    }
    int x = stoi(buf);
    a.erase(x);
    upd();
}


void MainWindow::on_pushButton_3_clicked()
{
    int avg = 0, kol = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] != 0){
            kol += a[i];
            avg += a[i] * i;
        }
    }
    if (kol){
        avg /= kol;
    }
    kol = 0;
    for (int i = 0; i < a.size(); i++){
        if (i > avg){
            kol += a[i];
        }
    }
    ui->textEdit_4->setText(QString::number(kol));
}


void MainWindow::on_pushButton_4_clicked()
{
    std::string buf = ui->textEdit_5->toPlainText().toStdString();
    if (!is_val(buf)){
        return;
    }
    int x = stoi(buf);
    if (a[x] > 0){
        a[x]--;
    }
    upd();
}


void MainWindow::on_pushButton_5_clicked()
{
    a.clear();
    upd();
}

