#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <fstream>
#include <iostream>
#include "firma.h"
#include "date.h"
using namespace std;
Firma *Info;
QString global_file_name;
bool flaag=false;
int count_work;
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
    global_file_name = QFileDialog::getOpenFileName(this, "Выберите", QDir::currentPath(), "*.txt");
    QMessageBox::information(this, "debug", global_file_name);
    if(global_file_name==nullptr) return;
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ifstream file(filePath);
    string s;
    vector < Firma > newFirm;

    delete Info;
    ui->listWidget->clear();
    //ui->comboBox->clear();
    count_work = 0;
    int flag=0;
    if(!file.eof()) {
        string test;
        file>>test;
        if (test!="File_For_Task4_Lab1") {
            flag = 1;
        }
    } else {
        flag = 1;
    }
    while (!file.eof()){
        string s1, s2, s3, s4, s5, s6, s7;
        file >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7;
        count_work++;
    }
    file.close();

    if ( flag == 1) {
        QMessageBox::information(this, "Ошибонька.", "Неверный формат файла(");
    }
    else {
        Info = new Firma[count_work];
        file.open(filePath);
        string test;
        file>>test;
        for (int i = 0; i < count_work; i++){
            string s1, s2, s3, s4, s5, s6, s7;
            file >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7;
            Info[i].Init(s1, s2, s3, s4, s5, s6, s7);
            ui->listWidget->addItem("Работа №" + QString::number(i));
            ui->comboBox->addItem("Работа №" + QString::number(i));
        }
        file.close();
    }

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (count_work==0) return;
        ui->textEdit->setText(QString::fromStdString(Info[index].F));
        ui->textEdit_2->setText(QString::fromStdString(Info[index].I));
        ui->textEdit_3->setText(QString::fromStdString(Info[index].O));
        ui->textEdit_4->setText(QString::fromStdString(Info[index].projName));
        ui->textEdit_5->setText(QString::fromStdString(Info[index].Task));
        ui->textEdit_6->setText(QString::fromStdString(Info[index].dateStart));
        ui->textEdit_7->setText(QString::fromStdString(Info[index].dateEnd));



}


void MainWindow::on_pushButton_clicked()
{
    if(ui->listWidget->currentRow()==-1) {QMessageBox::information(this, "info", "Выберите Работу"); return;}
    int id = ui->listWidget->currentRow();
    QMessageBox::information(this, "info", QString::fromStdString(Info[id].toStrFormat()));
}


void MainWindow::on_pushButton_2_clicked()
{
    if(ui->listWidget->count()==0) {QMessageBox::information(this, "info", "Выберите Работу"); return;}
    Firma* Info2 = new Firma[count_work];
    for(int i=0; i<count_work; ++i){
        Info2[i]=Info[i];
    }

    for(int i=0; i<count_work; ++i){
        Firma temp = Info2[i];
        for(int j = i+1; j<count_work; ++j) {
            if(Info2[i].toSort()>Info2[j].toSort()){
                temp = Info2[i];
                Info2[i]=Info2[j];
                Info2[j]=temp;
            }
        }
    }
    string ans;

    for(int i=0; i<count_work; ++i){
        ans+=Info2[i].projName+" ("+Info2[i].dateEnd+")\n";
    }
    QMessageBox::information(this, "info", QString::fromStdString(ans));
    delete[] Info2;

}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->listWidget->count()==0) {QMessageBox::information(this, "info", "Выберите Работу"); return;}
    string ans;
    for(int i=0; i<count_work; ++i) {
        ans+=Info[i].F+' '+Info[i].I+' '+Info[i].O+" ("+to_string(Info[i].day)+" дней работал(а) в последний месяц)\n";
    }
    QMessageBox::information(this, "info", QString::fromStdString(ans));
}


void MainWindow::on_pushButton_4_clicked()
{
    if(ui->listWidget->count()==0) {QMessageBox::information(this, "info", "Выберите Работу"); return;}
    string ans;
    for(int i=0; i<count_work; ++i) {
            ans+=Info[i].F+' '+Info[i].I+' '+Info[i].O+" работал над: "+Info[i].Task+"\n";
        }
        QMessageBox::information(this, "info", QString::fromStdString(ans));
}


void MainWindow::on_action_2_triggered()
{
    global_file_name = QFileDialog::getSaveFileName(this, "Выберите", ".", "*.txt");
    QMessageBox::information(this, "debug", global_file_name);
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ofstream file_out(filePath);

    file_out<<"File_For_Task4_Lab1";
    for(int i=0; i<count_work; ++i) {
        file_out<<"\n";
        file_out<<Info[i].toStrFile();
    }
    file_out.close();

}

