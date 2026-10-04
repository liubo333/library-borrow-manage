// TriangleQuestion.h
// 三角形题目类（实验一：类与对象 + 实验二：组合/依赖关系中的部分类）
// 类的声明文件：只声明数据成员和成员函数，不写函数体
#ifndef TRIANGLE_QUESTION_H
#define TRIANGLE_QUESTION_H

#include <string>
using namespace std;

class TriangleQuestion {
private:
    // 数据成员（访问控制：private，只能通过公有成员函数访问）
    int    id_;                 // 题目编号
    double side1_, side2_, side3_;  // 三条边长
    double userArea_;           // 用户输入的答案（面积）
    double userPerimeter_;      // 用户输入的答案（周长）
    double correctArea_;        // 正确答案（面积）
    double correctPerimeter_;   // 正确答案（周长）
    bool   answered_;           // 是否已经作答
    bool   isCorrect_;          // 本题是否答对

public:
    // 构造函数：默认构造函数（对象数据成员初始化为一定的值）
    TriangleQuestion();
    // 构造函数：重载构造函数（用参数构造对象）
    TriangleQuestion(int id, double a, double b, double c);

    // 基本操作：初始化 / 修改
    void setId(int id);
    // 修改三条边长，并验证三边能否构成三角形，成功返回true
    bool setSides(double a, double b, double c);

    // 基本操作：获取
    int    getId() const;
    double getSide1() const;
    double getSide2() const;
    double getSide3() const;
    double getUserArea() const;
    double getUserPerimeter() const;
    double getCorrectArea() const;
    double getCorrectPerimeter() const;
    bool   isAnswered() const;
    bool   isCorrect() const;

    // 基本操作：输出
    void showQuestion() const;   // 出题时只显示题目信息（不显示答案）
    void show() const;           // 显示完整信息（含正确答案）

    // 其他操作：计算周长、面积、判断三角形类型、合法性验证
    double calcPerimeter() const;
    double calcArea() const;     // 用海伦公式计算面积
    string getType() const;      // 判断三角形类型
    bool   isValid() const;      // 三边能否构成三角形

    // 其他操作：随机生成一道合法题目（边长3~20）
    void generateRandomQuestion(int id);

    // 其他操作：计算正确答案
    void calcCorrectAnswer();

    // 其他操作：输入自己的答案，判断对错
    void setUserAnswer(double area, double perimeter);
    bool checkAnswer();
};

#endif
