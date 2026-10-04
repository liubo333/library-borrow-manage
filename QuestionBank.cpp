// QuestionBank.cpp
// 题库类的定义文件：实现 QuestionBank.h 中声明的成员函数
#include "QuestionBank.h"
#include <iostream>
using namespace std;

// 默认构造函数
QuestionBank::QuestionBank() {
    name_ = "未命名题库";
    totalScore_ = 0;
    answeredCount_ = 0;
    averageScore_ = 0.0;
}

// 重载构造函数：指定题库名称
QuestionBank::QuestionBank(string name) {
    name_ = name;
    totalScore_ = 0;
    answeredCount_ = 0;
    averageScore_ = 0.0;
}

void QuestionBank::setName(string name) {
    name_ = name;
}

string QuestionBank::getName() const {
    return name_;
}

int QuestionBank::getQuestionCount() const {
    return (int)questions_.size();
}

int QuestionBank::getTotalScore() const {
    return totalScore_;
}

int QuestionBank::getAnsweredCount() const {
    return answeredCount_;
}

double QuestionBank::getAverageScore() const {
    return averageScore_;
}

// 输出所有题目
void QuestionBank::showAllQuestions() const {
    cout << "======= " << name_ << " =======" << endl;
    if (questions_.empty()) {
        cout << "题库中暂时没有题目。" << endl;
        return;
    }
    cout << "题库共有 " << questions_.size() << " 道题：" << endl;
    // 使用 STL 容器 vector 的迭代器遍历所有题目
    vector<TriangleQuestion>::const_iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        it->show();
        cout << "--------------------------" << endl;
    }
}

// 输出成绩和平均分
void QuestionBank::showScore() const {
    cout << "======= 本次成绩 =======" << endl;
    cout << "已练习题目数：" << answeredCount_ << endl;
    cout << "总成绩：" << totalScore_ << " 分（每题 10 分）" << endl;
    if (answeredCount_ > 0) {
        cout << "平均分：" << averageScore_ << " 分" << endl;
    } else {
        cout << "平均分：还没有练习记录" << endl;
    }
}

// 向题库内增加题目
void QuestionBank::addQuestion(const TriangleQuestion& q) {
    questions_.push_back(q);   // 使用 vector 的 push_back 增加题目
    cout << "题目 " << q.getId() << " 已加入题库，当前共 "
         << questions_.size() << " 道题。" << endl;
}

// 在题库内删除题目（按题目编号），成功返回true
bool QuestionBank::deleteQuestion(int id) {
    // 使用 vector 的迭代器查找并删除
    vector<TriangleQuestion>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        if (it->getId() == id) {
            questions_.erase(it);   // 使用 vector 的 erase 删除题目
            cout << "题目 " << id << " 已从题库中删除。" << endl;
            return true;
        }
    }
    cout << "没有找到编号为 " << id << " 的题目。" << endl;
    return false;
}

// 查询题库的题目（按编号查找），找不到返回NULL
TriangleQuestion* QuestionBank::findQuestion(int id) {
    vector<TriangleQuestion>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        if (it->getId() == id) {
            return &(*it);
        }
    }
    return NULL;
}

// 按下标取题目（练习时随机抽题用），下标越界返回NULL
TriangleQuestion* QuestionBank::getQuestionByIndex(int index) {
    if (index < 0 || index >= (int)questions_.size()) {
        return NULL;
    }
    return &(questions_[index]);
}

// 记录一次练习成绩（答对得10分），并更新平均分
void QuestionBank::recordResult(bool isCorrect) {
    if (isCorrect) {
        totalScore_ += 10;
    }
    answeredCount_++;
    averageScore_ = (double)totalScore_ / answeredCount_;
}
