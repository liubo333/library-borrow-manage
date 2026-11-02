// ShapeQuestion.cpp
// 题目类的定义文件：实现 ShapeQuestion 类的成员函数
#include "ShapeQuestion.h"

#include <iostream>
#include <cmath>
using namespace std;

// 默认构造函数
ShapeQuestion::ShapeQuestion()
    : id_(0), shape_(nullptr), correctArea_(0), correctPerimeter_(0),
      userArea_(0), userPerimeter_(0), isCorrect_(false) {
}

// 重载构造函数：根据图形对象自动计算并保存正确答案
ShapeQuestion::ShapeQuestion(int id, Shape* shape)
    : id_(id), shape_(shape),
      correctArea_(shape->area()),       // 多态调用：自动执行对应子类的面积计算
      correctPerimeter_(shape->perimeter()),
      userArea_(0), userPerimeter_(0), isCorrect_(false) {
}

// 析构函数：释放组合的图形对象
ShapeQuestion::~ShapeQuestion() {
    delete shape_;
}

int ShapeQuestion::getId() const {
    return id_;
}

Shape* ShapeQuestion::getShape() const {
    return shape_;
}

double ShapeQuestion::getCorrectArea() const {
    return correctArea_;
}

double ShapeQuestion::getCorrectPerimeter() const {
    return correctPerimeter_;
}

double ShapeQuestion::getUserArea() const {
    return userArea_;
}

double ShapeQuestion::getUserPerimeter() const {
    return userPerimeter_;
}

bool ShapeQuestion::getIsCorrect() const {
    return isCorrect_;
}

// 写入用户输入的答案
void ShapeQuestion::setUserAnswer(double area, double perimeter) {
    userArea_ = area;
    userPerimeter_ = perimeter;
}

// 直接标记作答结果（从文件读取题目时，按保存时的状态恢复）
void ShapeQuestion::markResult(bool correct) {
    isCorrect_ = correct;
}

// 比对答案：面积和周长都在误差 0.01 以内就算答对
bool ShapeQuestion::checkAnswer() {
    if (fabs(userArea_ - correctArea_) < 0.01 &&
        fabs(userPerimeter_ - correctPerimeter_) < 0.01) {
        isCorrect_ = true;
    } else {
        isCorrect_ = false;
    }
    return isCorrect_;
}

// 输出题目：图形类型 + 基本信息
void ShapeQuestion::showQuestion() {
    cout << "第 " << id_ << " 题（" << shape_->getName() << "）：";
    shape_->showInfo();
    cout << endl;
}

// 输出用户作答记录
void ShapeQuestion::showUserRecord() {
    shape_->showInfo();
    cout << " | 正确答案：面积 " << correctArea_ << "，周长 " << correctPerimeter_;
    cout << " | 我的答案：面积 " << userArea_ << "，周长 " << userPerimeter_;
    cout << " | " << (isCorrect_ ? "答对" : "答错") << endl;
}
