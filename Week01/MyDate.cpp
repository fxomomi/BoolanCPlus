#include "MyDate.h"

int main() {
  Date* dateArr = new Date[10];
  srand((unsigned)time(NULL));  // 重置随机数种子
  CreatePoints(dateArr, 10);
  for (int index = 0; index < 10; index++) {
    dateArr[index].Print();
  }
  std::cout << "Sort........" << std::endl;
  Sort(dateArr, 10);
  for (int index = 0; index < 10; index++) {
    dateArr[index].Print();
  }
  delete[] dateArr;
  getchar();
}