
# C++ 面向对象高级编程
## 目标
- 培养正规大气的变成素养上，继续探讨更多技术。
- 泛型变成和面向对象编程
- this指针，vptr虚指针，vtbl虚表，vitual mechanism虚机制，virtual functions虚函数，Polymorphism多态
---

## 一、模板
### 1. 转换函数 
#### Conversion Function(转换函数)
    operator double() const {
      return (double)(m_numerator / m_denominator);
    }
    ...
    Fraction f(3,5);
    double d=4+f; // 调用 operator double() 将 f 转为 0.6

- 没有 RetrunType
- 没有参数
- 转换不会改变 class 里面的 data,所以要加 const
- 任何一个Type都能作为转换函数，只要先前声明过，编译器认识
- 作用：可以把 **这种东西** 转换成 **别的东西**

<br>

- 编译器先找 global function operator+()
- 其次找转化函数 operator double()

#### Non-*Explicit*-One-Argument Ctor
    Fraction(int num, int den=1)
      : m_numerator(num), m_denominator(den) {}

    Fraction operator+(const Fraction& f) {
      return Fraction(...);
    }
    ...
    Fraction f(3,5);
    Fraction d2=f+4; // 调用 non-explicit ctor 将 4 转为 Fraction(4,1)
                     // 然后调用 operator+
    
- 数学上3就是3/1
- 作用：可以把**别的东西**转换成**这种东西**

#### Conversion Function vs. Non-Explicit-One-Argument Ctor
    Fraction(int num, int den=1)
     : m_numerator(num), m_denominator(den) {}
    operator double() const {
      return (double)(m_numerator / m_denominator);
    }
    Fraction operator+(const Fraction& f) {
      return Fatction(...);
    }
    ...
    Fraction f(3,5);
    Fraction d2=f+4; // [Error] ambiguous
- 此处有两种可能的路线
  - 调用 non-explicit ctro 将 4 转为 Fraction，再调用 operator+
  - 调用转换函数 double() 将 f 转为 double，在调用数学的加法，最后把结果通过 non-explicit ctor 转为 Fraction
  - **因此会造成歧义**
  
#### **Explicit**-One-Argument Ctor
    explict Fraction(int num, int den=1)
     : m_numerator(num), m_denominator(den) {}
    ...
    Fraction f(3,5);
    Fraction d2=f+4; // [Error] conversion from'double'to'Fraction'requested 
- 为了避免上述情况，需要指定 **Explicit** 关键字，表示不需要编译器自动的调用，只在真正构造函数的时候，才把 3 转换为 3/1
- 此时编译器不会吧 4 转换为 Fraction，因此会将 f 转换为 double 执行加法，最后在将结果转为 Fraction 的时候发现不行，报错
---

### 2. Pointer-Like Classes
#### 关于智能指针
    template<class T>
    class shared_ptr{
      public:
        T& operator*() const{
          return *px;
        }
        T* operator-> const{
          return px;
        }
        shared_ptr(T* p) : px(p) {}
      
      private:
        T* px;
        long* pn;
      ...
    }
    Foo f(*sp) ===> Foo f(*px);
    
    sp->method(); ===> px->method(); // "->"操作符作用下去得到的结果会继续作用下去
                                     // 因此此处的 sp 与 -> 结合得到 px 继续与 -> 作用
- 智能指针内部一定都有一个普通的指针，如上例中的 px
- 普通指针支持的功能智能也要支持。因此需要支持 operator* 和 operator->，写法基本如上
- 智能指针一般有一个接受一个普通指针作为参数的构造函数 `shared_ptr<Foo> sp(new Foo);` 

#### 关于迭代器
    template <class T>
    struct __list_node {
      void* prev;
      void* next;
      T data;
    };

    template<class T, class Ref, class Ptr>
    struct __list_iterator {
      typedef __list_iteraotr<T, Ref, Ptr> self;
      ...
      typedef __list_node<T>* link_type;
      link_type node;   // 真正的指针
      bool operator==(const self& x) const { return node == x.node;}
      ...
      reference operator*() const { return (*node).data; }
      pointer operator->() const { return &(operator*()); }
      ...
    };
