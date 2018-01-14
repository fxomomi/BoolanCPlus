#include "Rectangle.h"
#include <iostream>
using namespace std; 

int main(){
  Rectangle myRe = Rectangle(10,20,1,2);
  cout<<"myRe"<<endl;
  myRe.Print();
  Rectangle copyRe = Rectangle(myRe);
  cout<<"copyRe"<<endl;
  copyRe.Print();
  Rectangle assignRe = Rectangle(1,1,0,0);
  copyRe = assignRe;
  cout<<"copyRe after assign"<<endl;
  copyRe.Print();

  getchar();
  return 0;
}