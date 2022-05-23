#include "paintscene.h"

paintScene::paintScene()
{

}
void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    addEllipse(event->scenePos().x() - 5, event->scenePos().y(), 10, 10);
    prev = event->scenePos();
}
void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    addLine(prev.x(), prev.y(), event->scenePos().x(), event->scenePos().y());
    prev = event->scenePos();
}
