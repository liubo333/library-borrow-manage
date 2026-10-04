// Grader.cpp
// 判卷类的定义文件：实现 Grader.h 中声明的成员函数
#include "Grader.h"
#include <iostream>
using namespace std;

// 判卷函数：判卷类的成员函数参数是三角形题目类的对象引用，
// 在函数中通过题目对象的公有成员函数读取答案、判断对错并修改其状态，
// 这就是类之间的依赖关系（use-a）。
bool Grader::judge(TriangleQuestion& q) {
    // 1. 调用题目对象自身的 checkAnswer()，由对象完成答案比对，
    //    并更新自己的作答状态（isCorrect_ 是否答对）
    bool ok = q.checkAnswer();

    // 2. 通过公有获取函数读取题目对象中的答案信息，输出判卷反馈
    if (ok) {
        cout << "【判卷】回答正确！本题得 10 分。" << endl;
    } else {
        cout << "【判卷】回答错误。正确答案：面积 "
             << q.getCorrectArea() << "，周长 "
             << q.getCorrectPerimeter() << "，本题得 0 分。" << endl;
    }

    // 3. 注意：这里 q 是引用传递。checkAnswer 对题目对象状态的修改
    //    （是否答对）会保留在 main 函数中真正的题目对象上；
    //    如果这里改成值传递，函数内只是对副本的修改，原对象不会变化。
    return ok;
}
