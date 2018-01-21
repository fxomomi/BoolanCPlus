## Class with pointer member(stirng)
### 1. Big Three
- 拷贝构造 `String(const String& str);`
- 拷贝赋值 `String& operator=(const String& str);`
- 析构函数 `~String();`

#### 构造函数和析构函数
- 构造函数
  - `String(const char* cstr = 0);` 
  - 字符串构造要注意检查是否为 **nullptr**
- 析构函数
  - 带有指针的 Class 多半会动态分配内存，因此在析构函数中要主动将动态分配的内存 delete 掉
  - ```
    inline String::~String(){
      delete[] m_data;
    }
    ```
> Class with pointer members 必须要有 copy ctor 和 copy op=
- 默认的copy ctor 和 copy op= 只会进行浅拷贝，会导致两个指针指向同一内存块，形成 alias 和 memory leak
- TODO 图片51页

#### 拷贝构造
- ```
  inline String::String(const String& str){
    m_data = new char[ strlen(str.m_data) + 1 ];
    strcpy(m_data, str.m_data);
  }
  ```
- String s2(s1) <===> String s2 = s1  *两者调用的都是拷贝构造函数*

#### 拷贝赋值    
- ```
  inline String& String::operator=(const String& str){
    if (this == &str)
      return *this;           // 检测自我赋值
    delete[] m_data;
    m_data = new char[ strlen(str.m_data) + 1 ];
    strcpy(m_data, str.m_data);
    return *this;
  }
  ```
- 步骤：
  1. 先释放自己 `delete[] m_data`
  2. 分配足够的内存 `m_data = new char[ strlen(str.m_data) + 1 ];`
  3. 拷贝数据 `strcpy(m_data, str.m_data);`
- 要点：
  - 返回类型要是String&,用于s1 = s2 = s3的使用情景
  - 一定要检测**自我赋值**,否则会造成undefined behavior
  - TODO 图片57页

---
### 2. Stack(栈) 与 Heap(堆) 
#### Stack
- `Complex c1(1,2);`
- 内存由编译器在需要时自动分配和释放。通常用来存储局部变量和函数参数。（为运行函数而分配的局部变量、函数参数、返回地址等存放在栈区）。
- 栈运算分配内置于处理器的**指令集**中，效率很高，但是分配的内存容量有限。
- Stack 对象的生命在作用域 Scope 结束之际结束，自动调用其析构函数


#### Heap
- `Complex* p = new Comples(3);`
- System Heap, 由操作系统提供的一块 global 内存空间，程序可动态分配从中获得若干区块
- **要配合使用 delete 或 delete[] 进行释放**,否则会造成内存泄漏

<<<<<<< HEAD
#### 其他内存块 [[参考]](https://www.cnblogs.com/findumars/p/5929831.html?utm_source=itdadao&utm_medium=referral)
=======
#### 其他内存块 [参考](https://www.cnblogs.com/findumars/p/5929831.html?utm_source=itdadao&utm_medium=referral)
>>>>>>> a2372335b74790c1985cd48f7ae25377513cade4
- 自由存储区：就是那些由malloc等分配的内存块，他和堆是十分相似的，使用free来释放内存
- 全局/静态存储区：全局变量和静态变量被分配到同一块内存中(在以前的C语言中，全局变量又分为初始化的和未初始化的，在C++里面没有这个区分了，他们共同占用同一块内存区)
- 常量存储区：一块比较特殊的存储区，里面存放的是常量，不允许修改。

#### 对象
- Stack Objects
  1. `Complex c1(1,2);` 
  2. 生命在作用域(Scope)结束之际结束
  3. 编译器自动调用其析构函数，因此又称为 auto object
- Static Stack Objects
  1. `static Complex c2(1,2);`
  2. 生命在作用域(Scope)结束之后仍存在，直至**整个程序**结束
- Global Object
  1. `Complex c3(1,2);` <br>
     `int main(){` <br>
      `...` <br>
     `}`  
  2. 生命在作用域(Scope)结束之后仍存在，直至**整个程序**结束
- Heap Objects
  1. `Complex* p = new Complex;`
  2. 生命在它被 delete 之际结束，调用其析构函数
  3. 若未 delete 则会造成 memory leak(指针p的生命已经结束了，但所致的heap object仍存在)

<<<<<<< HEAD
### 3. new & delete
#### new 与 构造
=======

### 3. new 与 构造, delete 与 析构
#### new
>>>>>>> a2372335b74790c1985cd48f7ae25377513cade4
- 先分配 memory, 再调用 ctor
- `Complex* pc = new Complex(1,2);` ==> 

  ```
  void* mem = operator new(sizeof(Complex)); // 分配内存，内部调用 malloc(n)
  pc = static_cast<Complex*>(mem);           // 转型
  pc->Complex::Complex(1,2);                 // 调用构造函数
  ```

#### delete 与 析构
- 先调用 dtor, 再释放 memory
- `delete pc;` ==> 

  ```
  Complex::~Complex(pc);                    // 析构函数
  operator delete(pc);                      // 释放内存，内部调用 free(pc)
  ```

#### 内存详情
*Single Object*
- 图片68
- 灰色部分为Debug模式额外添加的信息
- 绿色部分为对象数据所占空间，此处需要满足内存4字节对齐（青绿色标出）
- 内存块收尾为标记为，其值代表整个内存块大小。最后1位用于指示内存块的用途，1：送出 0：回收
*Array Object*
- 图片69

**Array new 一定要搭配 Array Delete**
- 图片70
- Array new 分配的内存的使用 delete 释放时，编译器仅会施放申请的内存，且只调用**1次析构函数**，会导致部分对象未正确析构

### 4. Static
*Static Data Member*
- 将数据与对象分离，与类绑定
- 一定要在类外初始化（真正的分配内存），赋不赋值均可
  - `class Account {`
    `public:`
      `static double m_rate;`
      `static void set_rate(const double& x) { m_rate =x; };`
    `}`
    `double Accont::m_rate = 8.0;`

*Static Function Member*
- 没有 This Pointer，只能用于处理Static Data
- 调用方式：
  - 通过 object 调用 `Accout a; a.set_rate(7.0);`
  - 通过 class name 调用 `Account::set_rate(5.0);`

*Singleton(单例)* [[参考]](http://blog.yangyubo.com/2009/06/04/best-cpp-singleton-pattern/) --- 把 ctor 放在 private 区
    
    class Singleton {
      public:
        static Singleton& Instance() {
          static Singleton theSingleton;
          return theSingleton;
      }

    /* more (non-static) functions here */

    private:
      Singleton();                            // ctor hidden
      Singleton(Singleton const&);            // copy ctor hidden
      Singleton& operator=(Singleton const&); // assign op. hidden
      ~Singleton();                           // dtor hidden
    };
- 在 Instance() 调用前，不会存在 theSingleton对象，没有内存的浪费
- Static 全局变量 vs. 普通全局变量
  - 全局变量本身就是静态存储方式， 静态全局变量当然也是静态存储方式。 这两者在存储方式上并无不同
  - 非静态的全局变量在各个源文件中都是有效的
  - 而静态全局变量则限制了其作用域， 只在定义该变量的源文件内有效， 在同一源程序的其它源文件中不能使用它
  - **全局变量改为静态后改变了它的作用域**
- Static 局部变量 vs. 普通局部变量
  - Static 局部变量存储在**静态区**，生命直至整个程序结束
  - 普通局部变量存储在**栈区**，生命仅在 Scope 内有效
  - **局部变量改为静态后改变了它的生命期**

    
  