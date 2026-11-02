// QuestionBank.cpp
// 题库类的定义文件：实现 QuestionBank.h 中声明的成员函数
// 实验五：使用 vector 的 push_back / erase / begin / end / size / clear 组织管理题目
// 实验六：使用 fstream 把题目数据保存到文件、从文件读取恢复
#include "QuestionBank.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;

// 生成 [min, max] 区间内的随机整数
static int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 默认构造函数
QuestionBank::QuestionBank()
    : name_("几何图形题库"), totalScore_(0), totalAnswered_(0), correctCount_(0) {
}

// 重载构造函数：指定题库名称
QuestionBank::QuestionBank(string name)
    : name_(name), totalScore_(0), totalAnswered_(0), correctCount_(0) {
}

// 析构函数：释放 vector 中所有题目对象
QuestionBank::~QuestionBank() {
    clearAll();
}

string QuestionBank::getName() const {
    return name_;
}

int QuestionBank::getSize() const {
    return (int)questions_.size();   // vector 的 size()：返回题目数量
}

int QuestionBank::getTotalScore() const {
    return totalScore_;
}

double QuestionBank::getAverage() const {
    if (totalAnswered_ == 0) {
        return 0;
    }
    return (double)totalScore_ / totalAnswered_;
}

// 按图形类型随机生成一道题目并加入题库
void QuestionBank::addQuestion(int type) {
    Shape* shape = NULL;
    int id = (int)questions_.size() + 1;   // 新题目的编号 = 当前题目数 + 1

    switch (type) {
    case 1: {   // 正方形：随机边长 3~15
        double side = randomInt(3, 15);
        shape = new Square(side);
        break;
    }
    case 2: {   // 长方形：随机长和宽 3~15
        double length = randomInt(3, 15);
        double width = randomInt(3, 15);
        shape = new Rectangle(length, width);
        break;
    }
    case 3: {   // 圆形：随机半径 2~10
        double radius = randomInt(2, 10);
        shape = new Circle(radius);
        break;
    }
    case 4: {   // 三角形：第三边保证两边之差 < c < 两边之和，能构成三角形
        double a = randomInt(3, 15);
        double b = randomInt(3, 15);
        int minC = (int)fabs(a - b) + 1;
        int maxC = (int)(a + b) - 1;
        double c = randomInt(minC, maxC);
        shape = new Triangle(a, b, c);
        break;
    }
    case 5: {   // 梯形（等腰梯形）：随机上底、下底、高，腰按几何关系计算
        double top = randomInt(3, 10);
        double bottom = randomInt(top + 2, 15);
        double h = randomInt(3, 10);
        double waist = sqrt(pow((bottom - top) / 2.0, 2) + h * h);
        shape = new Trapezoid(top, bottom, h, waist);
        break;
    }
    default:
        cout << "图形类型无效，请输入 1~5。" << endl;
        return;
    }

    ShapeQuestion* q = new ShapeQuestion(id, shape);
    questions_.push_back(q);   // 实验五：使用 vector 的 push_back 增加题目
    cout << "题目 " << id << " 已加入题库（" << shape->getName() << "），当前共 "
         << questions_.size() << " 道题。" << endl;
}

// 按编号删除题目，成功返回 true
bool QuestionBank::deleteQuestion(int id) {
    // 实验五：使用 vector 的迭代器遍历查找，找到后用 erase 删除
    vector<ShapeQuestion*>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;              // 先释放题目对象（析构函数会释放图形对象）
            questions_.erase(it);    // 再从 vector 中删除
            cout << "题目 " << id << " 已从题库中删除，当前共 "
                 << questions_.size() << " 道题。" << endl;
            return true;
        }
    }
    cout << "没有找到编号为 " << id << " 的题目。" << endl;
    return false;
}

// 按编号查询题目，找不到返回 NULL
ShapeQuestion* QuestionBank::findQuestion(int id) {
    vector<ShapeQuestion*>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
    return NULL;
}

// 按下标取题目（练习时随机抽题用），下标越界返回 NULL
ShapeQuestion* QuestionBank::getQuestionByIndex(int index) {
    if (index < 0 || index >= (int)questions_.size()) {
        return NULL;
    }
    return questions_[index];
}

