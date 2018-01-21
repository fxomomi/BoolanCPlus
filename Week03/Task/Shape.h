#ifndef __MYSHAPE__
#define __MYSHAPE__
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

/*
要点：
  1. 父类指针指向子类对象，用一个父类指针数组去存放指向 Rectangle 和 Circle
的指针
  2. 通过虚函数调用到各子类对应的 getArea() 函数
  3. 父类的析构函数一定要设计为虚析构函数，否则 delete
父类指针时无法调用到子类的析构函数
  4. new 出的 Heap 内存空间，在使用完毕后一定要 delete 掉，包括 Rectangle、Circle
对象 和 指针数组
*/

const double PI = 3.1415926;

/* ---------- Class Declaration Begin ---------- */
class Shape {
 public:
  Shape(int no = 0) : no(no) {}  // Shape 构造函数
  virtual int getArea() = 0;
  virtual ~Shape() {}  // 虚析构函数
  // for test
  virtual void Print() = 0;

  // Get/Set
  int GetNo() const { return this->no; }
  void SetNo(int no) { this->no = no; }

 private:
  int no;
};
class Point {
 public:
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  // Get/Set
  int GetX() const { return x; }
  int GetY() const { return y; }
  void SetX(int x) { this->x = x; }
  void SetY(int y) { this->y = y; }

 private:
  int x;
  int y;
};
class Rectangle : public Shape {
 public:
  Rectangle(int no, int width, int height, int x, int y);  // 构造函数
  Rectangle(const Rectangle &other);                       // 拷贝构造
  Rectangle &operator=(const Rectangle &other);            // 拷贝赋值
  ~Rectangle() {                                           // 析构函数
    // for test
    cout << "Rectangle Destory" << endl;
  }

  int getArea();

  // for test
  void Print() {
    printf(
        "No: %2d  xRay: %2d  yRay: %2d  Width: %2d  Height: %2d  Area: %3d\n",
        this->GetNo(), this->leftUp.GetX(), this->leftUp.GetY(), this->width,
        this->height, this->getArea());
  }

 private:
  int width;
  int height;
  Point leftUp;
};
class Circle : public Shape {
 public:
  Circle(int no, int radius, int x, int y);  // 构造函数
  Circle(const Circle &other);               // 拷贝构造
  Circle &operator=(const Circle &other);    // 拷贝赋值
  ~Circle() {                                // 析构函数
    // for test
    cout << "Circle Destory" << endl;
  }
  int getArea();

  // for test
  void Print() {
    printf("No: %2d  xRay: %2d  yRay: %2d  Radius: %2d  Area: %3d\n",
           this->GetNo(), this->center.GetX(), this->center.GetY(),
           this->radius, this->getArea());
  }

 private:
  Point center;
  int radius;
};
/* ---------- Class Declaration End ---------- */

/* ---------- Global Function Implementation End ---------- */
// 如题设要求随机生成10个Rectangle、10个Circle，并返回一个指针数组
// 每一个数组元素都指向一个Rectangle or Circle
Shape **CreateRecAndCir();
// 过滤掉 buff 中面积小于 minArea 的对象，并返回删除后数组的大小
int FilterShape(Shape **buff, int minArea);
/* ---------- Global Function Implementation End ---------- */

/* ---------- Rectangle Implementation Begin ---------- */
inline Rectangle::Rectangle(int no, int width, int height, int x, int y)
    : Shape(no), width(width), height(height), leftUp(x, y) {}

inline Rectangle::Rectangle(const Rectangle &other)
    : Shape(other),  // 优先调用基类的拷贝构造
      width(other.width),
      height(other.height),
      leftUp(other.leftUp.GetX(), other.leftUp.GetY()) {}

inline Rectangle &Rectangle::operator=(const Rectangle &other) {
  if (this == &other) {
    return *this;
  }
  Shape::operator=(other);  // 优先调用基类的拷贝赋值
  this->width = other.width;
  this->height = other.height;
  this->leftUp.SetX(other.leftUp.GetX());
  this->leftUp.SetY(other.leftUp.GetY());
  return *this;
}

inline int Rectangle::getArea() { return this->width * this->height; }
/* ---------- Rectangle Implementation End ---------- */

/* ---------- Circle Implementation Begin ---------- */
inline Circle::Circle(int no, int radius, int x, int y)
    : Shape(no), center(x, y), radius(radius) {}

inline Circle::Circle(const Circle &other)
    : Shape(other),
      center(other.center.GetX(), other.center.GetY()),
      radius(other.radius) {}

inline Circle &Circle::operator=(const Circle &other) {
  if (this == &other) {
    return *this;
  }
  Shape::operator=(other);  // 优先调用基类的拷贝赋值
  this->center.SetX(other.center.GetX());
  this->center.SetY(other.center.GetY());
  this->radius = other.radius;
  return *this;
}

inline int Circle::getArea() { return this->radius * this->radius * PI; }
/* ---------- Circle Implementation End ---------- */

/* ---------- Global Function Implementation Begin ---------- */
// 产生一个[min,max]间的随机数
int RandNum(int min, int max) { return (rand() % (max - min + 1)) + min; }
Shape **CreateRecAndCir() {
  srand((unsigned)time(NULL));  // 重置随机数种子
  Shape **buff = new Shape *[20];
  for (int index = 0; index < 10; index++) {
    buff[index] = new Rectangle(index + 1, RandNum(1, 10), RandNum(1, 10),
                                RandNum(1, 10), RandNum(1, 10));
  }
  for (int index = 10; index < 20; index++) {
    buff[index] =
        new Circle(index + 1, RandNum(1, 10), RandNum(1, 10), RandNum(1, 10));
  }
  return buff;
}
int FilterShape(Shape **buff, int minArea) {
  // left, right 指针用于指向 buff 的头和尾
  Shape **left = buff;
  Shape **right = buff + 19;
  int size = 0;
  while (left <= right) {
    int area = (*left)->getArea();
    if (area < minArea) {
      // 将需要删除元素与数组末端元素进行交换
      Shape *tmp = *left;
      *left = *right;
      *right = tmp;
      // 删除掉末端元素，并将 rihgt 前移，同时调用对应对象的析构函数
      delete *right;
      *right = nullptr;
      right--;
    } else {
      left++;  // 满足条件，left 后移
      size++;  // 元素数量 ++
    }
  }
  return size;
}
  /* ---------- Global Function Implementation End ---------- */

#endif