// TriangleQuestion.cpp
// 三角形题目类的定义文件：实现 TriangleQuestion.h 中声明的成员函数
#include "TriangleQuestion.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

const double EPS = 1e-6;   // 判断浮点数相等时用到的误差范围

// 默认构造函数：将对象数据成员初始化为一定的值（3、4、5是合法直角三角形）
TriangleQuestion::TriangleQuestion() {
    id_ = 0;
    side1_ = 3.0;
    side2_ = 4.0;
    side3_ = 5.0;
    userArea_ = 0.0;
    userPerimeter_ = 0.0;
    answered_ = false;
    isCorrect_ = false;
    calcCorrectAnswer();
}

// 重载构造函数：用题目编号和三条边长构造对象
TriangleQuestion::TriangleQuestion(int id, double a, double b, double c) {
    setId(id);
    if (!setSides(a, b, c)) {
        // 边长不合法时给出提示，并重置为一个合法三角形
        cout << "提示：输入的边长不能构成三角形，已重置为 3 4 5" << endl;
        setSides(3.0, 4.0, 5.0);
    }
    userArea_ = 0.0;
    userPerimeter_ = 0.0;
    answered_ = false;
    isCorrect_ = false;
    calcCorrectAnswer();
}

// 设置题目编号
void TriangleQuestion::setId(int id) {
    id_ = id;
}

// 修改三条边长（带合法性验证）
bool TriangleQuestion::setSides(double a, double b, double c) {
    // 边长必须为正，且任意两边之和大于第三边
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return false;
    }
    side1_ = a;
    side2_ = b;
    side3_ = c;
    calcCorrectAnswer();   // 边长修改后同步更新正确答案
    return true;
}

int TriangleQuestion::getId() const { return id_; }
double TriangleQuestion::getSide1() const { return side1_; }
double TriangleQuestion::getSide2() const { return side2_; }
double TriangleQuestion::getSide3() const { return side3_; }
double TriangleQuestion::getUserArea() const { return userArea_; }
double TriangleQuestion::getUserPerimeter() const { return userPerimeter_; }
double TriangleQuestion::getCorrectArea() const { return correctArea_; }
double TriangleQuestion::getCorrectPerimeter() const { return correctPerimeter_; }
bool TriangleQuestion::isAnswered() const { return answered_; }
bool TriangleQuestion::isCorrect() const { return isCorrect_; }

// 计算周长
double TriangleQuestion::calcPerimeter() const {
    return side1_ + side2_ + side3_;
}

// 计算面积：海伦公式  S = sqrt(p(p-a)(p-b)(p-c))，其中 p 为半周长
double TriangleQuestion::calcArea() const {
    double p = (side1_ + side2_ + side3_) / 2.0;
    return sqrt(p * (p - side1_) * (p - side2_) * (p - side3_));
}

// 判断三角形类型：等边 / 等腰 / 直角 / 一般
string TriangleQuestion::getType() const {
    if (!isValid()) {
        return "不能构成三角形";
    }
    double a = side1_, b = side2_, c = side3_;
    // 找出最大边，用于判断直角三角形
    double maxSide = a;
    if (b > maxSide) maxSide = b;
    if (c > maxSide) maxSide = c;

    // 等边三角形：三条边相等
    if (fabs(a - b) < EPS && fabs(b - c) < EPS) {
        return "等边三角形";
    }
    // 直角三角形：最大边的平方 = 另外两边平方之和
    // 即 a*a + b*b + c*c == 2*maxSide*maxSide
    double sum = a * a + b * b + c * c;
    if (fabs(sum - 2 * maxSide * maxSide) < EPS) {
        return "直角三角形";
    }
    // 等腰三角形：有两条边相等
    if (fabs(a - b) < EPS || fabs(b - c) < EPS || fabs(a - c) < EPS) {
        return "等腰三角形";
    }
    return "一般三角形";
}

// 三边能否构成三角形
bool TriangleQuestion::isValid() const {
    if (side1_ <= 0 || side2_ <= 0 || side3_ <= 0) {
        return false;
    }
    if (side1_ + side2_ <= side3_ ||
        side1_ + side3_ <= side2_ ||
        side2_ + side3_ <= side1_) {
        return false;
    }
    return true;
}

// 随机生成一道合法题目：边长取 3~20 的整数，不合法就重新生成
void TriangleQuestion::generateRandomQuestion(int id) {
    setId(id);
    int a, b, c;
    do {
        a = rand() % 18 + 3;   // rand()%18 得到 0~17，加 3 得到 3~20
        b = rand() % 18 + 3;
        c = rand() % 18 + 3;
    } while (a + b <= c || a + c <= b || b + c <= a);
    side1_ = a;
    side2_ = b;
    side3_ = c;
    answered_ = false;
    isCorrect_ = false;
    calcCorrectAnswer();
}

// 计算正确答案（周长和面积）
void TriangleQuestion::calcCorrectAnswer() {
    correctPerimeter_ = calcPerimeter();
    correctArea_ = calcArea();
}

// 输入自己的答案（面积和周长）
void TriangleQuestion::setUserAnswer(double area, double perimeter) {
    userArea_ = area;
    userPerimeter_ = perimeter;
    answered_ = true;
}

// 判断用户答案是否正确（允许 0.01 以内的计算误差）
bool TriangleQuestion::checkAnswer() {
    const double ANSWER_EPS = 0.01;
    if (fabs(userArea_ - correctArea_) <= ANSWER_EPS &&
        fabs(userPerimeter_ - correctPerimeter_) <= ANSWER_EPS) {
        isCorrect_ = true;
    } else {
        isCorrect_ = false;
    }
    return isCorrect_;
}

// 出题时只显示题目信息（不显示答案）
void TriangleQuestion::showQuestion() const {
    cout << "题目" << id_ << "：三角形三边长分别为 "
         << side1_ << "、" << side2_ << "、" << side3_ << endl;
    cout << "（这是一个" << getType() << "）" << endl;
}

// 显示完整信息（含正确答案和用户作答情况）
void TriangleQuestion::show() const {
    cout << "题目编号：" << id_ << endl;
    cout << "三条边长：" << side1_ << "、" << side2_ << "、" << side3_ << endl;
    cout << "图形类型：" << getType() << endl;
    cout << "正确答案：周长 " << correctPerimeter_
         << "，面积 " << correctArea_ << endl;
    if (answered_) {
        cout << "用户答案：周长 " << userPerimeter_
             << "，面积 " << userArea_
             << "（" << (isCorrect_ ? "回答正确" : "回答错误") << "）" << endl;
    } else {
        cout << "用户答案：尚未作答" << endl;
    }
}
