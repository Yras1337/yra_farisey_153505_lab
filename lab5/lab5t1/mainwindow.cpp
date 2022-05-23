#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "queue.h"
#include <QMessageBox>
#include <iostream>
Deque deq;

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
    QString s;
    for (int i = 0; i < deq.length(); i++){
        s += QString::number(deq[i]);
        if (i != deq.length() - 1){
            s += ',';
        }
    }
    ui->textEdit->setText(s);
}
void MainWindow::on_pushButton_clicked()
{
    std::string s = ui->textEdit_2->toPlainText().toStdString();
    if (s.size() >= 8){
        QMessageBox::information(this, "error", "write 0 <= num < 1e8");
        return;
    }
    for (int i = 0; i < s.size(); i++){
        if (s[i] < '0' || s[i] > '9'){
            QMessageBox::information(this, "error", "write 0 <= num < 1e8");
            return;
        }
    }
    deq.push_back(ui->textEdit_2->toPlainText().toInt());
    upd();
}



void MainWindow::on_pushButton_2_clicked()
{
    std::string s = ui->textEdit_3->toPlainText().toStdString();
    if (s.size() >= 8){
        QMessageBox::information(this, "error", "write 0 <= num < 1e8");
        return;
    }
    for (int i = 0; i < s.size(); i++){
        if (s[i] < '0' || s[i] > '9'){
            QMessageBox::information(this, "error", "write 0 <= num < 1e8");
            return;
        }
    }
    deq.push_front(ui->textEdit_3->toPlainText().toInt());
    upd();
}


void MainWindow::on_pushButton_3_clicked()
{
    deq.pop_back();
    upd();
}


void MainWindow::on_pushButton_4_clicked()
{
    deq.pop_front();
    upd();
}


void MainWindow::on_pushButton_5_clicked()
{
    deq.clear();
    upd();
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit_7->setText(QString::number(deq.length()));
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit_8->setText(QString::number(deq.empty()));
}

