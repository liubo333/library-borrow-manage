#pragma once
class Triangleltem
{
public:
	Triangleltem();
	Triangleltem(int a,int b,int c);
	void set(int a, int b, int c);
	void printTri();
	bool isTriangle();
	int calperimeter();
	float calarea();
	bool isRight();
	void flow();
	//get类的成员函数
	inline float getArea() { return m_area; }
	inline float getUarea() { return m_uarea; }
	inline float getA() { return m_a; }
	inline float getB() { return m_b; }
	inline float getC() { return m_c; }
	inline float getPerimeter() { return m_perimeter; }
	inline float getUperimeter() { return m_uperimeter; }
	inline float getScore() { return m_score; }
private:
	float m_area;
	float m_uarea;
	int m_a;
	int m_b;
	int m_c;
	int m_perimeter;
	int m_uperimeter;
	int m_score;
};

