#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mList.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <fstream>
#include <iostream>
#include <QString>
#include <set>
using namespace std;
QString global_file_name;
struct Player{
    string town;
    string team;
    string name_1;
    string name_2;
    string name_3;
    string num;
    int age;
    int height;
    int weight;
};
mList<Player> List;
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
bool is_num(char c){
    if (c < '0' || c > '9'){
        return 0;
    }
    return 1;
}
bool is_num(string s){
    for (int i = 0; i < int(s.size()); i++){
        if (!is_num(s[i])){
            return 0;
        }
    }
    return 1;
}
void MainWindow::clear_text_widgets()
{
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    ui->textEdit_3->setText("");
    ui->textEdit_4->setText("");
    ui->textEdit_5->setText("");
    ui->textEdit_6->setText("");
    ui->textEdit_7->setText("");
    ui->textEdit_11->setText("");
    ui->textEdit_12->setText("");
    ui->comboBox->clear();
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
    Player tmp;
    clear_text_widgets();
    List.clear();
    int id = 0;
    while (!file.eof()){
        string s;
        file >> s;
        //cout << s << ' ';
        if (s.size() == 0){
            break;
        }
        if (file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }

        tmp.town = s;
        file >> s;
        if (file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.team = s;
        file >> s;
        if (file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.name_1 = s;
        file >> s;
        if (file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.name_2 = s;
        file >> s;
        if (file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.name_3 = s;
        file >> s;
        if (file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.num = s;
        file >> s;
        if (!is_num(s) || file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.age = stoi(s);
        file >> s;
        if (!is_num(s) || file.eof() || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.height = stoi(s);
        file >> s;
        if (!is_num(s) || s.size() == 0){
            QMessageBox::information(this, "error", "choose correct file");
            List.clear();
            clear_text_widgets();
            file.close();
            return;
        }
        tmp.weight = stoi(s);
        List.add(tmp);
        ui->comboBox->addItem("Player #" + QString::number(id));
        id++;
    }
    file.close();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (!List.size()){
        clear_text_widgets();
        return;
    }
    Player tmp = List.getItem(index);
    //cout << tmp.town << ' ' << tmp.team << endl;
    ui->textEdit->setText(QString::fromStdString(tmp.town));
    ui->textEdit_2->setText(QString::fromStdString(tmp.team));
    ui->textEdit_3->setText(QString::fromStdString(tmp.name_1));
    ui->textEdit_4->setText(QString::fromStdString(tmp.num));
    ui->textEdit_5->setText(QString::number(tmp.age));
    ui->textEdit_6->setText(QString::number(tmp.height));
    ui->textEdit_7->setText(QString::number(tmp.weight));
    ui->textEdit_11->setText(QString::fromStdString(tmp.name_2));
    ui->textEdit_12->setText(QString::fromStdString(tmp.name_3));
}


void MainWindow::on_action_2_triggered()
{
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    ofstream out(filePath);
    for (int i = 0; i < int(List.size()); i++){
        Player tmp = List.getItem(i);
        out << tmp.town << ' ' << tmp.team << ' ' << tmp.name_1 << ' ' << tmp.name_2 << ' ' << tmp.name_3 << ' ' << tmp.num << ' ' << tmp.age << ' ' << tmp.height << ' ' << tmp.weight << endl;
    }
    out.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!List.size()){
        return;
    }
    int curId = ui->comboBox->currentIndex();
    List.delItem(curId);
    ui->comboBox->removeItem(ui->comboBox->count() - 1);
    on_comboBox_currentIndexChanged(0);
}


void MainWindow::on_pushButton_3_clicked()
{
    Player tmp;
    tmp.town = ui->textEdit->toPlainText().toStdString();
    tmp.team = ui->textEdit_2->toPlainText().toStdString();
    tmp.name_1 = ui->textEdit_3->toPlainText().toStdString();
    tmp.name_2 = ui->textEdit_11->toPlainText().toStdString();
    tmp.name_3 = ui->textEdit_12->toPlainText().toStdString();
    tmp.num = ui->textEdit_4->toPlainText().toStdString();
    tmp.age = ui->textEdit_5->toPlainText().toInt();
    tmp.height = ui->textEdit_6->toPlainText().toInt();
    tmp.weight = ui->textEdit_7->toPlainText().toInt();
    List.add(tmp);
    ui->comboBox->addItem("Player #" + QString::number(ui->comboBox->count()));
    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());
}


void MainWindow::on_pushButton_clicked()
{
    string Str = ui->textEdit_8->toPlainText().toStdString();
    QString ans = "Result:\n";
    bool isFind = 0;
    for (int i = 0; i < int(List.size()); i++){
        Player tmp = List.getItem(i);
        if (Str == tmp.name_1){
            isFind = 1;
            ans += "Player #" + QString::number(i);
            ans += '\n';
        }
    }
    if (!isFind){
        ans += "empty";
    }
    QMessageBox::information(this, "result", ans);
}


void MainWindow::on_pushButton_4_clicked()
{
    int curValue = ui->textEdit_9->toPlainText().toInt();
    bool isFind = 0;
    QString ans = "Result:\n";
    for (int i = 0; i < int(List.size()); i++){
        Player tmp = List.getItem(i);
        if (curValue == tmp.weight){
            isFind = 1;
            ans += "Player #" + QString::number(i);
            ans += '\n';
        }
    }
    if (!isFind){
        ans += "empty";
    }
    QMessageBox::information(this, "result", ans);
}
void MainWindow::on_pushButton_5_clicked()
{
    int curValue = ui->textEdit_10->toPlainText().toInt();
    bool isFind = 0;
    QString ans = "Result:\n";
    set < string > check;
    for (int i = 0; i < int(List.size()); i++){
        Player toFind = List.getItem(i);
        bool isOk = 1;
        if (check.find(toFind.team) != check.end()){
            continue;
        }
        check.insert(toFind.team);
        for (int j = 0; j < int(List.size()); j++){
            Player tmp = List.getItem(j);
            if (tmp.team != toFind.team){
                continue;
            }
            if (tmp.height < curValue){
                isOk = 0;
                break;
            }
        }
        if (isOk){
            ans += QString::fromStdString(toFind.team);
            ans += '\n';
            isFind = 1;
        }
    }
    if (!isFind){
        ans += "empty";
    }
    QMessageBox::information(this, "result", ans);
}
void MainWindow::on_pushButton_6_clicked()
{
    double curValue = 1e9;
    QString ans = "Result:\n";
    string result;
    set < string > check;
    for (int i = 0; i < int(List.size()); i++){
        Player toFind = List.getItem(i);
        if (check.find(toFind.team) != check.end()){
            continue;
        }
        check.insert(toFind.team);
        double sumAge = 0;
        int count_players = 0;
        for (int j = 0; j < int(List.size()); j++){
            Player tmp = List.getItem(j);
            if (tmp.team != toFind.team){
                continue;
            }
            count_players++;
            sumAge += tmp.age;
        }
        if (sumAge / count_players < curValue){
            curValue = sumAge / count_players;
            result = toFind.team;
        }
    }
    ans += QString::fromStdString(result);
    QMessageBox::information(this, "result", ans);
}

