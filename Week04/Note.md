<<<<<<< HEAD
## 目标
- 培养正规大气的变成素养上，继续探讨更多技术。
- 泛型变成和面向对象编程
- this指针，vptr虚指针，vtbl虚表，vitual mechanism虚机制，virtual functions虚函数，Polymorphism多态
=======
# C++ 面向对象高级编程
### 1.转换函数 
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
- 作用：可以把**这种东西**转换成**别的东西**

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
  - 因此会造成歧义
  
#### **Explicit**-One-Argument Ctor
    explict Fraction(int num, int den=1)
     : m_numerator(num), m_denominator(den) {}
    ...
    Fraction f(3,5);
    Fraction d2=f+4; // [Error] conversion from'double'to'Fraction'requested 
- 为了避免上述情况，需要指定 **Explicit** 关键字，表示不需要编译器自动的调用，只在真正构造函数的时候，才把 3 转换为 3/1
- 此时编译器不会吧 4 转换为 Fraction，因此会将 f 转换为 double 执行加法，最后在将结果转为 Fraction 的时候发现不行，报错
---

### 2.Pointer-Like Classes
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
      link_type_node;   // 真正的指针
      bool operator==(const self& x) const { return node == x.node;}
      ...
      reference operator*() const { return (*node).data; }
      pointer operator->() const { return &(operator*()); }
      ...
    };
- 迭代器也是一种智能指针，主要用于遍历容器。因此处了要支持 operaotr* 和 operator-> 外，一般还支持 operator==, operator!=, operator++, operator--
- 迭代器的 operator*，是需要获取 data 对象，因此需要返回 (\*node).data
- 迭代器的 operator->，是需要调用 data 对象的引用(指向 data 的指针)。如 ite->method(); ==> Foo::method() ==> (*ite).method(); ==> **(&(\*ite)**->method();
---

### 3.Function-Like Classes 
    template <class T>
    struct identity ... {
      const T&;
      operator() (const T& x) const { return x; }
    }
- 仿函数 function-lice classes
  - 新标准中又称为函数对象 function object
  - 行为类似函数的对象
  - 通过重载 **operator()**, function call operator 实现
- 为什么需要仿函数？
  - 一般情况下函数指针可以达到“**将整租操作当做算法的参数**”这一目的 
  - 函数指针不能满足 STL 对抽象性的要求，也不能满足软件积木的要求---函数指正无法和 STL 其他组件搭配，产生更灵活的变化。
  - **是无法定义一个模板函数的指针的**
- 用法：
  - `greater<int> ig; ig(4,6);`
  - `greater<int>()(6,4)` 第一个括号用于产生临时变量，第二个括号用于function call
- 应用场景
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
- 详情可参考 <<STL 源码剖析>> p413





>>>>>>> a2372335b74790c1985cd48f7ae25377513cade4
