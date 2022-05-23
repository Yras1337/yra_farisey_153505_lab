#include "figure.h"
#include <iostream>
void mRect::build_rect(int a, int b, int c){
    QPolygonF poly;
    this->cords.push_back({250 - a, 175 - a});
    this->cords.push_back({250 - a, 175 + b});
    this->cords.push_back({250 + b + c, 175 + b});
    this->cords.push_back({250 + b + c, 175 - a});
    poly << QPoint(250 - a, 175 - a) << QPoint(250 - a, 175 + b) << QPoint(250 + b + c, 175 + b) << QPoint(250 + b + c, 175 - a);
    setPolygon(poly);
}
Tre::Tre(){
    QPolygonF poly;
    this->cords.push_back({300, 175});
    this->cords.push_back({300 - 30, 175 - 40});
    this->cords.push_back({300 + 30, 175 - 40});
    poly << QPoint(300, 175) << QPoint(300 - 30, 175 - 40) << QPoint(300 + 30, 175 - 40);
    setPolygon(poly);
}
mRect::mRect(){
    build_rect(100, 50, 70);
}
double PI = 3.1415926535;
double to_radian(double x){
    double result = x * PI / 180.0;
    return result;
}

void mStar::build_mn(double N){
    QPolygonF poly;
    std::cout << N << std::endl;
    int x0 = 300, y0 = 175;
    for (double F = 0; F <= 6.283 * 10; F += 0.01){
        double r = 30.0 / cos(2.0 * PI / N * (0.5 * std::floor(N * F / PI) - std::floor(0.5 * std::floor(N * F / PI))) - F + PI / N * std::floor(N * F / PI));
        //std::cout << F << ' ' << r << ' ' << cos(F) << std::endl;
        double x = x0 + r * cos(F);
        double y = y0 + r * sin(F);
        this->cords.push_back({x, y});
        poly << QPoint(x, y);
    }
    setPolygon(poly);
}
mStar::mStar(double N){
    build_mn(N);
}
mStar2::mStar2(double N){
    build_mn(N);
}
mStar3::mStar3(double N){
    build_mn(N);
}
mn_6::mn_6(double N){
    build_mn(N);
}
/*mStar::mStar(){
    QPolygonF poly;
    std::vector < int > p = {1, 3, 5, 2, 4, 1};
    for (int i = 0; i < int(p.size()); i++){
        int x = 300 + sin(72.0 / 180.0 * PI * p[i]) * 100;
        int y = 175 + cos(72.0 / 180.0 * PI * p[i]) * 100;
        poly << QPoint(x, y);
        this->cords.push_back({x, y});
    }
    setPolygon(poly);
}*/
mRomb::mRomb(){
    build_rect(70, 70, 0);
}
mCircle::mCircle(){
    QPolygon poly;
    float a = 3.1415 * 2 / 100;
    for (int i = -1; i < 100; i++){
        int x = sin(a * i) * 100 + 300;
        int y = cos(a * i) * 100 + 175;
        this->cords.push_back({x, y});
        poly << QPoint(x, y);
    }
    setPolygon(poly);
}
cSqrt::cSqrt(){
    build_rect(50, 50, 0);
}
std::pair < double, double > figure::get_centroid_kords(){
    std::pair < double, double > result;
    for (int i = 0; i < int(cords.size()); i++){
        result.first += cords[i].first;
        result.second += cords[i].second;
    }
    result.first /= int(cords.size());
    result.second /= int(cords.size());
    return result;
}
void figure::add_x(double x){
    for (int i = 0; i < int(cords.size()); i++){
        cords[i].first += x;
    }
}
void figure::add_y(double y){
    for (int i = 0; i < int(cords.size()); i++){
        cords[i].second += y;
    }
}
double figure::get_perim(){
    double result = 0;
    for (int i = 0; i < int(cords.size()) - 1; i++){
        result += sqrt((cords[i].first - cords[i + 1].first) * (cords[i].first - cords[i + 1].first) +
                (cords[i].second - cords[i + 1].second) * (cords[i].second - cords[i + 1].second));
    }
    result += sqrt((cords[0].first - cords[int(cords.size()) - 1].first) * (cords[0].first - cords[int(cords.size()) - 1].first) +
            (cords[0].second - cords[int(cords.size()) - 1].second) * (cords[0].second - cords[int(cords.size()) - 1].second));
    return result * param_mult;
}
double figure::get_sq(){
    double result = 0;
    for (int i = 0; i < int(cords.size()) - 1; i++){
        result += cords[i].first * cords[i + 1].second;
        result -= cords[i].second * cords[i + 1].first;
    }
    result += cords[int(cords.size()) - 1].first * cords[0].second;
    result -= cords[int(cords.size()) - 1].second * cords[0].first;
    return abs(result * 0.5) * param_mult;
}
void figure::set_mult(double factor){
    param_mult = factor;
}
mLine::mLine(QPointF c1, QPointF c2){
    QPolygonF poly;
    poly << c1 << c2;
    setPolygon(poly);
}
mParalel::mParalel(){
    QPolygonF poly;
    cords.push_back({250, 175});
    cords.push_back({300, 225});
    cords.push_back({350, 225});
    cords.push_back({350, 175});
    poly << QPointF(250, 175) << QPointF(300, 225) << QPointF(350, 225) << QPointF(350, 175);
    setPolygon(poly);
}
