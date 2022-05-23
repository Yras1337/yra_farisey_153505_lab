#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dArray.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <fstream>
#include <iostream>
#include <QString>
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
struct Data{
    std::string group;
    std::string mark;
    std::string date;
    std::string status;
};
bool is_num(char c){
    if (c < '0' || c > '9'){
        return 0;
    }
    return 1;
}
bool is_num(std::string s){
    for (int i = 0; i < int(s.size()); i++){
        if (!is_num(s[i])){
            return 0;
        }
    }
    return 1;
}
vector < Data > Info, comp, uncomp;
void MainWindow::clear_text_widgets()
{
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    ui->textEdit_3->setText("");
    ui->textEdit_4->setText("");
    ui->textEdit_5->setText("");
    ui->textEdit_6->setText("");
    ui->textEdit_7->setText("");
    ui->textEdit_8->setText("");
    ui->comboBox->clear();
    ui->comboBox_2->clear();
}
void MainWindow::on_action_triggered()
{
    global_file_name = QFileDialog::getOpenFileName(this, "Выберите", QDir::currentPath());
    QMessageBox::information(this, "debug", global_file_name);
    if(global_file_name==nullptr) return;
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    std::ifstream file(filePath);
    std::string s;
    QString str;
    //std::cout << "A" << std::endl;
    Info.clear();
    uncomp.clear();
    comp.clear();


    clear_text_widgets();
    //std::cout << "B" << std::endl;
    while(!file.eof()){
        Data tmp;
        file >> s;
        //std::cout << s << std::endl;
        if (s.size() == 0){
            break;
        }
        if (file.eof()){
            QMessageBox::information(this, "info", "invalid file");
            file.close();
            Info.clear();
            return;
        }
        tmp.group = s;
        file >> s;
        if (s.size() == 0 || file.eof()){
            QMessageBox::information(this, "info", "invalid file");
            file.close();
            Info.clear();
            return;
        }
        tmp.mark = s;
        file >> s;
        //std::cout << s << std::endl;
        //std::cout << "A" << std::endl;
        if (s.size() == 0 || file.eof() || s.size() != 10 || s[2] != '.' || s[5] != '.' ||
                !is_num(s[0]) || !is_num(s[1]) || !is_num(s[3]) || !is_num(s[4]) || !is_num(s[6]) || !is_num(s[7]) || !is_num(s[8]) || !is_num(s[9])){
            QMessageBox::information(this, "info", "invalid file, date format XX.XX.XXXX");
            file.close();
            Info.clear();
            return;
        }
        //std::cout << "B" << std::endl;
        tmp.date = s;
        file >> s;
        //std::cout << s << std::endl;
        if (s.size() == 0){
            QMessageBox::information(this, "info", "invalid file");
            file.close();
            Info.clear();
            return;
        }
        if (s != "complete" && s != "uncomplete"){
            QMessageBox::information(this, "info", "invalid file");
            file.close();
            Info.clear();
            return;
        }
        tmp.status = s;
        //std::cout << "A" << std::endl;
        Info.push_back(tmp);
        //std::cout << "B" << std::endl;
    }
    //std::cout << "C" << std::endl;
    int l = 0, r = 0;
    for (int i = 0; i < Info.size(); i++){
        if (Info[i].status == "uncomplete"){
            uncomp.push_back(Info[i]);
            ui->comboBox->addItem("Заказ #" + QString::number(l));
            l++;
        }
        else{
            comp.push_back(Info[i]);
            ui->comboBox_2->addItem("Заказ #" + QString::number(r));
            r++;
        }
    }

    file.close();
}


