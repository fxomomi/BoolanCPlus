#ifndef __MYFRUIT__
#define __MYFRUIT__
#include <iostream>
#include <iomanip>
using namespace std;

class Fruit {
	int no;
	double weight;
	char key;
	// static cnt 用于计数
	static int cnt;

public:
	Fruit() : weight(0.0), key(' ') {
		no = ++cnt;
		cout << "Fruit::ctor. this=" << this << " no=" << no << endl;
	}
	virtual ~Fruit() {
		--cnt;
		cout << "Fruir::dtor. this=" << this << " no=" << no << endl;
	}
	void print() {}
	virtual void process() {}
};
int Fruit::cnt = 0;

class Apple : public Fruit {
	int size;
	char type;

public:
	Apple() : size(0), type(' ') { cout << "Apple::ctor. this=" << this << endl; }
	~Apple() { cout << "Apple::dtor. this=" << this << endl; }

	// 重载 operator new & delete
	static void* operator new(size_t size);
	static void operator delete(void*, size_t size);
	static void* operator new[](size_t size);
	static void operator delete[](void* pdead, size_t size);

	void save() {}
	virtual void process() {}
};

void* Apple::operator new(size_t size) {
	Apple* p = (Apple*)malloc(size);
	cout << "Apple::opeartor new."
		<< " size=" << size << " return: " << p << endl;
	return p;
}
void Apple::operator delete(void* pdead, size_t size) {
	cout << "Apple::opeartor delete."
		<< " pdead: " << pdead << " size=" << size << endl;
	free(pdead);
}
void* Apple::operator new[](size_t size) {
	Apple* p = (Apple*)malloc(size);
	cout << "Apple::opeartor new[]."
		<< " size=" << size << " return: " << p << endl;
	return p;
}
void Apple::operator delete[](void* pdead, size_t size) {
	cout << "Apple::opeartor delete[]."
		<< " pdead: " << pdead << " size=" << size << endl;
	free(pdead);
}

// 重载全局 operator new & delete
inline void* operator new(size_t size) {
	cout << "Global::opeartor new()."
		<< " size=" << size << endl;
	return malloc(size);
}
inline void operator delete(void* pdead, size_t size) {
	cout << "Global::opeartor delete()."
		<< " pdead: " << pdead << " size=" << size << endl;
	free(pdead);
}
inline void* operator new[](size_t size) {
	cout << "Global::opeartor new[]()."
		<< " size=" << size << endl;
	return malloc(size);
}
inline void operator delete[](void* pdead, size_t size) {
	cout << "Global::opeartor delete[]()."
		<< " pdead: " << pdead << " size=" << size << endl;
	free(pdead);
}
#endif