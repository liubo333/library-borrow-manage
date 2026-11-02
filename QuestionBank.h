// QuestionBank.h
// 题库类的定义文件：管理多道几何图形题目
// 用 STL 容器 vector 保存题目对象指针（实验五），用 fstream 保存/读取题目数据（实验六）
// 对应知识点：组合关系（题库 has-a 多道题目）、vector、文件输入输出流
#ifndef QUESTION_BANK_H
#define QUESTION_BANK_H

#include <string>
#include <vector>
#include "ShapeQuestion.h"

class QuestionBank {
private:
    std::string name_;                       // 题库名称
    std::vector<ShapeQuestion*> questions_;  // 题目集合：题目对象指针的 vector（组合关系）
    int totalScore_;                         // 练习总得分
    int totalAnswered_;                      // 已作答的题目数
    int correctCount_;                       // 答对的题目数

public:
    QuestionBank();                          // 默认构造函数
    QuestionBank(std::string name);          // 重载构造函数
    ~QuestionBank();                         // 析构函数：释放所有题目对象

    std::string getName() const;
    int getSize() const;                     // 返回题目数量（vector 的 size）
    int getTotalScore() const;
    double getAverage() const;               // 平均分

    void addQuestion(int type);              // 按图形类型随机生成一道题目（push_back）
    bool deleteQuestion(int id);             // 按编号删除题目（erase）
    ShapeQuestion* findQuestion(int id);     // 按编号查询题目
    ShapeQuestion* getQuestionByIndex(int index);  // 按下标取题目（练习时随机抽题用）
    void showAll();                          // 遍历输出全部题目
    void clearAll();                         // 清空题库（clear）

    void saveToFile(std::string fileName);       // 实验六：把题目保存到文件
    void loadFromFile(std::string fileName);     // 实验六：从文件读取题目恢复题库

    void recordResult(bool isCorrect);   // 记录一次练习成绩（答对得10分）
};

#endif // QUESTION_BANK_H
