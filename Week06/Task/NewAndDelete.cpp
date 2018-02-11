#include "NewAndDelete.h"

int main() {

	// Fruit
	cout << "===============" << setw(15) << setiosflags(ios::left) << " Fruit Begin" << "===============" << endl;
	Fruit* pFruit = new Fruit();
	delete pFruit;
	Fruit* pArrFruit = new Fruit[3]();
	delete[] pArrFruit;
	cout << "===============" << setw(15) << " Fruit End" << "===============" << endl << endl;

	// Apple
	cout << "===============" << setw(15) << " Apple Begin" << "===============" << endl;
	Apple* pApple = new Apple();
	delete pApple;
	Apple* pArrApple = new Apple[3]();
	delete[] pArrApple;
	cout << "===============" << setw(15) << " Apple End" << "===============" << endl << endl;

	// ::opeartor new & ::opeartor delete
	cout << "=============== Global opeartor Begin ===============" << endl;
	Apple* pgApple = ::new Apple();
	::delete pgApple;
	Apple* pgArryApple = ::new Apple[3]();
	::delete[] pgArryApple;
	cout << "=============== Global opeartor End ===============" << endl;

	getchar();
	return 0;
}

/*
=============== Fruit Begin   ===============
Global::opeartor new(). size=32
Fruit::ctor. this=030AADE0 no=1
Fruir::dtor. this=030AADE0 no=1
Global::opeartor delete(). pdead: 030AADE0 size=32
Global::opeartor new[](). size=100
Fruit::ctor. this=030A52D4 no=1
Fruit::ctor. this=030A52F4 no=2
Fruit::ctor. this=030A5314 no=3
Fruir::dtor. this=030A5314 no=3
Fruir::dtor. this=030A52F4 no=2
Fruir::dtor. this=030A52D4 no=1
Global::opeartor delete[](). pdead: 030A52D0 size=100
=============== Fruit End     ===============
分析：
1、Furit 类没有重载 member operator new,new[],delete,delete[] 因此调用的是全局版本。
2、使用 new 构造一个 Fruit 对象时申请了 32 字节的内存，与上一节分析一致，其中包含一个 8 字节的虚指针、int no 4+4、double weight 8、 char key 1+7
3、构造对象时先申请内存，后调用构造函数。析构对象时先调用析构函数，后释放内存。
4、使用 new[] 构造构造3个 Fruit 对象时申请了 100 字节的内存，其中 96 字节为 3 个 Fruit 的大小，多出来的字节用于存放数组大小
5、数组中的对象先构造的后析构，后构造的先析构。如结果中所示 no=3 的对象最后才构造，但最先析构。

=============== Apple Begin   ===============
Apple::opeartor new. size=40 return: 030AADE0
Fruit::ctor. this=030AADE0 no=1
Apple::ctor. this=030AADE0
Apple::dtor. this=030AADE0
Fruir::dtor. this=030AADE0 no=1
Apple::opeartor delete. pdead: 030AADE0 size=40
Apple::opeartor new[]. size=124 return: 030AA1B0
Fruit::ctor. this=030AA1B4 no=1
Apple::ctor. this=030AA1B4
Fruit::ctor. this=030AA1DC no=2
Apple::ctor. this=030AA1DC
Fruit::ctor. this=030AA204 no=3
Apple::ctor. this=030AA204
Apple::dtor. this=030AA204
Fruir::dtor. this=030AA204 no=3
Apple::dtor. this=030AA1DC
Fruir::dtor. this=030AA1DC no=2
Apple::dtor. this=030AA1B4
Fruir::dtor. this=030AA1B4 no=1
Apple::opeartor delete[]. pdead: 030AA1B0 size=124
=============== Apple End     ===============
分析：
1、Furit 类重载了 member operator new,new[],delete,delete[] 因此调用的是 class member 的版本
2、使用 new 构造一个 Apple 对象时申请了 40 字节的内存，与上一节分析一致，其中包含一个 8 字节的虚指针、int no 4+4、double weight 8、 char key + int size 1+7, char type 1+7
3、构造 Apple 对象时首先调用父类 Fruit 的构造函数，其次才调用 Apple 的构造函数。
4、析构 Apple 对象时首先调用 Apple 自己的析构函数，其次才调用父类 Fruit 的析构函数。
5、使用 new[] 构造构造3个 Apple 对象时申请了 124 字节的内存，其中 120 字节为 3 个 Fruit 的大小，多出来的字节用于存放数组大小。
6、数组中的对象先构造的后析构，后构造的先析构。如结果中所示 no=3 的对象最后才构造，但最先析构。构造每个对象时先父类再子类，析构时再子类再父类。

=============== Global opeartor Begin ===============
Global::opeartor new(). size=40
Fruit::ctor. this=030AADE0 no=1
Apple::ctor. this=030AADE0
Apple::dtor. this=030AADE0
Fruir::dtor. this=030AADE0 no=1
Global::opeartor delete(). pdead: 030AADE0 size=40
Global::opeartor new[](). size=124
Fruit::ctor. this=030AA1B4 no=1
Apple::ctor. this=030AA1B4
Fruit::ctor. this=030AA1DC no=2
Apple::ctor. this=030AA1DC
Fruit::ctor. this=030AA204 no=3
Apple::ctor. this=030AA204
Apple::dtor. this=030AA204
Fruir::dtor. this=030AA204 no=3
Apple::dtor. this=030AA1DC
Fruir::dtor. this=030AA1DC no=2
Apple::dtor. this=030AA1B4
Fruir::dtor. this=030AA1B4 no=1
Global::opeartor delete[](). pdead: 030AA1B0 size=124
=============== Global opeartor End ===============
分析：
1、此处采用 ::new、::new[]、::delete 和 ::delete[] 来创建和删除对象，强制调用了 Global 的版本。
2、除了调用的是 Global 版本的 new 和 delete 函数外，其余分析与上例相同。
*/