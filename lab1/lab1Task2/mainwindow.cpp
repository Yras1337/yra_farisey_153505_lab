#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figure.h"
#include <QGraphicsPolygonItem>
#include <iostream>
#include <QMessageBox>
#include <QList>
#include <string>
using namespace std;
Tre *obj1 = new Tre;
mLine *newLine;
figure *lastObj;
QGraphicsItem *lastItem;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,600,350,this);
    ui->graphicsView->setScene(scene);
    updTimer = new QTimer(this);
    connect(updTimer, SIGNAL(timeout()), this, SLOT(update_info()));
    updTimer->start(100);
}
bool num_check(char c){
    if ((c < '0' || c > '9') && (c != '-')){
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
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    prev = QPointF(event->position().x() - 5, event->position().y() - 5);
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    mLine *ob = new mLine(prev, QPointF(event->scenePosition().x(), event->scenePosition().y()));
    QGraphicsItem *newL = ob;
    if (prev.x() != 0 && prev.y() != 0)
    scene->addItem(newL);
    prev = QPointF(event->scenePosition().x(), event->scenePosition().y());
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_info(){
    if (lastItem == 0){
        return;
    }
    pair < double, double > centroid_kords = lastObj->get_centroid_kords();
    string temp = "Центр масс x = " + to_string(centroid_kords.first) + "\ny = " + to_string(centroid_kords.second);
    ui->label_6->setText(QString::fromStdString(temp));
    temp = "Периметр = " + to_string(lastObj->get_perim());
    ui->label_8->setText(QString::fromStdString(temp));
    temp = "Площадь = " + to_string(lastObj->get_sq());
    ui->label_7->setText(QString::fromStdString(temp));
}
void MainWindow::on_pushButton_clicked()
{
    draw_figure(1);
}

void MainWindow::on_pushButton_8_clicked()
{
    if (lastItem == 0){
        return;
    }
    string tmp = ui->textEdit->toPlainText().toStdString();
    if (!num_check(tmp)){
        QMessageBox::information(this, "error", "error, invalid value");
        return;
    }
    tmp = ui->textEdit_2->toPlainText().toStdString();
    if (!num_check(tmp)){
        QMessageBox::information(this, "error", "error, invalid value");
        return;
    }
    int x = ui->textEdit->toPlainText().toInt();
    int y = ui->textEdit_2->toPlainText().toInt();
    lastObj->add_x(x);
    lastObj->add_y(y);
    lastItem->moveBy(x, y);
}
void MainWindow::draw_figure(int type){
    prev = QPointF(0, 0);
    switch (type){
        case 1:
           lastObj = new Tre;
           lastItem = lastObj;
           break;
        case 2:
           lastObj = new mCircle;
           lastItem = lastObj;
           break;
        case 3:
            lastObj = new mRomb;
            lastItem = lastObj;
            lastItem->setRotation(lastItem->rotation() + 45);
            break;
        case 4:
           lastObj = new cSqrt;
           lastItem = lastObj;
           break;
        case 5:
           lastObj = new mRect;
           lastItem = lastObj;
            break;
        case 6:
            lastObj = new mStar;
            lastItem = lastObj;
            break;
        case 7:
            lastObj = new mn_6;
            lastItem = lastObj;
            break;
        case 8:
            lastObj = new mStar2;
            lastItem = lastObj;
            break;
        case 9:
            lastObj = new mStar3;
            lastItem = lastObj;
            break;
        case 10:
            lastObj = new mParalel;
            lastItem = lastObj;
            break;
        default:
            return;
    }
    pair < double, double > centroid_kords = lastObj->get_centroid_kords();
    lastItem->setTransformOriginPoint(centroid_kords.first, centroid_kords.second);
    scene->addItem(lastItem);
}
void MainWindow::on_pushButton_4_clicked()
{
    draw_figure(4);
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if (lastItem == 0){
        return;
    }
    lastObj->set_mult(position / 10.0);
    lastItem->setScale(position / 10.0);
}

double angle;
void MainWindow::on_pushButton_9_clicked()
{
    if (lastItem == 0){
        return;
    }
    string tmp = ui->textEdit_3->toPlainText().toStdString();
    if (!num_check(tmp)){
        QMessageBox::information(this, "error", "error, invalid value");
        return;
    }
    rotateTimer = new QTimer(this);
    connect(rotateTimer, SIGNAL(timeout()), this, SLOT(rotate_f()));
    angle = (ui->textEdit_3->toPlainText().toInt() + lastItem->rotation());
    rotateTimer->start(10);
}
void MainWindow::rotate_f(){

    if (lastItem->rotation() != angle){
        lastItem->setRotation(lastItem->rotation() + 1);
    }
    else{
        rotateTimer->stop();
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    draw_figure(2);
}


void MainWindow::on_pushButton_3_clicked()
{
    draw_figure(3);
}


void MainWindow::on_pushButton_5_clicked()
{
    draw_figure(5);
}


void MainWindow::on_pushButton_6_clicked()
{
    draw_figure(6);
}


void MainWindow::on_pushButton_10_clicked()
{
    draw_figure(8);
}


void MainWindow::on_pushButton_11_clicked()
{
    draw_figure(9);
}


void MainWindow::on_pushButton_7_clicked()
{
    draw_figure(7);
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    if (lastItem == 0){
        return;
    }
    lastObj->set_mult(ui->horizontalSlider->value() / 10.0);
    lastItem->setScale(ui->horizontalSlider->value() / 10.0);
}


void MainWindow::on_pushButton_12_clicked()
{
    draw_figure(10);
}

