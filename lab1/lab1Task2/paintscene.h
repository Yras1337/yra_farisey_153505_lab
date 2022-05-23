#ifndef PAINTSCENE_H
#define PAINTSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class paintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    paintScene();
private:
    QPointF prev;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void slotTimer();
};

#endif // PAINTSCENE_H
