#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void draw_figure(int type);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_9_clicked();

    void update_info();

    void rotate_f();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();
    void on_horizontalSlider_actionTriggered(int action);

    void on_horizontalSlider_sliderPressed();

    void on_pushButton_12_clicked();

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QPointF prev;

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QTimer* aTimer;
    QTimer* updTimer;
    QTimer* rotateTimer;
    QTimer* paintTimer;
};
#endif // MAINWINDOW_H