void MainWindow::on_action_2_triggered()
{
    QByteArray temp = global_file_name.toLocal8Bit();
    const char *filePath = temp.data();
    std::ofstream out(filePath);
    for (int i = 0; i < Info.size(); i++){
        out << Info[i].group << ' ' << Info[i].mark << ' ' << Info[i].date << ' ' << Info[i].status;
    }
    out.close();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (!Info.size() || !uncomp.size()){
        ui->textEdit->setText("");
        ui->textEdit_2->setText("");
        ui->textEdit_3->setText("");
        ui->textEdit_4->setText("");
        //clear_text_widgets();
        return;
    }
    ui->textEdit->setText(QString::fromStdString(uncomp[index].group));
    ui->textEdit_2->setText(QString::fromStdString(uncomp[index].mark));
    ui->textEdit_3->setText(QString::fromStdString(uncomp[index].date));
    ui->textEdit_4->setText(QString::fromStdString(uncomp[index].status));
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (!Info.size() || !comp.size()){
        //clear_text_widgets();
        return;
    }
    ui->textEdit_5->setText(QString::fromStdString(comp[index].group));
    ui->textEdit_6->setText(QString::fromStdString(comp[index].mark));
    ui->textEdit_7->setText(QString::fromStdString(comp[index].date));
    ui->textEdit_8->setText(QString::fromStdString(comp[index].status));
}


void MainWindow::on_pushButton_clicked()
{
    if (!Info.size() || !uncomp.size()){
        return;
    }
    ui->comboBox_2->addItem("Заказ #" + QString::number(ui->comboBox_2->count()));
    uncomp[ui->comboBox->currentIndex()].status = "complete";
  //  std::cout << "A" << std::endl;
    comp.push_back(uncomp[ui->comboBox->currentIndex()]);
    uncomp.erase(ui->comboBox->currentIndex());
    ui->comboBox->removeItem(ui->comboBox->count() - 1);
    on_comboBox_currentIndexChanged(0);
  //  std::cout << "B" << std::endl;
}


void MainWindow::on_pushButton_3_clicked()
{
    Data temp;
    std::string tmp;
    tmp = ui->textEdit->toPlainText().toStdString();
    if (tmp.size() == 0){
        QMessageBox::information(this, "info", "error");
        return;
    }
    temp.group = tmp;
    tmp = ui->textEdit_2->toPlainText().toStdString();
    if (tmp.size() == 0){
        QMessageBox::information(this, "info", "error");
        return;
    }
    temp.mark = tmp;
    tmp = ui->textEdit_3->toPlainText().toStdString();
    if (tmp.size() != 10 || tmp[2] != '.' || tmp[5] != '.' ||
            !is_num(tmp[0]) || !is_num(tmp[1]) || !is_num(tmp[3]) || !is_num(tmp[4]) || !is_num(tmp[6]) || !is_num(tmp[7]) || !is_num(tmp[8]) || !is_num(tmp[9])){
        QMessageBox::information(this, "info", "error");
        return;
    }
    temp.date = tmp;
    tmp = ui->textEdit_4->toPlainText().toStdString();
    if (tmp != "complete" && tmp != "uncomplete"){
        QMessageBox::information(this, "info", "error");
        return;
    }
    temp.status = tmp;
    if (temp.status == "uncomplete"){
        uncomp.push_back(temp);
        ui->comboBox->addItem("Заказ #" + QString::number(ui->comboBox->count()));
        //on_comboBox_currentIndexChanged(0);
    }
    else{
        comp.push_back(temp);
        ui->comboBox_2->addItem("Заказ #" + QString::number(ui->comboBox_2->count()));
        //on_comboBox_2_currentIndexChanged(0);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    std::string toFind = ui->textEdit_9->toPlainText().toStdString();
    QString ans;
    ans += "uncomplited:\n";
    bool isFind = 0;
    for (int i = 0; i < uncomp.size(); i++){
        if (uncomp[i].group == toFind){
            isFind = 1;
            ans += QString::fromStdString("Заказ #");
            ans += QString::number(i);
            ans += '\n';
        }
    }
    if (!isFind){
        ans += "empty\n";
    }
    isFind = 0;
    ans += "complited:\n";
    for (int i = 0; i < comp.size(); i++){
        if (comp[i].group == toFind){
            isFind = 1;
            ans += QString::fromStdString("Заказ #");
            ans += QString::number(i);
            ans += '\n';
        }
    }
    if (!isFind){
        ans += "empty\n";
    }
    QMessageBox::information(this, "result", ans);
}

