## C++简介
### 书籍推荐
- 语言：C++Primer(C++第一个编译器者著), The C++ Programming Language(C++之父著)
- 标准库：The C++ Standard Library, STL源码剖析
- 提升：Effective C++

### Object Based vs. Object Oriented
- Object Based:面对的是单一class的设计。
- Object Oriented:面对的是多重classes的设计，classes和classes之间的关系。 

---


## Class without pointer member(complex)
### 1. 头文件
#### 代码基本形式
	// .h(Classes Declaration) + .cpp + .h(Standard Library)

    #include <iostream.h>
    #include "complex.h"
    ...
    ex.main()
    ...
	
#### Header中的防御式声明
	// 避免头文件重复include

	#ifndef __COMPLEX__
	#define __COMPLEX__
	....
	#endif

#### Header的布局
	// forward declaration(前置声明)
	#include <cmath>
	class ostream;
	....

<br>

	// calss declarations(类-声明)
	class complex{
		....
	};

<br>

	// class definition(类-定义)
	complex::function ....


### 2. Complex类设计 
#### inline(内联)函数
- 函数若在class内定义完成，便自动成为inline候选人
- 函数体外增加 **inline** 关键字定义<br>
	`inline double imag(const complex& x){ return x.imag(); }`
- **最终是否成为 *inline function* 由编译器决定，一般来说复杂的函数无法成为inline function**
- 内联是以**代码膨胀（复制）**为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率。 如果执行函数体内代码的时间，相比于函数调用的开销较大，那么效率的收获会很少。另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。

#### 访问级别
- **public**:函数部分(外界使用的)
- **private**:数据部分&函数部分(仅用于内部使用，不对外的)

#### 构造函数
* 语法 `complex (double r = 0, double i = 0) : re(r), im(i) {}`
	1. 名字与类名相同
	2. 有参数
	3. 可以有默认实参
	4. 不需要返回类型 
	5. **初值列**-速度会更快，初始化时即赋值
* (overloading)重载 
	1. 编译器会将函数名称、参数个数、参数类型进行编码，用于区分
* 构造函数放在 private
	1. 一般情况不放在 private 里面，除非你不想让外界创建
	2. Singleton(单例)模式会放在 private 里面

#### Const Member Functions(常量成员函数)
* 凡是不会改变数据内容的，尽量都加上const
	```
	// 不会改变数据内容的需要加上const
	double real() const { return re; }`
	double imag() const { return im; }`
	```
* 如使用者创建了一个const型的complex对象，此时去获取它的实部和虚部，若前面的函数没有加上const，就会出现“使用者不允许改变实部和虚部，但调用的函数**有可能**改变实部和虚部的情况，导致调用失败，因此能加const的地方，一定要加上const
	```
	const complex  c1(2,1);
	cout << c1.real();
	cout << c1.imag();
	```

#### Pass By Value vs. Pass By Reference(to const)
* Reference 等同于指针，无论对象多大，传的都只有4个byte
* 引用前可加 **const** ，避免接受者更改我的内存

	`complex& operator += (const complex&);`

* 参数传递尽量都 By Reference

#### Return By Value vs. Return By Reference(to const)
* 返回值的传递也尽量都 By Reference
* 函数操作的结果不是由自己创建的内存空间，一般可用 return by reference
* **传递者无需知道接受者是以 reference 形式接收**
	* 返回的都是object，至于接收端是 value 还是 refrence，传递者无需在乎

#### Friend(友元)
* 友元函数可以自由取得 private 成员 

	`friend complex& __doapl(complex*, const complex& r)`
* friend 是直接拿，若不设计为友元，也可提供其余接口函数让外部获取数据，不过会**慢一些**
* **相同 class 的各个 objects 互为 friends**
	```
	class complex{
		....
		int func(const complex& param){
			return param.re + param.im; // 直接取得了param的private成员
		}
		....
	}
	```

#### 重点
1. 构造函数要使用 initialization list
2. 函数本体内定义的函数需要加 const 的要加
3. 参数尽可能 by refrence, 另需考虑加不加 const
4. 返回值尽可能 by refrence
5. 数据放在 private 里

#### 扩展
1. Initialization List 为什么好？[参考地址](https://www.cnblogs.com/BlueTzar/articles/1223169.html)
	* 对于内置类型的成员初始化和赋值没有大的区别
		- 在成员初始化列表和构造函数体内进行，在性能和结果上都是一样的
	* 对于非内置类型的成员变量，初始化列表能够避免两次构造
		- 类类型的数据成员对象在进入函数体前已经构造完成，也就是说在成员初始化列表处进行构造对象的工作，调用构造函数，在进入函数体之后，进行的是对已经构造好的类对象的赋值，又调用个拷贝赋值操作符才能完成
	* 部分情况必须上进行显示的初始化
		- 成员类型是没有默认构造函数的类。若没有提供显示初始化式，则编译器隐式使用成员类型的默认构造函数，若类没有默认构造函数，则编译器尝试使用默认构造函数将会失败
		- const成员或引用类型的成员。因为const对象或引用类型只能初始化，不能对他们赋值。 
2. Protected 访问权限
	* public 和 private 代表类的封装，protected 代表类的继承
	* 成员能被派生类对象访问，不能被类外访问


### 3. 操作符重载与临时变量 
#### 成员函数
* 所有的成员都隐含一个参数 this，谁调用谁就是 this
	```
	inline complex& complex::operator +=(const complex& r){
		return __doapl(this, r);
	}
	```

#### 非成员函数
* 没有 this 指针
* 为了应付 client 的多种可能用法，需对应开发多个函数
	```
	inline complex operator + (const complex& x, const complex& y){
		....
	}

	inline complex operator + (const complex& x, double y){
		....
	}

	inline complex operator + (double x, const complex& y){
		....
	}
	```
* **上述函数不可 return by reference. 因为它们返回的必定是个 local object.**

#### Temp Object(临时对象)
* typename(); `complex();`
* 临时生成的，无需命名，生命到下一行就结束了

#### Return Void vs. Return Objects&
* 当使用者是的用法是需要连续使用时需要Return Object&
	```
	ostream& operator << (ostream& os, const complex& x){
		....
	}
	cout << c1 << conj(c1); 
	// cout << c1 执行结果，要能够接受 conj(c1)，因此返回的需要是ostream&
	```
