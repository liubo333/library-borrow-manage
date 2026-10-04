// Grader.h
// 判卷类（实验二：依赖关系）
// 判卷类的成员函数 judge 的参数是三角形题目类的对象引用，
// 即判卷类在成员函数中使用了三角形题目类，两者是依赖关系（use-a）。
#ifndef GRADER_H
#define GRADER_H

#include "TriangleQuestion.h"

class Grader {
public:
    // 判卷：判断题目对象中的用户答案是否正确（参数为对象引用）
    // 使用引用传递是因为需要修改传入的题目对象的状态，
    // 如果使用值传递，修改不会影响到原来的对象。
    bool judge(TriangleQuestion& q);
};

#endif
