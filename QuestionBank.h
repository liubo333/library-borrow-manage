// QuestionBank.h
// 题库类（实验二：组合关系中的整体类）
// 整体类包含部分类（三角形题目类）的对象，体现 has-a 的组合关系
#ifndef QUESTION_BANK_H
#define QUESTION_BANK_H

#include <string>
#include <vector>
#include "TriangleQuestion.h"

using namespace std;

class QuestionBank {
private:
    // 数据成员
    string name_;                        // 题库名称
    vector<TriangleQuestion> questions_; // 包含的所有题目（组合关系：整体包含部分）
    int    totalScore_;                  // 所做题目的成绩（总分）
    int    answeredCount_;               // 已作答题目数
    double averageScore_;                // 平均分

public:
    // 构造函数
    QuestionBank();                      // 默认构造函数
    QuestionBank(string name);           // 重载构造函数：指定题库名称

    // 基本操作：初始化 / 修改 / 获取
    void   setName(string name);
    string getName() const;
    int    getQuestionCount() const;     // 获取题目数量
    int    getTotalScore() const;
    int    getAnsweredCount() const;
    double getAverageScore() const;

    // 基本操作：输出显示
    void showAllQuestions() const;       // 输出所有题目
    void showScore() const;              // 输出成绩和平均分

    // 其他操作：向题库内增加题目
    void addQuestion(const TriangleQuestion& q);
    // 其他操作：在题库内删除题目，成功返回true
    bool deleteQuestion(int id);
    // 其他操作：查询题库的题目（按编号查找），找不到返回NULL
    TriangleQuestion* findQuestion(int id);
    // 其他操作：按下标取题目（练习时随机抽题用）
    TriangleQuestion* getQuestionByIndex(int index);

    // 其他操作：记录一次练习成绩（答对得10分）
    void recordResult(bool isCorrect);
};

#endif
