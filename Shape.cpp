// Shape.cpp
// 图形类的定义文件：实现 Shape 基类和 5 个派生类的成员函数
#include "Shape.h"

#include <iostream>
#include <cmath>
using namespace std;

// ==================== 基类 Shape ====================
Shape::Shape() : name_("图形") {
}

Shape::Shape(string name) : name_(name) {
}

Shape::~Shape() {
}

string Shape::getName() const {
    return name_;
}

// ==================== 正方形 Square ====================
Square::Square() : Shape("正方形"), side_(0) {
}

Square::Square(double side) : Shape("正方形"), side_(side) {
}

Square::~Square() {
}

double Square::area() {
    return side_ * side_;
}

double Square::perimeter() {
    return 4 * side_;
}

void Square::showInfo() {
    cout << "边长：" << side_;
}

int Square::getType() {
    return 1;
}

double Square::getSide() const {
    return side_;
}

// ==================== 长方形 Rectangle ====================
Rectangle::Rectangle() : Shape("长方形"), length_(0), width_(0) {
}

Rectangle::Rectangle(double length, double width) : Shape("长方形"), length_(length), width_(width) {
}

Rectangle::~Rectangle() {
}

double Rectangle::area() {
    return length_ * width_;
}

double Rectangle::perimeter() {
    return 2 * (length_ + width_);
}

void Rectangle::showInfo() {
    cout << "长：" << length_ << "，宽：" << width_;
}

int Rectangle::getType() {
    return 2;
}

double Rectangle::getLength() const {
    return length_;
}

double Rectangle::getWidth() const {
    return width_;
}

// ==================== 圆形 Circle ====================
Circle::Circle() : Shape("圆形"), radius_(0) {
}

Circle::Circle(double radius) : Shape("圆形"), radius_(radius) {
}

Circle::~Circle() {
}

double Circle::area() {
    return 3.14159 * radius_ * radius_;
}

double Circle::perimeter() {
    return 2 * 3.14159 * radius_;
}

void Circle::showInfo() {
    cout << "半径：" << radius_;
}

int Circle::getType() {
    return 3;
}

double Circle::getRadius() const {
    return radius_;
}

// ==================== 三角形 Triangle ====================
Triangle::Triangle() : Shape("三角形"), side1_(0), side2_(0), side3_(0) {
}

Triangle::Triangle(double s1, double s2, double s3) : Shape("三角形"), side1_(s1), side2_(s2), side3_(s3) {
}

Triangle::~Triangle() {
}

double Triangle::area() {
    // 海伦公式：s = (a + b + c) / 2，面积 = sqrt(s(s-a)(s-b)(s-c))
    double s = (side1_ + side2_ + side3_) / 2;
    return sqrt(s * (s - side1_) * (s - side2_) * (s - side3_));
}

double Triangle::perimeter() {
    return side1_ + side2_ + side3_;
}

void Triangle::showInfo() {
    cout << "三边：" << side1_ << "、" << side2_ << "、" << side3_;
}

int Triangle::getType() {
    return 4;
}

double Triangle::getSide1() const {
    return side1_;
}

double Triangle::getSide2() const {
    return side2_;
}

double Triangle::getSide3() const {
    return side3_;
}

// ==================== 梯形 Trapezoid ====================
Trapezoid::Trapezoid() : Shape("梯形"), topBase_(0), bottomBase_(0), height_(0), waist_(0) {
}

Trapezoid::Trapezoid(double top, double bottom, double h, double w)
    : Shape("梯形"), topBase_(top), bottomBase_(bottom), height_(h), waist_(w) {
}

Trapezoid::~Trapezoid() {
}

double Trapezoid::area() {
    return (topBase_ + bottomBase_) * height_ / 2;
}

double Trapezoid::perimeter() {
    return topBase_ + bottomBase_ + 2 * waist_;
}

void Trapezoid::showInfo() {
    cout << "上底：" << topBase_ << "，下底：" << bottomBase_
         << "，高：" << height_ << "，腰：" << waist_;
}

int Trapezoid::getType() {
    return 5;
}

double Trapezoid::getTopBase() const {
    return topBase_;
}

double Trapezoid::getBottomBase() const {
    return bottomBase_;
}

double Trapezoid::getHeight() const {
    return height_;
}

double Trapezoid::getWaist() const {
    return waist_;
}
