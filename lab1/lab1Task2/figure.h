#ifndef FIGURE_H
#define FIGURE_H
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
#include <vector>
class figure : public QGraphicsPolygonItem{
public:
    void scale_fig(double x);
    void change_angle(double x);
    std::pair < double, double > get_centroid_kords();
    void add_x(double x);
    void add_y(double y);
    double get_perim();
    double get_sq();
    void set_mult(double factor);
private:

protected:
    double param_mult = 1;
    std::vector < std::pair < double, double > > cords;
};
class Tre : public figure {
public:
    Tre();
private:
};
class mCircle : public figure{
public:
    mCircle();
private:
    double rad = 30;
};
class mRect : public figure{
public:
    mRect();
protected:
    void build_rect(int a, int b, int c);
};
class cSqrt : public mRect{
public:
    cSqrt();
};
class mRomb : public cSqrt{
public:
    mRomb();
};
class mStar : public figure{
public:
    mStar(double N = 2.5);
protected:
    void build_mn(double N);
};
class mStar2 : public mStar{
public:
    mStar2(double N = 3.5);
};
class mStar3 : public mStar{
public:
    mStar3(double N = 4.5);
};
class mn_6 : public mStar{
public:
    mn_6(double N = 6.0);
};
class mLine : public figure{
public:
    mLine(QPointF c1, QPointF c2);
};
class mParalel : public mStar{
public:
    mParalel();
};

#endif // FIGURE_H