- 迭代器也是一种智能指针，主要用于遍历容器。因此除了要支持 operaotr* 和 operator-> 外，一般还支持 operator==, operator!=, operator++, operator--
- 迭代器的 operator*，是需要获取 data 对象，因此需要返回 (\*node).data
- 迭代器的 operator->，是需要调用 data 对象的引用(指向 data 的指针)。如 ite->method(); ==> Foo::method() ==> (*ite).method(); ==> **(&(\*ite)**->method();
---

### 3. Function-Like Classes 
    template <class T>
    struct identity ... {
      const T&;
      operator() (const T& x) const { return x; }
    }
#### 仿函数 function-lice classes
- 
  - 新标准中又称为函数对象 function object
  - 行为类似函数的对象
  - 通过重载 **operator()** --- function call operator 实现
- **为什么需要仿函数？**
  - 一般情况下函数指针可以达到“**将整组操作当做算法的参数**”这一目的 
  - 但函数指针不能满足 STL 对抽象性的要求，也不能满足软件积木的要求---函数指正无法和 STL 其他组件搭配，产生更灵活的变化。
  - **是无法定义一个指向模板函数的指针的**
- 用法：
  - `greater<int> ig; ig(4,6);`
  - `greater<int>()(6,4)` 第一个括号用于产生临时变量，第二个括号用于调用 function call
- 场景
  ```
  template <typename T>
  class functor {
    void operator();
  };
  algorithm(first, last, ..., functorObj) { 
    ...
    functorObj(...);
    ...
  }
  ```
- 详情可参考 **<<STL 源码剖析>>** p413

#### 奇特的 base classes
  - ```
    template <class Arg, class Result>
    struct unary_function {
      typedef Arg argument_type;
      typedef Result result_type;
    };

    template <class Arg1, class Arg2, class Result>
    struct binary_function {
      typedef Arg1 first_argument_type;
      typedef Arg2 second_argument_type;
      typedef Result result_type;
    };    
    ```
  - less<int>::result_type ==> bool
  - 上述两个class大小理论值为0，但实际值可能为1(sizeof)
  - TODO:为什么要这样继承？
---

### 4. 模板
#### Class Template 类模板
    template<typename T>
    class complex {
      public:
        complex (T r = 0, T i = 0) : re(r), im(i) {}
        ....
      private:
        T re, im;
    }
- 使用者在使用时才指定 T 的类型 `complex<double> c1(2.5, 1.5);`

#### Function Template 函数模板
    template <class T>
    inline const T& min(const T& a, const T& b){
      return b < a ? b : a;
    }
- 使用时不必指明 Type，编译器会进行**实参推导（argument deduction）**,`r3 = min(r1, r2);`
- 模板在使用时会和使用代码一起编译一次，此时如果使用不当可能会报错。如上述 r1 和 r2 为 stone 类型时，会调用 stone::operator< ，若未定义则无法通过编译。

#### Member Template 成员模板
    template <class T1, class T2>
    struct pair {
      typedef T1 first_type;
      typedef T2 second_type;

      T1 first;
      T2 second;
      ....
      // begin
      template <class U1, class U2>
      pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
      //end
    }
- 是模板里的一个 Member，本身又是一个 Template
- 子类对象初始化父类容器
  - ![](http://upload-images.jianshu.io/upload_images/9987091-2ce42a8c46643f54.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - 把一个由鲫鱼和麻雀构成的 pair，放进(拷贝)一个由鱼类和鸟类构成的 pair 中
  - ```
    pair<Derived1, Derived2> p;
    pair<Base1, Base2> p2(p);  // 用子类对象构造的 p 去初始化父类的容器 p2，等价于
    ==> pair<Base1, Base2> p2(pair<Derived1, Derived2>())
    ```
- 模拟指针的 up-cast 操作
  - ```
    template<typename _Tp>
    class shared_ptr : public __shared_ptr<_Tp>{
      ...
      template<typename _Tp1>
      explicit shared_ptr(_Tp1* __p)  
       : __shared_ptr<_Tp(__p) { }
      ...
    };

    Base1* ptr = new Derived1;  // 用父类指针指向子类对象，up-cast
    shared_ptr<Base1> sptr(new Derived1); // 模拟 up-cast
    ```
--- 

### 5. Specialization 模板特化 
#### Full Specialization 特化（全特化）
    // 泛化
    template <class Key>
    struct hash { };

    // char 的特化版本
    template<>
    struct hash<char> {
      size_t operator() (char x) const { return x; }
    };

    // int 的特化版本
    template<>
    struct hash<int> {
      size_t operator() (int x) const { return x; }
    };
- 特化 --- 绑定模板泛化的部分，绑定后 template 后面尖括号内的内容无需写`template <>`

#### Parital Specialization 偏特化
- **个数** 的偏
  - ```
    // 泛化
    template<typename T, typename Alloc=...>  // 模板参数
    class vector {
      ....
    };
    
    // 偏特化
    template<typename Alloc=...>
    class vector<bool, Alloc> { // bool 型只占1个字节，因此可能需要一些特殊的处理
      ....
    };
    ```
  - 只部分绑定了 T，因此尖括号内的 Alloc 还需要写`template<typename Alloc=...>`
  - 绑定只能**从左到右**，不能绑定了1,3,5，不绑定2,4,6
- **范围** 的偏
  - ```
    // 泛化
    template <typename T>
    class C {
      ....
    };

    // 偏特化
    template <typename T>   --- 此处的 teypname T 不能省略
    class C<T*> {
      ....
    };
    ```
  - `C<string> obj1;`  --- 调用泛化版本
  - `C<string*> obj1;` --- 调用偏特化版本
  - 范围的偏 --- 缩小范围，如从任意类型 ==> 指针类型
--- 

### 6.Template Template Parameter 模板模板参数
    template<typename T
            template <typename T>  --- 拿第一个模板参数作为自身的参数
              class Container 
            >
    class XCls {
      private:
        Container<T> c;
      public:
        ....
    };
- 模板模板参数 --- 模板作为模板的参数，即模板参数本身是一个模板
- 用法：
  - `XCls<string, list> mylst1;` --- 此代码编译会报错，并不是由于模板模板参数造成，而是由于 list 在初始化时需要指定第二参数 alloc，且**不会自动利用默认参数**。
  - ```
    template<typename T>
    using Lst = list<T, allocator<T>>;   // C++2.0 新加语法，用于解决上述的问题
    XCls<string, Lst> mylst2;            // 编译通过
    ``` 
- **不是模板模板参数**
  - ```
    template <class T, class Sequence = deque<T>>
    class stack {
      ....
    };
    ```
  - 上述代码中的 `class Sequence = deque<T>` 不是一个模板模板参数
  - `stack<int, list<int>> s1;` --- 此时的 list<int> 已经不是一个模板了，已经没有泛化的部分了
---

## 二、C++11
  - ![](http://upload-images.jianshu.io/upload_images/9987091-fed95f831ca75122.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> Algorithms + Data Structures = Progams
> Tips: macro __plusplus 用于确认 C++ 的版本，199711 为 C++97,201103 为 C++11
### 1. Variadic Templates(since C++11)
![](http://upload-images.jianshu.io/upload_images/9987091-013762a864479dbc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - "..." 就是一个所谓的 pack (包)
  - 用于 template parameters, 就是 template parameters pack (模板参数包)
  - 用于 template parameters types, 就是 template parameters types pack (模板参数类型包)
  - 用于 function parameters, 就是 function parameters pack (函数参数包)
- *sizeof...(args)* 用于获取 args 的个数

### 2. Auto(since C++11)
    // 旧版本定义一个 iterator
    list<string> c;
    ....
    list<string>::iterator ite;
    ite = find(c.begin(), c.end(), target);

    // 新版本定义 
    list<string> c;
    ....
    auto ite = find(c.begin(), c.end(), target);
- 编译器会自己推算出的版本
- `auto ite; ite = ....` 是**错误**的，编译器无法推算出 ite 的类型

### 3. Ranged-Base for(since C++11)
    for ( decl : coll ) { 
      statement
    }
    ==>
    for ( int i : {1, 2, 3, 5, 7, 9} ) {
      cout << i << endl;
    }
- 把容器内的每个元素都遍历一遍
![](http://upload-images.jianshu.io/upload_images/9987091-a4e3eceec176ff66.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - 当需要改变元素的值时需要使用 pass by reference 

### 4. Reference(补充)
> 引用就是指针，一种 **漂亮** 的指针

![](http://upload-images.jianshu.io/upload_images/9987091-7dd356b4328aa0f9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - 引用在声明时一定要有**初值**
  - 赋值后其值不能再变改变
  - reference 本质上只占 4 byte(32位系统), 但 sizeof(x) == sizeof(r)
  - &x == &r
- reference 通常不用于声明变量，而用于 *参数类型(parameters type)* 和 *返回类型(return type)* 的描述
- 引用和值被视为同意中函数签名，因此不能只有两者不同时不能用于函数重载
  - ```
    double imag(const double& im) { .... }
    double imag(const double  im) { .... } // Ambiguity
    ```
> const 是函数签名的一部分 `double imga() {}` 和 `double imga() const {}` 是两个不同的函数
---

## 三、Object Model 对象模型 
### 1. vptr 和 vtbl
![](http://upload-images.jianshu.io/upload_images/9987091-0b12bf7909f67526.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - vptr --- 虚指针，指向虚表 vtbl, 一个类中只要有虚函数，就会有一个 vptr
    - 函数继承的是调用权，父类有虚函数，子类一定就也有
  - vtbl --- 虚表，存放所有虚函数的函数指针（地址哈哈）
  - C 语法：`(*(p->vptr)[n])(p); or  (* p->vptr[n] )(p);`
- **动态绑定三要素**
  - 函数通过 **指针** 调用
  - 指针向上转型 **up-cast** --- `A* p = new B(); // 父类指针指向子类对象` 
  - 调用的是 **虚函数**

### 2. 多态
![](http://upload-images.jianshu.io/upload_images/9987091-adfa8ec4b412697b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - `list<A*> myLst;` 通过父类指针容器存放不同的子类对象
  - 通过指针指向对象的不同调用不一样的 draw() 函数
  - 若用 C 来实现多态，一是写起来麻烦，需要判断指针指向的对象类型来调用不一样的 draw() 函数；二是缺乏扩展性，未来新增子类时还需重新更改判断的代码。

### 3. Template Method
![](http://upload-images.jianshu.io/upload_images/9987091-32b1212be4e60bd6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - “谁” 调用 “谁” 就是 **this** 指针
  - 通过虚函数的动态绑定机制，来实现模板方法。

### 4. Dynamic Binding
![](http://upload-images.jianshu.io/upload_images/9987091-19ee87c7813e85c3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](http://upload-images.jianshu.io/upload_images/9987091-e251c0ff917c09b4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


  - `a.vfunc1()` 属于静态绑定，调用是 `A::vfunc1()` 利用对象调用，不满足动态绑定的要求，对象是谁，调用的就是谁的方法
  - `pa->vfunc1() ==> call dword ptr [edx]` 即是 `(*(p->vptr)[n])(p)` 
---
字节对齐：http://blog.csdn.net/hairetz/article/details/4084088

## 四、补充
### 1. Const
- const member functions 常量成员函数
  - `const `加在 () 和 {} 之间 `double real () const { return re; }` 
  - 函数加上 const, 是告诉编译器该成员函数不会改变 class 的 data
  - 只有成员函数有 const, 一般全局函数没有 const
![](http://upload-images.jianshu.io/upload_images/9987091-ecfd9635159f9586.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 当成员函数的 const 和 non-const 版本同时存在时
  - **const** object 只能调用 const 版本
  - non-cosnt object 只能调用 non-const 版本
- `const String str("hello world") str.print();`
  - 若设计时未将 print() 函数指明为 const, 则在用const Object 调用 non-cosnt member function 时会出错。
#### 示例
    charT
    operator[](size_type) const {
      ....../* 不必考虑 COW */ 
    }
    reference 
    operator[](size_type) {
      ....../* 必须考虑 COW */ 
    }
    // COW: Copy On Write
- 标准库的`class template std::basic_string<>` 中有上述两个函数
- 标准库的 String 采用引用计数的规则，因此当有人想改变字符串时，必须考虑COW

### 2. 动态分配 New & Delete
#### 表达式 new & delete
- `Foo* p = new Foo;` ==>
  1. `void* mem = operator new(sizeof(Foo));` operator new 函数可被 **重载**
  2. `ps = static_cast<Foo*>(mem);`
  3. `p->Foo::Foo();`
- `delete p` ==>
  1. `p->~Foo();`
  2. `operator delete(p);` operator delete 函数可被 **重载**
- 重载 operator new 和 operator delete 可用于构建自己的 **内存池**
#### 重载 operator new() & operator delete()
- 全局重载 `::operator xxx`
  ```
  inline void* opeartor new(size_t size) {
    ....
  }
  inline void* opeartor new[](size_t size) {
    ....
  }
  inline void* opeartor delete(void* ptr) {
    ....
  }
  inline void* opeartor delete[](size_t size) {
    ....
  }
  ```
  - 上述函数不可以被声明于一个 namespace 内
  - 上述函数由编译器自动调用（上述表达式 new 和 delete 的分解步骤中）
  - 在构造对象时使用`::new`可强制使用 globals 的版本 `Foo* pf = ::new Foo;`
  - 对于全局的重载要格外小心，这些影响 **无远弗届**
- 重载 member operator new / delete
  ```
  void* operator new(size_t);
  void  operator delete(void*, size_t); // 第二个参数 size_t 可选
  ```
- 重载 member operator new[] / delete[]
  ```
  void* operator new[](size_t);
  void  operator delete[](void*, size_t); // 第二个参数 size_t 可选

  Foo* p = new Foo[N]; ==>
    1. void* mem = operator new(sizeof(Foo)*N + 4); // 多处来的 4 字节用于记录数组大小
    2. p = static_cast<Foo*)(mem);
    3. p->Foo::Foo(); // N 次

  delete[] p; ==>
    1. p->~Foo(); // N 次
    2. operator delete(p);
  ```
  - 数组中构造个对象的构造顺序与析构顺序相反，先构造的后析构，后构造的先析构
- 示例

![](http://upload-images.jianshu.io/upload_images/9987091-5f937c5482f5721a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](http://upload-images.jianshu.io/upload_images/9987091-8cb8ca2ff706230f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](http://upload-images.jianshu.io/upload_images/9987091-96867bb75434f713.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 重载多版本 new(), delete()
  - 可重载多个版本的 class member operator new()
    1. 每个版本都必须有 **独特** 的参数列
    2. 第一个参数必须是 size_t  
    3. 其余参数以所指定的 placement arguments 为初值
  - 可重载多个版本的 class member operator delete()
    1. 它们 **不会** 被 delete 调用
    2. 仅当 对应版本的 operator new 所调用的 ctor 抛出 exception 时，才会调用这些重载版本的 opeartor delete(), 只要用来归还未能完成创建功能的 object 所占用的 memory
    3. **opeartor delete(...) 未能一一对应于 operator new(...) 也不会报错** -- 代表设计者放弃处理 ctor 发出的异常
  - 应用 --- basic_string 使用 new(extra) 扩充申请量
![](http://upload-images.jianshu.io/upload_images/9987091-30bc935d16fef72c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
      - Rep 用于引用计数
 - 疑问?
    - operator delete() 是如何对应上 operator new() 的
    - 若 new(size_t) 的版本对应 delete(void*, size_t), 那么 new(size_t, size_t) 的版本对应怎样的 delete(...)