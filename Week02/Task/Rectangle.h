#ifndef __MYRECTANGLE__
#define __MYRECTANGLE__
#include <iostream>
/*
要点：
  1、拷贝构造、拷贝赋值一定要优先调用父类的对应函数
  2、任何涉及指针的操作一定要考虑nullptr的情况
*/
class Shape
{
  int no;
};
class Point
{
public:
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  void Print() { std::cout << this->x << "," << this->y << std::endl; }

private:
  int x;
  int y;
};
class Rectangle : public Shape
{
public:
  Rectangle(int width, int height, int x, int y); // 构造函数
  Rectangle(const Rectangle &other);              // 拷贝构造
  Rectangle &operator=(const Rectangle &other);   // 拷贝赋值
  ~Rectangle();                                   // 析构函数

  void Print()
  {
    std::cout << this->width << "," << this->height << std::endl;
    if (this->leftUp != nullptr)
    {
      this->leftUp->Print();
    }
    else
    {
      std::cout << "leftUp is nullpty" << std::endl;
    }
  }

private:
  int width;
  int height;
  Point *leftUp;
};

inline Rectangle::Rectangle(int width, int height, int x, int y)
    : width(width), height(height), leftUp(new Point(x, y)) {}

inline Rectangle::Rectangle(const Rectangle &other) // 优先调用基类的拷贝构造
    : Shape(other), width(other.width), height(other.height)
{
  if (other.leftUp == nullptr)
  { // 考虑nullptr的情况
    this->leftUp = nullptr;
  }
  else
  {
    this->leftUp = new Point(*other.leftUp); // 直接利用Point的默认拷贝构造函数
  }
}

inline Rectangle &Rectangle::operator=(const Rectangle &other)
{
  if (this == &other)
  {
    return *this;
  }
  Shape::operator=(other); // 优先调用基类的拷贝赋值
  this->width = other.width;
  this->height = other.height;
  if (this->leftUp == nullptr)
  { // 考虑nullptr的情况
    if (other.leftUp != nullptr)
    { // 左空右不空
      this->leftUp = new Point(*other.leftUp);
    }
  }
  else
  {
    if (other.leftUp != nullptr)
    { // 左不空右不空
      delete this->leftUp;
      this->leftUp = new Point(*other.leftUp);
    }
    else
    { // 左不空右空
      delete this->leftUp;
      this->leftUp = nullptr;
    }
  }
  return *this;
}

inline Rectangle::~Rectangle() { delete leftUp; }

#endif