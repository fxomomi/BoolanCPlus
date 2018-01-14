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

### 3. new 与 构造, delete 与 析构
#### new
- 先分配 memory, 再调用 ctor
- `Complex* pc = new Complex(1,2);` ==> 

  ```
  void* mem = operator new(sizeof(Complex)); // 分配内存，内部调用 malloc(n)
  pc = static_cast<Complex*>(mem);           // 转型
  pc->Complex::Complex(1,2);                 // 调用构造函数
  ```

#### delete
- 先调用 dtor, 再释放 memory
- `delete pc;` ==> 

  ```
  Complex::~Complex(pc);                    // 析构函数
  operator delete(pc);                      // 释放内存，内部调用 free(pc)
  ```


    
  