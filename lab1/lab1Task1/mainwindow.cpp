#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rect.h"
#include <QGraphicsPolygonItem>
#include <iostream>
using namespace std;
int tek = 1;
bool isEnd = 0;
cRect *obj = new cRect;
Door *d1 = new Door;
Door *d2 = new Door;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,600,400,this);
    ui->graphicsView->setScene(scene);
    scene->addLine(230,400,350,400,QPen(QBrush(Qt::black),3));
    scene->addLine(230,300,350,300,QPen(QBrush(Qt::black),3));
    scene->addLine(230,200,350,200,QPen(QBrush(Qt::black),3));
    scene->addLine(230,100,350,100,QPen(QBrush(Qt::black),3));
    scene->addLine(230,0,350,0,QPen(QBrush(Qt::black),3));
    scene->addItem(obj);
    scene->addItem(d1);
    scene->addItem(d2);
    //aTimer = new QTimer(this);
    //connect(aTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
    //aTimer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::to_h(){
    int kord = -(obj->getH() - 1) * 100;
    if (obj->y() == kord){
        isEnd = 0;
        aTimer->stop();
        return;
    }
    if (obj->y() > kord){
        obj->up();
        d1->up();
        d2->up();
    }
    if (obj->y() < kord){
        obj->down();
        d1->down();
        d2->down();
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    if (isEnd){
        return;
    }
    isEnd = 1;
    obj->setH(2);
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(to_h()));
    aTimer->start(50);
}


void MainWindow::on_pushButton_clicked()
{
    if (isEnd){
        return;
    }
    isEnd = 1;
    obj->setH(1);
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(to_h()));
    aTimer->start(50);
}


void MainWindow::on_pushButton_3_clicked()
{
    if (isEnd){
        return;
    }
    isEnd = 1;
    obj->setH(3);
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(to_h()));
    aTimer->start(50);
}


void MainWindow::on_pushButton_4_clicked()
{
    if (isEnd){
        return;
    }
    isEnd = 1;
    obj->setH(4);
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(to_h()));
    aTimer->start(50);
}
/*void MainWindow::on_pushButton_5_clicked()
{
    obj->setH(5);
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(to_h()));
    aTimer->start(50);
}*/
void MainWindow::open_doors(){
    if (d1->tek_pos() == 0){
        d1->change_state(1);
        d2->change_state(1);
        bTimer->stop();
        isEnd = 0;
        return;
    }
    open_left();
    open_right();
}
void MainWindow::open_left(){
    d1->change_pos(d1->tek_pos() - 1);
    d1->left();
}
void MainWindow::open_right(){
    d2->change_pos(d2->tek_pos() + 1);
    d2->right();
}
void MainWindow::close_left(){
    d1->change_pos(d1->tek_pos() + 1);
    d1->right();
}
void MainWindow::close_right(){
    d2->change_pos(d2->tek_pos() - 1);
    d2->left();
}
void MainWindow::close_doors(){
    if (d1->tek_pos() == 40){
        d1->change_state(0);
        d2->change_state(0);
        isEnd = 0;
        bTimer->stop();
        return;
    }
    close_left();
    close_right();
}
void MainWindow::on_pushButton_5_clicked()
{
    if(isEnd){
        return;
    }
    if (d1->get_state() == 0){
        isEnd = 1;
        bTimer = new QTimer(this);
        connect(bTimer, SIGNAL(timeout()), this, SLOT(open_doors()));
        bTimer->start(50);
    }
    else{
        isEnd = 1;
        bTimer = new QTimer(this);
        connect(bTimer, SIGNAL(timeout()), this, SLOT(close_doors()));
        bTimer->start(50);
    }
}

