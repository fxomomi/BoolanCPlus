#include "Shape.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 前置声明 
const double PI = 3.141592; 
Shape** createShape(int num);
Shape** filterShape(Shape* myshape[], int num, int &ncnt);  
void printShape(Shape* myshape[], int num);
void deleteData(Shape* myshape[], int num);

int main(){
	
	// 本来想用上一周写好的cout函数，但发现cout是非成员函数，使用不方便。因此在Test2种放弃使用cout，而建立了新的成员函数print

	cout << "---------- Test ----------" << endl;
	 
	const int num = 20;
	Shape** myshape = createShape(num);
	cout << "---------- Before filter ----------" << endl;
	printShape(myshape, num);  
	cout << "---------- After filter ----------" << endl;
	int ncnt = 0;
	Shape** filtershape = filterShape(myshape, num, ncnt);   
	printShape(filtershape, ncnt);  	
	deleteData(myshape, num);
	deleteData(filtershape, ncnt);
	return 0;	
}

Shape** createShape(int num) {
	Shape** myshape = new Shape*[num];
	time_t t;
	srand((unsigned)time(&t));
	for (int i=0; i<num/2; ++i) {
		int w = rand()%10 + 1;
		int h = rand()%10 + 1;
		int x = rand()%10 + 1;
		int y = rand()%10 + 1;
		myshape[i] = new Rectangle(w, h, x, y);
	}
	for (int i=num/2; i<num; ++i) {
		int r = rand()%10 + 1;
		int x = rand()%10 + 1;
		int y = rand()%10 + 1;
		myshape[i] = new Circle(r, x, y);
	}
	return myshape;
}

Shape** filterShape(Shape* myshape[], int num, int &ncnt) {
	Shape** filtershape = new Shape*[num];
	for (int i=0; i<num; ++i){
		if (myshape[i]->getArea()>=50) {
			filtershape[ncnt++] = myshape[i]->copy();
		} 
	}
	return filtershape;
}

void printShape(Shape* shape[], int num) {
	for (int i=0; i<num; ++i) {
		shape[i]->print();
	}
}
 
void deleteData(Shape* shape[], int cnt) {
	for (int i=0; i<cnt; ++i) {
		delete shape[i];
	}
	delete [] shape;
	shape = nullptr;
}
