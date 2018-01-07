#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__
#include <stdlib.h>
#include <time.h>
#include <iostream>

class Date {
 public:
  Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {}
  bool operator>(const Date&);
  bool operator<(const Date&);
  bool operator==(const Date&);
  void Print();

  //重置Date的值，用于排序时的交换
  void SetValue(int y = 0, int m = 0, int d = 0);

 private:
  int year;
  int month;
  int day;
};

/* ---------- Member Function Begin ---------- */
inline bool Date::operator>(const Date& r) {
  if (this->year != r.year) {
    return this->year > r.year;
  } else if (this->month != r.month) {
    return this->month > r.month;
  } else {
    return this->day > r.day;
  }
}

// 此处因为r传入的是const，所以不能直接返回 r > (*this)，TODO思考下哪种更合适
inline bool Date::operator<(const Date& r) {
  if (this->year != r.year) {
    return this->year < r.year;
  } else if (this->month != r.month) {
    return this->month < r.month;
  } else {
    return this->day < r.day;
  }
}

inline bool Date::operator==(const Date& r) {
  return this->year == r.year && this->month == r.month && this->day == r.day;
}

inline void Date::Print() {
  std::cout << this->year << "-" << this->month << "-" << this->day << std::endl;
}

inline void Date::SetValue(int y, int m, int d) {
  this->year = y;
  this->month = m;
  this->day = d;
}
/* ---------- Member Function End ---------- */

/* ---------- Global Function Begin ---------- */
// TODO:全局函数要不要加inline?
// 产生一个[min,max]间的随机数，参考来自Google
int RandNum(int min, int max) {
  return (rand() % (max - min + 1)) + min;
}

void RandomOneDay(Date& oneDay) {
  int year = RandNum(1991, 2050);
  int month = RandNum(1, 12);
  int day = 0;
  if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
      month == 10 || month == 12) {
    day = RandNum(1, 31);
  } else if (month == 2) {
    day = RandNum(1, 28);  // 暂时不考虑闰年二月
  } else {
    day = RandNum(1, 30);
  }
  oneDay.SetValue(year, month, day);
}

/*
题目要求生成10个随机的Date，且需用数组的形式返回，
若直接在函数内部分配堆空间，使用者有可能忘记释放内存，
造成内存泄漏，因此改为使用者自己分配空间，并指定数量的形式生成随机Date
*/
Date* CreatePoints(Date arr[], int size) {
  if (arr == NULL) return arr;
  for (int index = 0; index < size; index++) {
    RandomOneDay(arr[index]);
  }
  return arr;
}

// 数据量级不大且交换起来耗费较小，故直接采用冒泡排序，后续可根据情况在优化
void Sort(Date arr[], int size) {
  for (int rd = 0; rd < size; rd++) {
    for (int index = 0; index < (size - 1 - rd); index++) {
      if (arr[index] > arr[index + 1]) {
        Date tmp = arr[index];
        arr[index] = arr[index + 1];
        arr[index + 1] = tmp;
      }
    }
  }
}
/* ---------- Global Function End ---------- */

#endif
