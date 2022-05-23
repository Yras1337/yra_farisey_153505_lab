#ifndef RECT_H
#define RECT_H
#include <QMainWindow>
#include <QWidget>
#include <windows.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QGraphicsPolygonItem>
class figure : public QGraphicsPolygonItem
{
public:
    void up();
    void down();
    void left();
    void right();
    void setH(int x);
    int getH();
private:
    int h;
};
class cRect : public figure
{
public:
    cRect();
};
class Door : public figure
{
public:
    bool get_state();
    int tek_pos();
    void change_state(int x);
    void change_pos(int x);
    Door();
private:
    bool is_open = 0;
    int pos = 40;
};

#endif // RECT_H
