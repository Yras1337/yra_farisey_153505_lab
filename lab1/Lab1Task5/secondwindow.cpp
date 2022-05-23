#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <string>
#include "date.h"
#include <mainwindow.h>
#include <QMessageBox>
extern string globDate;
SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
bool cisNum(char x){
    if (x < '0' || x > '9'){
        return 0;
    }
    return 1;
}
void SecondWindow::on_pushButton_clicked()
{

    if (ui->textDate == 0){
        QMessageBox::information(this, "error", "invalid date input date in XX.XX.XXXX format");
        return;
    }
    std::string str = ui->textDate->toPlainText().toStdString();
    if (str[2] != '.' || str[5] != '.' || str.size() != 10){
        QMessageBox::information(this, "error", "invalid date input date in XX.XX.XXXX format");
        return;
    }
    if (!cisNum(str[0]) || !cisNum(str[1]) || !cisNum(str[3]) || !cisNum(str[4]) || !cisNum(str[6]) || !cisNum(str[7]) || !cisNum(str[8]) || !cisNum(str[9])){
        QMessageBox::information(this, "error", "invalid date input date in XX.XX.XXXX format");
        return;
    }
    Date Day = str;
    if (!Day.valid_check()){
        QMessageBox::information(this, "error", "input valid date");
        return;
    }
    Date Day0 = globDate;
    int kol = Day0.Duration(Day);
    string s = std::to_string(kol);
    QString out = QString::fromStdString(s);
    QMessageBox::information(this, "info", out);
    hide();
}

