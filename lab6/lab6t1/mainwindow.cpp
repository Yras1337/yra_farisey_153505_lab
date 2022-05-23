#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "binTree.h"
#include <iostream>
Map < int, std::string > a;
std::vector < int > keys;
int type = 1;
bool is_val(std::string buf){
    if (buf.size() > 7 || buf.empty()){
        return 0;
    }
    for (int i = 0; i < buf.size(); i++){
        if (buf[i] < '0' || buf[i] > '9'){
            return 0;
        }
    }
    return 1;
}
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
void MainWindow::upd(int type){
    std::vector < std::pair < int, std::pair < int, int > > > b;
    if (type == 1){
        a.clrBuf();
        a.ob1();
        b = a.getBuf();

    }
    if (type == 2){
        a.clrBuf();
        a.ob2();
        b = a.getBuf();
    }
    if (type == 3){
        a.clrBuf();
        a.ob3();
        b = a.getBuf();
        reverse(b.begin(), b.end());
    }
    QString s;
    for (int i = 0; i < b.size(); i++){
        s += "key = " + QString::number(b[i].first) + ", value = " + QString::fromStdString(a[b[i].first]) + ";\n";//", left key = " + QString::number(b[i].second.first) + ", right key = " + QString::number(b[i].second.second) + '\n';
        s += ' ';
    }
    std::cout << std::endl;
    ui->textEdit->setText(s);
}

void MainWindow::on_pushButton_2_clicked()
{
    type = 1;
    upd(type);
}


void MainWindow::on_pushButton_6_clicked()
{
    type = 2;
    upd(type);
}


void MainWindow::on_pushButton_7_clicked()
{
    type = 3;
    upd(type);
}


void MainWindow::on_pushButton_clicked()
{
    std::string buf = ui->textEdit_2->toPlainText().toStdString();
    if (!is_val(buf)){
        return;
    }
    int x = stoi(buf);
    std::string str = ui->textEdit_3->toPlainText().toStdString();
    if (!str.size()){
        return;
    }
    keys.push_back(x);
    a.insert({x, str});
    upd(type);
}


void MainWindow::on_pushButton_4_clicked()
{
    std::string buf = ui->textEdit_5->toPlainText().toStdString();
    if (!is_val(buf)){
        return;
    }
    int x = stoi(buf);
    a.erase(x);
    upd(type);
}


void MainWindow::on_pushButton_5_clicked()
{
    a.clear();
    upd(type);
}


void MainWindow::on_pushButton_8_clicked()
{
    std::string buf = ui->textEdit_6->toPlainText().toStdString();
    if (!is_val(buf)){
        return;
    }
    int x = stoi(buf);
    if (a.find(x)){
        std::cout << a[x] << std::endl;
        ui->textEdit_6->setText(QString::fromStdString(a[x]));
    }
    else{
        ui->textEdit_6->setText("");
    }
}

