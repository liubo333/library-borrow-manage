#include <iostream>
#include "Triangle.h"

using namespace std;

int main()
{
    cout << "==============================" << endl;
    cout << "       三角形题目类实验       " << endl;
    cout << "==============================" << endl;

    // 创建对象1：使用默认构造函数
    Triangle t1;

    cout << "\n【对象1：默认构造】" << endl;

    t1.show();

    cout << "周长：" << t1.perimeter() << endl;
    cout << "面积：" << t1.area() << endl;
    cout << "类型：" << t1.type() << endl;


    // 创建对象2：使用带参数构造函数
    Triangle t2(3, 4, 5);

    cout << "\n【对象2：带参数构造】" << endl;

    t2.show();

    cout << "周长：" << t2.perimeter() << endl;
    cout << "面积：" << t2.area() << endl;
    cout << "类型：" << t2.type() << endl;


    // 获取数据成员
    cout << "\n【获取三边数据】" << endl;

    cout << "a = " << t2.getA() << endl;
    cout << "b = " << t2.getB() << endl;
    cout << "c = " << t2.getC() << endl;


    // 修改三边
    cout << "\n【修改三边】" << endl;

    if (t2.setSides(5, 5, 6))
    {
        cout << "修改成功！" << endl;

        t2.show();

        cout << "周长：" << t2.perimeter() << endl;
        cout << "面积：" << t2.area() << endl;
        cout << "类型：" << t2.type() << endl;
    }
    else
    {
        cout << "修改失败！" << endl;
    }


    // 测试非法数据
    cout << "\n【测试非法数据】" << endl;

    if (!t2.setSides(1, 2, 10))
    {
        cout << "1、2、10 不能构成三角形！" << endl;
        cout << "修改失败，原来的数据没有改变。" << endl;
    }


    cout << "\n==============================" << endl;
    cout << "          实验结束            " << endl;
    cout << "==============================" << endl;

    return 0;
}