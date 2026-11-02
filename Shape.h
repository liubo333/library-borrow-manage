// Shape.h
// 图形类的定义文件：声明图形基类 Shape 和 5 个派生类
// （正方形 Square、长方形 Rectangle、圆形 Circle、三角形 Triangle、梯形 Trapezoid）
// 对应知识点：实验三（继承与派生）、实验四（虚函数多态）
#ifndef SHAPE_H
#define SHAPE_H

#include <string>

// 图形基类：抽象类
// 把计算面积、周长设计成纯虚函数，统一各派生类的接口
class Shape {
private:
    std::string name_;   // 图形名称

public:
    Shape();                       // 默认构造函数
    Shape(std::string name);       // 重载构造函数
    virtual ~Shape();              // 虚析构函数：用基类指针删除派生类对象时能正确释放

    std::string getName() const;   // 获取图形名称

    virtual double area() = 0;            // 纯虚函数：计算面积
    virtual double perimeter() = 0;       // 纯虚函数：计算周长
    virtual void showInfo() = 0;          // 纯虚函数：输出边长等基本信息
    virtual int getType() = 0;            // 纯虚函数：返回图形类型编号
    // （1正方形 2长方形 3圆形 4三角形 5梯形，保存文件时按类型恢复）
};

// 正方形类：公有继承 Shape
class Square : public Shape {
private:
    double side_;   // 边长

public:
    Square();
    Square(double side);
    ~Square();
    double area() override;        // 重写基类的纯虚函数
    double perimeter() override;
    void showInfo() override;
    int getType() override;
    double getSide() const;
};

// 长方形类
class Rectangle : public Shape {
private:
    double length_, width_;   // 长、宽

public:
    Rectangle();
    Rectangle(double length, double width);
    ~Rectangle();
    double area() override;
    double perimeter() override;
    void showInfo() override;
    int getType() override;
    double getLength() const;
    double getWidth() const;
};

// 圆形类
class Circle : public Shape {
private:
    double radius_;   // 半径

public:
    Circle();
    Circle(double radius);
    ~Circle();
    double area() override;
    double perimeter() override;
    void showInfo() override;
    int getType() override;
    double getRadius() const;
};

// 三角形类
class Triangle : public Shape {
private:
    double side1_, side2_, side3_;   // 三条边

public:
    Triangle();
    Triangle(double s1, double s2, double s3);
    ~Triangle();
    double area() override;          // 用海伦公式计算
    double perimeter() override;
    void showInfo() override;
    int getType() override;
    double getSide1() const;
    double getSide2() const;
    double getSide3() const;
};

// 梯形类（按等腰梯形设计：上底、下底、高、腰）
class Trapezoid : public Shape {
private:
    double topBase_, bottomBase_, height_, waist_;   // 上底、下底、高、腰

public:
    Trapezoid();
    Trapezoid(double top, double bottom, double h, double w);
    ~Trapezoid();
    double area() override;          // 面积 = (上底 + 下底) * 高 / 2
    double perimeter() override;     // 周长 = 上底 + 下底 + 2 * 腰
    void showInfo() override;
    int getType() override;
    double getTopBase() const;
    double getBottomBase() const;
    double getHeight() const;
    double getWaist() const;
};

#endif // SHAPE_H
