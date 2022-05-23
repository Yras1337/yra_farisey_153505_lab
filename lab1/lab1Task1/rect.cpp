#include "rect.h"
cRect::cRect()
{
    QPolygonF poly;
    poly << QPoint(250, 300) << QPoint(250 + 80, 300) << QPoint(250 + 80, 300 + 100) << QPoint(250, 300 + 100);
    setPolygon(poly);
}

void figure::up(){
    moveBy(0, -5);
}
void figure::down(){
    moveBy(0, 5);
}
void figure::left(){
    moveBy(-1, 0);
}
void figure::right(){
    moveBy(1, 0);
}
void figure::setH(int x){
    this->h = x;
}
int figure::getH(){
    return int(this->h);
}
Door::Door(){
    QPolygonF poly;
    poly << QPointF(250 + 40, 300) << QPointF(250 + 40, 300 + 100);
    setPolygon(poly);
}
bool Door::get_state(){
    return this->is_open;
}
void Door::change_state(int x){
    this->is_open = x;
}
void Door::change_pos(int x){
    this->pos = x;
}
int Door::tek_pos(){
    return this->pos;
}
