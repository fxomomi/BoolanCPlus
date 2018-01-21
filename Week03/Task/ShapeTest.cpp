#include "Shape.h"

int main() {
  Shape **buff = CreateRecAndCir();
  for (int index = 0; index < 20; index++) {
    buff[index]->Print();
  }
  cout << endl << "delete area less than 50" << endl << endl;
  int size = FilterShape(buff, 50);
  for (int index = 0; index < size; index++) {
    buff[index]->Print();
  }
  // 释放内存
  for (int index = 0; index < size; index++) {
    delete buff[index];  // 调用基类指针所指向子类的析构函数
    buff[index] = nullptr;
  }
  delete buff; // 释放数组空间
  getchar();
  return 0;
}