void MainWindow::on_pushButton_6_clicked()
{

    if(ui->listWidget->count()==0) {QMessageBox::information(this, "info", "Выберите Работу"); return;}
    int del_id = ui->comboBox->currentIndex();
    Firma *temp = new Firma[count_work-1];
    int pos = 0;
    for (int i = 0; i < count_work; i++){
        ui->listWidget->takeItem(0);
        if (i == del_id){
            continue;
        }
        temp[pos] = Info[i];
        pos++;
    }
    /*while (ui->comboBox->count() > 0){
        flaag=true;
        ui->comboBox->removeItem(0);
    }*/
    count_work--;
    delete[] Info;
    Info = temp;

    for (int i = 0; i < count_work; i++){
        ui->listWidget->addItem("Работа №" + QString::number(i));
        ui->comboBox->addItem("Работа №" + QString::number(i));
    }

}


void MainWindow::on_pushButton_5_clicked()
{
    Firma temp;
    std::string s=ui->textEdit_8->toPlainText().toStdString();
    if(s==""){
        QMessageBox::information(this, "Ошибка", "не хватает данных");
        return;
    }
    for(int i=0;s[i];i++){
        if(s[i]==' '){
            QMessageBox::information(this, "Ошибка", "фамилия:не должно быть пробела");
            return;
        }
    }
    temp.F=s;
    s=ui->textEdit_12->toPlainText().toStdString();
    if(s==""){
        QMessageBox::information(this, "Ошибка", "не хватает данных");
        return;
    }
    for(int i=0;s[i];i++){
        if(s[i]==' '){
            QMessageBox::information(this, "Ошибка", "имя:не должно быть пробела");
            return;
        }
    }
    temp.I=s;
    s=ui->textEdit_10->toPlainText().toStdString();
    if(s==""){
        QMessageBox::information(this, "Ошибка", "не хватает данных");
        return;
    }
    for(int i=0;s[i];i++){
        if(s[i]==' '){
            QMessageBox::information(this, "Ошибка", "отчество:не должно быть пробела");
            return;
        }
    }
    temp.O=s;
    s=ui->textEdit_9->toPlainText().toStdString();
    if(s==""){
        QMessageBox::information(this, "Ошибка", "не хватает данных");
        return;
    }
    for(int i=0;s[i];i++){
        if(s[i]==' '){
            QMessageBox::information(this, "Ошибка", "проект:не должно быть пробела");
            return;
        }
    }
    temp.projName=s;
    s=ui->textEdit_11->toPlainText().toStdString();
    if(s==""){
        QMessageBox::information(this, "Ошибка", "не хватает данных");
        return;
    }
    for(int i=0;s[i];i++){
        if(s[i]==' '){
            QMessageBox::information(this, "Ошибка", "задача:не должно быть пробела");
            return;
        }
    }
    temp.Task=s;
    s=ui->textEdit_13->toPlainText().toStdString();
    if(s.size()!=10) {
        QMessageBox::information(this, "error", "неверные данные");
        return;
    }
    if(s[2]!='.'||s[5]!='.') {
        QMessageBox::information(this, "error", "неверные данные");
        return;
    }
    for(int i=0;i<10;i++) {
        if(i==2 || i==5) continue;
        if((int)s[i]<48 || (int)s[i]>57){
            QMessageBox::information(this, "error", "неверные данные");
            return;
        }

    }
    Date Check = s;
    if(!Check.validCheck()) {
        QMessageBox::information(this, "error", "неверооные данные");
        return;
    }
    temp.dateStart=s;
    temp.Task=s;
    s=ui->textEdit_14->toPlainText().toStdString();
    if(s.size()!=10) {
        QMessageBox::information(this, "error", "неверные данные");
        return;
    }
    if(s[2]!='.'||s[5]!='.') {
        QMessageBox::information(this, "error", "неверные данные");
        return;
    }
    for(int i=0;i<10;i++) {
        if(i==2 || i==5) continue;
        if((int)s[i]<48 || (int)s[i]>57){
            QMessageBox::information(this, "error", "неверные данные");
            return;
        }

    }
    Check = s;
    if(!Check.validCheck()) {
        QMessageBox::information(this, "error", "неверные данные");
        return;
    }
    Firma temp2;
    temp2.dateEnd=temp.dateStart;
    temp.dateEnd=s;
    if(temp.toSort()<temp2.toSort()) {
        QMessageBox::information(this, "error", "Дата начала должна быть ДО даты окончания");
        return;
    }




    Firma *tempo = new Firma[count_work+1];
    for(int i=0;i<count_work;i++){
        tempo[i]=Info[i];
    }
    tempo[count_work]=temp;
    delete[] Info;
    Info = tempo;

    ui->listWidget->addItem("Работа №" + QString::number(count_work));
    ui->comboBox->addItem("Работа №" + QString::number(count_work));
    count_work++;
    ui->comboBox->setCurrentIndex(0);
}