// 遍历输出全部题目
void QuestionBank::showAll() {
    cout << "======= 《" << name_ << "》共 " << questions_.size() << " 道题 =======" << endl;
    if (questions_.empty()) {
        cout << "题库中还没有题目，请先增加题目。" << endl;
        return;
    }
    // 实验五：使用 vector 的迭代器遍历所有题目
    vector<ShapeQuestion*>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        (*it)->showQuestion();
        cout << "    正确答案：面积 " << (*it)->getCorrectArea()
             << "，周长 " << (*it)->getCorrectPerimeter() << endl;
    }
}

// 清空题库：释放所有题目对象并清空 vector
void QuestionBank::clearAll() {
    vector<ShapeQuestion*>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        delete *it;
    }
    questions_.clear();   // 实验五：使用 vector 的 clear 清空元素
}

// 实验六：把题库中的所有题目保存到文件
// 每行一道题，格式：类型 编号 参数... 正确面积 正确周长 用户面积 用户周长 是否答对
void QuestionBank::saveToFile(string fileName) {
    ofstream fout(fileName);   // 打开文件（写入方式）
    if (!fout) {
        cout << "文件打开失败，无法保存！" << endl;
        return;
    }
    vector<ShapeQuestion*>::iterator it;
    for (it = questions_.begin(); it != questions_.end(); ++it) {
        ShapeQuestion* q = *it;
        Shape* s = q->getShape();
        fout << s->getType() << " " << q->getId() << " ";
        switch (s->getType()) {
        case 1:   // 正方形
            fout << static_cast<Square*>(s)->getSide();
            break;
        case 2:   // 长方形
            fout << static_cast<Rectangle*>(s)->getLength() << " "
                 << static_cast<Rectangle*>(s)->getWidth();
            break;
        case 3:   // 圆形
            fout << static_cast<Circle*>(s)->getRadius();
            break;
        case 4:   // 三角形
            fout << static_cast<Triangle*>(s)->getSide1() << " "
                 << static_cast<Triangle*>(s)->getSide2() << " "
                 << static_cast<Triangle*>(s)->getSide3();
            break;
        case 5:   // 梯形
            fout << static_cast<Trapezoid*>(s)->getTopBase() << " "
                 << static_cast<Trapezoid*>(s)->getBottomBase() << " "
                 << static_cast<Trapezoid*>(s)->getHeight() << " "
                 << static_cast<Trapezoid*>(s)->getWaist();
            break;
        }
        fout << " " << q->getCorrectArea() << " " << q->getCorrectPerimeter()
             << " " << q->getUserArea() << " " << q->getUserPerimeter()
             << " " << (q->getIsCorrect() ? 1 : 0) << endl;
    }
    fout.close();   // 关闭文件
    cout << "题库已保存到文件 " << fileName << "（共 " << questions_.size() << " 道题）。" << endl;
}

// 实验六：从文件读取题目，恢复题库
void QuestionBank::loadFromFile(string fileName) {
    ifstream fin(fileName);   // 打开文件（读取方式）
    if (!fin) {
        cout << "文件打开失败，无法读取（可能文件不存在）！" << endl;
        return;
    }
    clearAll();   // 先清空当前题库

    int type, id, isCorrect;
    double a, b, c, d;          // 图形参数（不同图形使用前几个）
    double ca, cp, ua, up;      // 正确面积/周长、用户面积/周长

    while (fin >> type >> id) {
        Shape* shape = NULL;
        switch (type) {
        case 1: fin >> a; shape = new Square(a); break;
        case 2: fin >> a >> b; shape = new Rectangle(a, b); break;
        case 3: fin >> a; shape = new Circle(a); break;
        case 4: fin >> a >> b >> c; shape = new Triangle(a, b, c); break;
        case 5: fin >> a >> b >> c >> d; shape = new Trapezoid(a, b, c, d); break;
        default: shape = NULL; break;
        }
        if (shape == NULL) {
            continue;
        }
        ShapeQuestion* q = new ShapeQuestion(id, shape);
        fin >> ca >> cp >> ua >> up >> isCorrect;
        q->setUserAnswer(ua, up);
        q->markResult(isCorrect == 1);   // 按保存时的状态恢复是否答对
        questions_.push_back(q);
    }
    fin.close();   // 关闭文件
    cout << "已从文件 " << fileName << " 读取题库，共 " << questions_.size() << " 道题。" << endl;
}

// 记录一次练习成绩（答对得 10 分）
void QuestionBank::recordResult(bool isCorrect) {
    totalAnswered_++;
    if (isCorrect) {
        totalScore_ += 10;
        correctCount_++;
    }
}
