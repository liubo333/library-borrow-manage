// ShapeQuestion.h
// 题目类的定义文件：一道几何图形计算题
// 组合一个图形对象（题目 has-a 图形），保存题目编号、正确答案、用户答案和作答状态
// 对应知识点：组合关系（延续实验二）、图形多态调用（实验四）
#ifndef SHAPEQUESTION_H
#define SHAPEQUESTION_H

#include "Shape.h"

class ShapeQuestion {
private:
    int id_;                  // 题目编号
    Shape* shape_;            // 图形对象（组合关系：new 创建，析构函数中 delete 释放）
    double correctArea_;      // 正确答案：面积
    double correctPerimeter_; // 正确答案：周长
    double userArea_;         // 用户输入的答案：面积
    double userPerimeter_;    // 用户输入的答案：周长
    bool isCorrect_;          // 本题是否答对

public:
    ShapeQuestion();                          // 默认构造函数
    ShapeQuestion(int id, Shape* shape);      // 重载构造函数：题目编号 + 图形对象
    ~ShapeQuestion();                         // 析构函数：释放图形对象

    int getId() const;
    Shape* getShape() const;
    double getCorrectArea() const;
    double getCorrectPerimeter() const;
    double getUserArea() const;
    double getUserPerimeter() const;
    bool getIsCorrect() const;

    void setUserAnswer(double area, double perimeter);   // 写入用户输入的答案
    void markResult(bool correct);                       // 直接标记作答结果（文件读取恢复时用）
    bool checkAnswer();                                  // 比对答案是否正确并更新状态
    void showQuestion();                                 // 输出题目信息
    void showUserRecord();                               // 输出用户的作答记录
};

#endif // SHAPEQUESTION_H
