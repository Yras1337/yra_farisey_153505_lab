#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QTableWidget>
#include "data.h"
#include <iostream>
using namespace std;
extern Data *Info;
extern int count_data;
SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(count_data);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "воскресенье" << "понедельник" << "вторник" << "среда" << "четверг" << "пятница" << "суббота");
    int week_pos[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < count_data; i++){
        int j = Info[i].get_day_of_week();
        QTableWidgetItem *itm = new QTableWidgetItem("рейс №" + QString::number(i) + "-" + QString::fromStdString(Info[i].get_rTime()));
        ui->tableWidget->setItem(week_pos[j], j, itm);
        week_pos[j]++;
    }
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
