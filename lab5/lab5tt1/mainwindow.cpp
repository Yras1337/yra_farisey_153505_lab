#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "queue.h"
#include <string>
#include <QString>
mQueue < std::string > que;
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
    std::cout << que.size() << std::endl;
    for (int i = 0; i < que.size(); i++){
        if (!que.getItem(i).size()){
            continue;
        }
        s += que.getItem(i).c_str();
        if (i != que.size() - 1){
            s += ",";
        }
    }
    ui->textEdit->setText(s);
}
void MainWindow::on_pushButton_clicked()
{
    std::string s = ui->textEdit_2->toPlainText().toStdString();
    if (!s.size()){
        return;
    }
    que.add(s);
    upd();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!que.size()){
        return;
    }
    ui->textEdit_3->setText(QString::fromStdString(que.getItem(0)));
    que.delItem(0);
    upd();
}


void MainWindow::on_pushButton_3_clicked()
{
    if (que.size() == 0){
        return;
    }
    ui->textEdit_4->setText(QString::fromStdString(que.getItem(0)));
}


void MainWindow::on_pushButton_4_clicked()
{
    if (!que.size()){
        return;
    }
    que.clear();
    upd();
}


void MainWindow::on_pushButton_5_clicked()
{
    if (!que.size()){
        ui->textEdit_6->setText("true");
    }
    else{
        ui->textEdit_6->setText("false");
    }
}

