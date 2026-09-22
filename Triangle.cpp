#include "Triangle.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// 判断三条边是否能够构成三角形
bool Triangle::isValid(double x, double y, double z) const
{
    return x > 0 && y > 0 && z > 0 &&
        x + y > z &&
        x + z > y &&
        y + z > x;
}

// 默认构造函数
Triangle::Triangle() : a(3), b(4), c(5)
{
}

// 带参数构造函数
Triangle::Triangle(double x, double y, double z)
    : a(3), b(4), c(5)
{
    if (!setSides(x, y, z))
    {
        cout << "输入的三条边不能构成三角形，"
            << "已使用默认值3、4、5。" << endl;
    }
}

// 析构函数
Triangle::~Triangle()
{
}

// 修改三条边
bool Triangle::setSides(double x, double y, double z)
{
    if (!isValid(x, y, z))
    {
        return false;
    }

    a = x;
    b = y;
    c = z;

    return true;
}

// 修改第一条边
bool Triangle::setA(double x)
{
    return setSides(x, b, c);
}

// 修改第二条边
bool Triangle::setB(double x)
{
    return setSides(a, x, c);
}

// 修改第三条边
bool Triangle::setC(double x)
{
    return setSides(a, b, x);
}

// 获取第一条边
double Triangle::getA() const
{
    return a;
}

// 获取第二条边
double Triangle::getB() const
{
    return b;
}

// 获取第三条边
double Triangle::getC() const
{
    return c;
}

// 输出三角形信息
void Triangle::show() const
{
    cout << fixed << setprecision(2);

    cout << "三角形三边："
        << a << "  "
        << b << "  "
        << c << endl;
}

// 求周长
double Triangle::perimeter() const
{
    return a + b + c;
}

// 求面积
double Triangle::area() const
{
    // 海伦公式
    double p = perimeter() / 2.0;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// 判断三角形类型
string Triangle::type() const
{
    const double eps = 1e-9;

    // 等边三角形
    if (fabs(a - b) < eps &&
        fabs(b - c) < eps)
    {
        return "等边三角形";
    }

    // 等腰三角形
    if (fabs(a - b) < eps ||
        fabs(a - c) < eps ||
        fabs(b - c) < eps)
    {
        return "等腰三角形";
    }

    // 为了判断直角三角形，先将三边从小到大排序
    double x = a;
    double y = b;
    double z = c;

    if (x > y)
        swap(x, y);

    if (y > z)
        swap(y, z);

    if (x > y)
        swap(x, y);

    // 勾股定理
    if (fabs(x * x + y * y - z * z) < eps)
    {
        return "直角三角形";
    }

    return "普通三角形";
}