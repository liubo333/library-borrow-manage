// main.cpp
// 主函数文件：生成类对象，组织程序功能（对象生成与功能调用放在此文件）
// 实验一：在合适位置生成三角形题目类的对象并调用其功能
// 实验二：生成题库类对象（组合关系）、判卷类对象（依赖关系）并调用功能
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TriangleQuestion.h"
#include "QuestionBank.h"
#include "Grader.h"

using namespace std;

// 显示主菜单
void showMenu() {
    cout << endl;
    cout << "========== 简单几何图形题库系统 ==========" << endl;
    cout << "  1. 增加题目" << endl;
    cout << "  2. 删除题目" << endl;
    cout << "  3. 查看全部题目" << endl;
    cout << "  4. 查询题目" << endl;
    cout << "  5. 开始练习（答题 + 判卷）" << endl;
    cout << "  6. 查看成绩" << endl;
    cout << "  0. 退出系统" << endl;
    cout << "===========================================" << endl;
    cout << "请输入你的选择：";
}

// 增加题目（用户输入题目编号和三条边长）
void addQuestion(QuestionBank& bank) {
    int id;
    double a, b, c;
    cout << "请输入题目编号：";
    cin >> id;
    cout << "请输入三条边长（用空格隔开）：";
    cin >> a >> b >> c;
    TriangleQuestion q(id, a, b, c);   // 实验一：生成三角形题目类的对象
    bank.addQuestion(q);               // 实验二：调用题库类的增加题目功能
}

// 开始练习：随机抽题、输入答案、判卷、记录成绩
void startPractice(QuestionBank& bank, Grader& grader) {
    if (bank.getQuestionCount() == 0) {
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

    int total = bank.getQuestionCount();
    int correctCount = 0;
    for (int i = 1; i <= n; ++i) {
        cout << endl << "——第 " << i << " 题——" << endl;
        // 随机抽一道题
        int index = rand() % total;
        TriangleQuestion* q = bank.getQuestionByIndex(index);
        // 实验一：调用对象的输出功能显示题目（只显示题目，不显示答案）
        q->showQuestion();

        // 输入自己的答案（面积和周长）
        double userArea, userPerimeter;
        cout << "请输入你计算的面积：";
        cin >> userArea;
        cout << "请输入你计算的周长：";
        cin >> userPerimeter;
        q->setUserAnswer(userArea, userPerimeter);

        // 实验二：判卷类对象调用其成员函数判卷（依赖关系）
        bool ok = grader.judge(*q);

        // 记录本次成绩
        bank.recordResult(ok);
        if (ok) {
            correctCount++;
        }
    }
    cout << endl << "本次练习共答对 " << correctCount << " 题。" << endl;
    // 输出本次成绩和平均分
    bank.showScore();
}

int main() {
    // 用系统时间初始化随机数种子，保证每次运行随机题目不同
    srand((unsigned int)time(NULL));

    // 实验二：生成整体类（题库类）的对象，组合了多道三角形题目
    QuestionBank bank("小学几何题库");

    // 初始化题库：加入几道预置题目
    bank.addQuestion(TriangleQuestion(1, 3, 4, 5));   // 直角三角形
    bank.addQuestion(TriangleQuestion(2, 6, 6, 6));   // 等边三角形
    bank.addQuestion(TriangleQuestion(3, 5, 5, 8));   // 等腰三角形
    // 再随机生成两道题目加入题库
    TriangleQuestion q4;
    q4.generateRandomQuestion(4);
    bank.addQuestion(q4);
    TriangleQuestion q5;
    q5.generateRandomQuestion(5);
    bank.addQuestion(q5);

    // 实验二：生成判卷类对象（与三角形题目类构成依赖关系）
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
            bank.deleteQuestion(id);   // 调用题库类的删除题目功能
            break;
        }
        case 3:
            bank.showAllQuestions();   // 调用题库类的输出功能
            break;
        case 4: {
            int id;
            cout << "请输入要查询的题目编号：";
            cin >> id;
            TriangleQuestion* q = bank.findQuestion(id);   // 调用题库类的查询功能
            if (q == NULL) {
                cout << "没有找到编号为 " << id << " 的题目。" << endl;
            } else {
                q->show();
            }
            break;
        }
        case 5:
            startPractice(bank, grader);
            break;
        case 6:
            bank.showScore();
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
