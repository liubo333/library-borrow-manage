// main.cpp
// 主函数文件：生成类对象，组织程序功能（对象生成与功能调用放在此文件）
// 实验三：生成 Shape 基类对象和 5 个派生类对象（继承、派生）
// 实验四：通过基类指针调用虚函数（多态），题库用题目对象指针的 vector 组织
// 实验五：vector 的 push_back / erase / begin / end / size / clear
// 实验六：fstream 把题库保存到文件、从文件读取恢复
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "QuestionBank.h"
#include "Grader.h"

using namespace std;

// 显示主菜单
void showMenu() {
    cout << endl;
    cout << "========== 简单几何图形题库系统 ==========" << endl;
    cout << "  1. 增加题目（选择图形类型）" << endl;
    cout << "  2. 删除题目" << endl;
    cout << "  3. 查看全部题目" << endl;
    cout << "  4. 查询题目" << endl;
    cout << "  5. 开始练习（答题 + 判卷）" << endl;
    cout << "  6. 查看成绩" << endl;
    cout << "  7. 保存题库到文件" << endl;
    cout << "  8. 从文件读取题库" << endl;
    cout << "  0. 退出系统" << endl;
    cout << "===========================================" << endl;
    cout << "请输入你的选择：";
}

// 增加题目：用户选择图形类型，程序随机生成参数并自动计算正确答案
void addQuestion(QuestionBank& bank) {
    int type;
    cout << "请选择图形类型（1正方形 2长方形 3圆形 4三角形 5梯形）：";
    cin >> type;
    bank.addQuestion(type);   // 实验三/四：内部 new 出对应派生类对象并加入 vector
}

// 开始练习：随机抽题、输入答案、判卷、记录成绩（核心函数）
void startPractice(QuestionBank& bank, Grader& grader) {
    if (bank.getSize() == 0) {
        cout << "题库中还没有题目，请先增加题目。" << endl;
        return;
    }
    int n;
    cout << "请输入本次练习的题目数：";
    cin >> n;
    if (n <= 0) {
        cout << "练习的题目数必须大于 0。" << endl;
        return;
    }

    int total = bank.getSize();
    int correctCount = 0;
    for (int i = 1; i <= n; ++i) {
        cout << endl << "——第 " << i << " 题——" << endl;
        // 随机抽一道题
        int index = rand() % total;
        ShapeQuestion* q = bank.getQuestionByIndex(index);
        // 输出题目（只显示图形类型和基本信息，不显示答案）
        q->showQuestion();

        // 输入自己的答案（面积和周长）
        double userArea, userPerimeter;
        cout << "请输入你计算的面积：";
        cin >> userArea;
        cout << "请输入你计算的周长：";
        cin >> userPerimeter;
        q->setUserAnswer(userArea, userPerimeter);

        // 判卷类对象调用其成员函数判卷（依赖关系）
        bool ok = grader.judge(*q);

        // 记录本次成绩（答对得 10 分）
        bank.recordResult(ok);
        if (ok) {
            correctCount++;
        }
    }
    cout << endl << "本次练习共答对 " << correctCount << " 题。" << endl;
    cout << "当前总分：" << bank.getTotalScore() << " 分，平均分："
         << bank.getAverage() << " 分。" << endl;
}

int main() {
    // 用系统时间初始化随机数种子，保证每次运行随机题目不同
    srand((unsigned int)time(NULL));

    // 生成整体类（题库类）的对象，组合了多道图形题目
    QuestionBank bank("小学几何题库");

    // 初始化题库：预置几道不同图形类型的题目（随机参数）
    bank.addQuestion(1);   // 正方形
    bank.addQuestion(2);   // 长方形
    bank.addQuestion(3);   // 圆形
    bank.addQuestion(4);   // 三角形
    bank.addQuestion(5);   // 梯形

    // 生成判卷类对象（与题目类构成依赖关系）
    Grader grader;

    int choice = -1;
    while (choice != 0) {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            addQuestion(bank);
            break;
        case 2: {
            int id;
            cout << "请输入要删除的题目编号：";
            cin >> id;
            bank.deleteQuestion(id);   // 调用题库类的删除题目功能（erase）
            break;
        }
        case 3:
            bank.showAll();            // 遍历输出全部题目（begin/end）
            break;
        case 4: {
            int id;
            cout << "请输入要查询的题目编号：";
            cin >> id;
            ShapeQuestion* q = bank.findQuestion(id);   // 调用题库类的查询功能
            if (q == NULL) {
                cout << "没有找到编号为 " << id << " 的题目。" << endl;
            } else {
                q->showQuestion();
                cout << "    正确答案：面积 " << q->getCorrectArea()
                     << "，周长 " << q->getCorrectPerimeter() << endl;
            }
            break;
        }
        case 5:
            startPractice(bank, grader);
            break;
        case 6:
            cout << "当前总分：" << bank.getTotalScore() << " 分（每题 10 分）"
                 << endl;
            cout << "平均分：" << bank.getAverage() << " 分。" << endl;
            break;
        case 7:
            bank.saveToFile("questions.txt");   // 实验六：保存题库到文件
            break;
        case 8:
            bank.loadFromFile("questions.txt"); // 实验六：从文件读取题库
            break;
        case 0:
            cout << "感谢使用，再见！" << endl;
            break;
        default:
            cout << "输入无效，请重新选择。" << endl;
            break;
        }
    }
    return 0;
}
