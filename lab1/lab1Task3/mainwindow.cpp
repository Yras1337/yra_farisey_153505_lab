#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <fstream>
#include <iostream>
#include "data.h"
#include "secondwindow.h"
using namespace std;
Data *Info;
QString global_file_name;
int count_data;
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
bool num_check(char c){
    if (c < '0' || c > '9'){
        return 0;
    }
    return 1;
}
bool num_check(string s){
    if (s.size() > 9){
        return 0;
    }
    for (int i = 0; i < int(s.size()); i++){
        if (!num_check(s[i])){
            return 0;
        }
    }
    return 1;
}
void MainWindow::on_action_2_triggered()
{
    global_file_name = QFileDialog::getOpenFileName(this, "Выберите", QDir::currentPath(), "*.txt");
    //QMessageBox::information(this, "debug", global_file_name);
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ifstream file(filePath);
    string s;
    vector < Data > newData;
    while (ui->listWidget->count() > 0){
        ui->listWidget->takeItem(0);
    }
    while (ui->comboBox->count() > 0){
        ui->comboBox->removeItem(0);
    }
    if (count_data != 0){
        delete[] Info;
    }
    count_data = 0;
    if (file.eof()){
        cout << "Deb" << endl;
        QMessageBox::information(this, "warning", "file is empty");
        return;
    }
    while (!file.eof()){
        string s1, s2, s3;
        string n1, n2, n3, n4, n5;
        file >> s1;
        if (count_data == 0 && s1.size() == 0){
            QMessageBox::information(this, "warning", "empty file");
            file.close();
            return;

        }
        if (s1[2] != '.' && s1[5] != '.'){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        if (file.eof()){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> n1;
        if (file.eof() || !num_check(n1)){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> s2;
        if (file.eof()){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> s3;
        if (file.eof() || s3.size() < 3 || s3[2] != ':'){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> n2;
        if (file.eof() || !num_check(n2)){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> n3;
        if (file.eof() || !num_check(n3)){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> n4;
        if (file.eof() || !num_check(n4)){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        file >> n5;
        if (!num_check(n5)){
            QMessageBox::information(this, "erroe", "invalid file");
            file.close();
            return;
        }
        count_data++;
    }
    file.close();
    Info = new Data[count_data];
    file.open(filePath);
    for (int i = 0; i < count_data; i++){
        string s1, s2, s3;
        int n1, n2, n3, n4, n5;
        file >> s1 >> n1 >> s2 >> s3 >> n2 >> n3 >> n4 >> n5;
        Info[i].add(s1, n1, s2, s3, n2, n3, n4, n5);
        ui->listWidget->addItem("рейс #" + QString::number(i));
        ui->comboBox->addItem("рейс #" + QString::number(i));
    }
}
void MainWindow::on_pushButton_clicked()
{
    if (ui->listWidget->currentRow() == -1){
        QMessageBox::information(this, "erroe", "error");
        return;
    }
    int id = ui->listWidget->currentRow();
    QMessageBox::information(this, "info", QString::fromStdString(Info[id].to_str_format()));
}
void MainWindow::on_pushButton_2_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); i++){
        cout << Info[i].get_day_of_week() << endl;
    }
    SecondWindow window;
    window.setModal(true);
    window.exec();
}
void MainWindow::on_action_triggered()
{
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ofstream file_out(filePath);
    for (int i = 0; i < count_data; i++){
        file_out << Info[i].to_str() << endl;
    }
    file_out.close();
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (count_data == 0){
        //QMessageBox::information(this, "error", "error");
        return;
    }
    ui->textEdit_2->setText(QString::fromStdString(Info[index].get_date()));
    ui->textEdit_3->setText(QString::number(Info[index].get_nReis()));
    ui->textEdit_4->setText(QString::fromStdString(Info[index].get_location()));
    ui->textEdit_5->setText(QString::fromStdString(Info[index].get_rTime()));
    ui->textEdit_6->setText(QString::number(Info[index].get_kPlace()));
    ui->textEdit_7->setText(QString::number(Info[index].get_pPlace()));
    ui->textEdit_8->setText(QString::number(Info[index].get_kFreePlase()));
    ui->textEdit_9->setText(QString::number(Info[index].get_pFreePlase()));
}
void MainWindow::on_pushButton_4_clicked()
{
    if (count_data == 0){
        QMessageBox::information(this, "error", "error");
        return;
    }
    string new_data = ui->textEdit_2->toPlainText().toStdString();
    if (new_data.size() == 0 || new_data.size() != 10 || !num_check(new_data[0]) || !num_check(new_data[1])
            || !num_check(new_data[3]) || !num_check(new_data[4]) || !num_check(new_data[6]) || !num_check(new_data[7]) || !num_check(new_data[8])
            || !num_check(new_data[9]) || new_data[2] != '.' || new_data[5] != '.'){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    string temp = ui->textEdit_3->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_r = ui->textEdit_3->toPlainText().toInt();
    string new_loc = ui->textEdit_4->toPlainText().toStdString();
    if (new_loc.size() == 0){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    string new_time = ui->textEdit_5->toPlainText().toStdString();
    if (new_time.size() != 5 || new_time[2] != ':'){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    temp = ui->textEdit_6->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_kp = ui->textEdit_6->toPlainText().toInt();
    temp = ui->textEdit_7->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_pp = ui->textEdit_7->toPlainText().toInt();
    temp = ui->textEdit_8->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_kfp = ui->textEdit_8->toPlainText().toInt();
    temp = ui->textEdit_9->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_pfp = ui->textEdit_9->toPlainText().toInt();
    if (ui->comboBox->currentIndex() == -1 || ui->listWidget->size().isEmpty()){
        QMessageBox::information(this, "erroe", "error");
        return;
    }
    Info[ui->comboBox->currentIndex()].add(new_data, new_r, new_loc, new_time, new_kp, new_pp, new_kfp, new_pfp);
}


void MainWindow::on_pushButton_5_clicked()
{
    if (count_data == 0 || ui->comboBox->currentIndex() == -1 || ui->comboBox->size().isEmpty() || ui->listWidget->size().isEmpty()){
        QMessageBox::information(this, "erroe", "error");
        return;
    }
    if (count_data == 1){
        count_data = 0;
        delete[] Info;
        ui->listWidget->clear();
        //ui->comboBox->addItem("");
        ui->comboBox->removeItem(0);
        ui->textEdit_2->setText("");
        ui->textEdit_3->setText("");
        ui->textEdit_4->setText("");
        ui->textEdit_5->setText("");
        ui->textEdit_6->setText("");
        ui->textEdit_7->setText("");
        ui->textEdit_8->setText("");
        ui->textEdit_9->setText("");
        return;
    }
    int del_id = ui->comboBox->currentIndex();
    Data *temp = new Data[count_data - 1];
    int pos = 0;
    for (int i = 0; i < count_data; i++){
        if (i == del_id){
            continue;
        }
        temp[pos] = Info[i];
        pos++;
    }
    count_data--;
    delete[] Info;
    Info = temp;
    for (int i = 0; i < count_data; i++){
        ui->listWidget->addItem("рейс #" + QString::number(i));
        ui->comboBox->addItem("рейс #" + QString::number(i));
    }
    while (ui->listWidget->count() > count_data){
        ui->listWidget->takeItem(0);
    }
    while (ui->comboBox->count() > count_data){
        ui->comboBox->removeItem(0);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    string ans;
    string gorod = ui->textEdit->toPlainText().toStdString();
    for (int i = 0; i < count_data; i++){
        if (Info[i].get_location() == gorod){
            ans += "рейс #" + to_string(i) + " продано билетов: " + to_string(Info[i].get_kPlace() - Info[i].get_kFreePlase() - Info[i].get_pFreePlase() + Info[i].get_pPlace());
            ans += '\n';
        }
    }
    if (ans.size() == 0){
        QMessageBox::information(this, "error", "рейсов в этот город не найдено");
    }
    else{
        QMessageBox::information(this, "info", QString::fromStdString(ans));
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    string new_data = ui->textEdit_2->toPlainText().toStdString();
    if (new_data.size() != 10 || !num_check(new_data[0]) || !num_check(new_data[1])
            || !num_check(new_data[3]) || !num_check(new_data[4]) || !num_check(new_data[6]) || !num_check(new_data[7]) || !num_check(new_data[8])
            || !num_check(new_data[9]) || new_data[2] != '.' || new_data[5] != '.'){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    string temp = ui->textEdit_3->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_r = ui->textEdit_3->toPlainText().toInt();
    string new_loc = ui->textEdit_4->toPlainText().toStdString();
    if (new_loc.size() == 0){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    string new_time = ui->textEdit_5->toPlainText().toStdString();
    if (new_time.size() != 5 || new_time[2] != ':'){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    temp = ui->textEdit_6->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_kp = ui->textEdit_6->toPlainText().toInt();
    temp = ui->textEdit_7->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_pp = ui->textEdit_7->toPlainText().toInt();
    temp = ui->textEdit_8->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_kfp = ui->textEdit_8->toPlainText().toInt();
    temp = ui->textEdit_9->toPlainText().toStdString();
    if (temp.size() == 0 || !num_check(temp)){
        QMessageBox::information(this, "erroe", "invalid input");
        return;
    }
    int new_pfp = ui->textEdit_9->toPlainText().toInt();
    Data *tmp = new Data[count_data + 1];
    count_data++;
    for (int i = 0; i < count_data - 1; i++){
        tmp[i] = Info[i];
    }
    tmp[count_data - 1].add(new_data, new_r, new_loc, new_time, new_kp, new_pp, new_kfp, new_pfp);
    delete[] Info;
    Info = tmp;
    ui->listWidget->addItem("рейс #" + QString::number(count_data - 1));
    ui->comboBox->addItem("рейс #" + QString::number(count_data - 1));
}

