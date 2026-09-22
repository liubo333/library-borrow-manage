#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>

class Triangle
{
private:
    double a;
    double b;
    double c;

    // 判断三条边是否合法
    bool isValid(double x, double y, double z) const;

public:
    // 默认构造函数
    Triangle();

    // 带参数构造函数
    Triangle(double x, double y, double z);

    // 析构函数
    ~Triangle();

    // 修改三条边
    bool setSides(double x, double y, double z);

    // 分别修改某一条边
    bool setA(double x);
    bool setB(double x);
    bool setC(double x);

    // 获取三条边
    double getA() const;
    double getB() const;
    double getC() const;

    // 输出三角形信息
    void show() const;

    // 求周长
    double perimeter() const;

    // 求面积
    double area() const;

    // 判断三角形类型
    std::string type() const;
};

#endif