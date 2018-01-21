#include "Shape.h"

int main(){
  Shape **buff = CreateRecAndCir();
  for (int index = 0; index < 20; index++){
    buff[index]->Print();
  }
  cout << endl;
  cout << "delete area less than 50" << endl;
  cout << endl;
  int size = FilterShape(buff, 50);
  for (int index = 0; index < size; index++){
    buff[index]->Print();
  }
  getchar();
  return 0;
}