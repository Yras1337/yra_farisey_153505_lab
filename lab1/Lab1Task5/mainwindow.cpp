#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <fstream>
#include <iostream>
#include "date.h"
#include "secondwindow.h"
string globDate;
using namespace std;
Date *dates;
QString global_file_name;
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


void MainWindow::on_pushButton_clicked()
{
    if (ui->tableWidget->currentItem() == 0){
        return;
    }
    QTableWidgetItem *itm = ui->tableWidget->currentItem();
    QMessageBox::information(this, "in", itm->text());
}
bool num_check(string s){
    for (int i = 0; i < int(s.size()); i++){
        if (s[i] == '.'){
            if (i == 2 || i == 5){
                continue;
            }
            else{
                return 0;
            }
        }
        if (s[i] < '0' || s[i] > '9'){
            return 0;
        }
    }
    return 1;
}
void MainWindow::on_MenuFileOpen_triggered()
{
    global_file_name = QFileDialog::getOpenFileName(this, "Выберите", QDir::currentPath(), "*.txt");
    QMessageBox::information(this, "debug", global_file_name);
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ifstream file(filePath);
    string s;
    vector < string > newData;
    while (file >> s){
        if (s.size() != 10 || s[2] != '.' || s[5] != '.' || !num_check(s)){
            file.close();
            QMessageBox::information(this, "in", "error, invali file");
            return;
        }
        newData.push_back(s);
    }
    file.close();
    delete dates;
    dates = new Date[newData.size()];
    for (int i = 0; i < int(newData.size()); i++){
        dates[i] = newData[i];
    }
    ui->tableWidget->setRowCount(newData.size());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "date" << "prev date" << "next date" << "birthday date");
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i){
        QTableWidgetItem *itm1 = new QTableWidgetItem(QString::fromStdString(dates[i].formatDate));
        ui->tableWidget->setItem(i, 0, itm1);
        QTableWidgetItem *itm2 = new QTableWidgetItem(QString::fromStdString(dates[i].PreviousDay().formatDate));
        ui->tableWidget->setItem(i, 1, itm2);
        QTableWidgetItem *itm3 = new QTableWidgetItem(QString::fromStdString(dates[i].nextDay().formatDate));
        ui->tableWidget->setItem(i, 2, itm3);
    }
}

bool isNum(char x){
    if (x < '0' || x > '9'){
        return 0;
    }
    return 1;
}
bool check_cell_data(QTableWidgetItem *itm, string itmDataFormat){
    int curColum = itm->column();
    if (curColum != 0){
        return 0;
    }
    string birthDate = itmDataFormat;
    if (birthDate[2] != '.' || birthDate[5] != '.' || birthDate.size() != 10){
        return 0;
    }
    if (!isNum(birthDate[0]) || !isNum(birthDate[1]) || !isNum(birthDate[3]) || !isNum(birthDate[4]) || !isNum(birthDate[6]) || !isNum(birthDate[7]) || !isNum(birthDate[8]) || !isNum(birthDate[9])){
        return 0;
    }
    Date birthDay = birthDate;
    if (!birthDay.valid_check()){
        return 0;
    }
    return 1;
}
void MainWindow::on_pushButton_2_clicked()
{
    QTableWidgetItem *itm = ui->tableWidget->currentItem();
    if (itm == 0){
        QMessageBox::information(this, "error", "invalid date format");
        return;
    }
    string birthDate = ui->tableWidget->item(itm->row(), 3)->text().toStdString();
    if (!check_cell_data(itm, birthDate)){
        QMessageBox::information(this, "error", "invalid date format");
        return;
    }
    QMessageBox::information(this, "result", tr("%1").arg(dates[itm->row()].DaysTillYourBithday(birthDate)));
}

void MainWindow::on_M_triggered()
{
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ofstream file_out(filePath);
    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
        if (ui->tableWidget->item(i, 0) == 0){
            continue;
        }
        file_out << ui->tableWidget->item(i, 0)->text().toStdString() << endl;
    }
    file_out.close();
}

void MainWindow::on_tableWidget_cellChanged(int row, int column){
    if (row != 0 || ui->tableWidget->item(row, column) == 0){
        return;
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QTableWidgetItem *itm = ui->tableWidget->currentItem();
    if (itm == 0){
        QMessageBox::information(this, "error", "invalid cell");
        return;
    }
    string curDate = itm->text().toStdString();
    if (curDate[2] != '.' || curDate[5] != '.' || curDate.size() != 10){
        QMessageBox::information(this, "error", "invalid cell data");
        return;
    }
    if (!isNum(curDate[0]) || !isNum(curDate[1]) || !isNum(curDate[3]) || !isNum(curDate[4]) || !isNum(curDate[6]) || !isNum(curDate[7]) || !isNum(curDate[8]) || !isNum(curDate[9])){
        QMessageBox::information(this, "error", "invalid cell data");
        return;
    }
    Date birthDay = curDate;
    if (!birthDay.valid_check()){
        QMessageBox::information(this, "error", "invalid cell data");
        return;
    }
    globDate = curDate;
    SecondWindow window;
    window.setModal(true);
    window.exec();
}

