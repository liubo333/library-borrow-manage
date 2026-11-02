// Grader.h
// 判卷类（实验二：依赖关系，延续到实验三~六）
// 判卷类的成员函数 judge 的参数是题目类的对象引用，
// 即判卷类在成员函数中使用了题目类，两者是依赖关系（use-a）。
#ifndef GRADER_H
#define GRADER_H

#include "ShapeQuestion.h"

class Grader {
public:
    // 判卷：判断题目对象中的用户答案是否正确（参数为对象引用）
    // 使用引用传递是因为需要读取题目对象的正确答案并输出判卷结果，
    // 同时也体现了依赖关系（函数的参数中出现了另一个类的对象引用）。
    bool judge(ShapeQuestion& q);
};

#endif // GRADER_H
