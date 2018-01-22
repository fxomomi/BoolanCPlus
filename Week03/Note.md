## Object Oriented Programming(OOP)

### 类与类的关系
- Inheritance(继承)
- Composition(复合)
- Delegation(委托)

---
### 1. Composition(复合)，表示 has-a
#### Adapter
*容器 A 包含实现多种功能的类 B, A 可选择性包含部分 B 中需要的部分* 
- ![Composition](http://upload-images.jianshu.io/upload_images/9987091-0f199bfa65a0f12b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

-   ```
    // queue 'has-a' deque
    template <class T>
    class queue{
      ....
      protected:
        deque<T> c; //底层容器
      public:
        // 以下完全利用 c 的操作函数完成
        bool empty() const { retrun c.empty;}
        size_type size() const { return c.size(); }
        ....
    }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
    ```
  
#### 大小计算
*复合类的大小由复合的类的大小决定,计算式逐个相加*
-  ```
    // Sizeof: 40
    template<clss T>
    class queue {
      protected:
        deque<T> c;
        ...
    };
    ```
    ```
    // Sizeof: 16 * 2 + 4 + 4
    template <class T>
    class deque {
      protected:
        Itr<T> start;
        Itr<T> finish;
        T** map;
        unsigned int map_size;
    };
    ```
    ```
    // Sizeof: 4 * 4
    template <class T>
    struct Itr{
      T* cur;
      T* first;
      T* last;
      T* node;
    ....
    };
    ```

#### 构造和析构 
- **构造由内而外** 
  *由内而外基础才稳定，要做一个东西，要先弄地基*
  ```
  // Container 的构造函数首先调用 Component 的 default 构造函数，然后才执行自己
  // "Component()"由编译器
  Container::Container(...): Component() {}; 

  // 如果 default 的构造函数不满足要求，需要手动写明需要调用的构造函数
  Container::Container(...): Component(...) {}; 
  ```
- **析构由外而内**
  *想象在拆掉一个东西的时候需要由外而内一层层的拆*
  ```
  // Container 的析构函数首先执行自己，然后才调用 Component 的析构// 
  // "~Component()"由编译器添加
  Container::~Container(...): {.... ~Component() }; 
  ```

### 2. Delegation(委托)，Composition By Reference
#### Handle / Body 
*容器 A 中只包含指向功能 B 的指针，需要使用时才实例化 B 对象（可在任何时候将任务“委托”）。“编译防火墙”，需要修改时修改 B 即可。*
- ```
  class StringRep;
  class String {
    public:
      String();
      ...
    private:
      StringRep* rep;  //pimpl (point to implementation)
  }
  ```
- ![Delegation](http://upload-images.jianshu.io/upload_images/9987091-348821d1b596641f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- Reference Counting(共享技术)
![Reference Counting](http://upload-images.jianshu.io/upload_images/9987091-0c3a75954b5c03bf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3. Inheritance(继承)，表示 is-a
- ```
  struct _List_node_base{
    _List_node_base* _M_next;
    _List_node_base* _M_prev;
  };

  template<typename _Tp>
  struct _List_node: public _List_node_base {
    _Tp _M_data;
  }
  ```

#### 构造和析构
- ![Inheritance](http://upload-images.jianshu.io/upload_images/9987091-9d1306c73b105ebb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
- **构造由内而外**
  - Derived 的构造函数首先调用 Base 的 default 构造函数，然后才执行自己。
  - `Derived::Derived(...): Base() { ... };`
- **析构由外而内**
  - Derived 的析构函数首先执行自己，然后才调用 Base 的析构函数。
  - `Derived::~Derived(...): { ... ~Base(); };`
- **Base 的析构函数一定要是 virtual 的，否则会出现 undefined behavior**
- (扩展)用基类指针去操作子类对象时，若基类的析构函数不是虚函数，则在施放内存时**只会调用基类的析构函数**，造成内存泄漏。

#### Inheritance With Virtual Function
- ```
  class Shape {
    public:
      virtual void draw() const = 0;                // pure virtual
      virtual void error(const std::string& msg);   // impure virtual
      int objectID() const;                         // non-virtual
      ...
  }
  ```
  - pure virtual 函数： 你希望 derived class 一定要重新定义它，你对它没有默认定义。
  - virtual 函数：你希望 derived class 重新定义它，且你对它已有默认定义。 
  - non-virtual 函数：你不希望 derived class 重新定义它。
- 应用
  - Template Method
  ![Template Method](http://upload-images.jianshu.io/upload_images/9987091-ddbae53b1789427a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 对象组合
#### Inheritance + Composition
- ![Inheritance + Composition](http://upload-images.jianshu.io/upload_images/9987091-bde0c287468ca9de.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
- **构造由内而外**
  - Derived 的构造函数首先调用 Base 的 default 构造函数，然后调用 Component 的 default 构造函数，最后才调用自己。
  - `Derived::Derived(...): Base(), Component() { ... };`
- **析构由外而内**
  - Derived 的析构函数首先执行自己，然后调用 Component 的析构函数，最后调用 Base 的析构函数。
  - `Derived::~Derived(...): { ...~Component(), ~Base(); };`
 
#### Delegation + Inheritance
 **1.Observer**
![Observer](http://upload-images.jianshu.io/upload_images/9987091-779ba74acbff0187.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
- Subject 包含一个委托容器 Observer
- Observer 类可继承 
- Subject 控制流程，让 Observer 的子类根据需求来注册、注销

 **2. Composite**
![103.png](http://upload-images.jianshu.io/upload_images/9987091-3749f5eb1ed257b6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  - Composite---add不能写成纯虚函数，因为Primitive没有add的动作，如文件是不能有+的动作的，只有文件夹才有

 **3. Prototype** (Design Patterns Explained Simply)
![Prototype](http://upload-images.jianshu.io/upload_images/9987091-f935b85c4b628ea3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
- 创建未来的对象，需要每个子类自己创建一个自己给父类，让父类可以看到
- LandSatImage(子类) 创建静态的自己挂接到框架中-addPrototype
- Image(框架)用于创建未知的子类-findAndClone

- 代码图：
  - 负号代表private,#代表protected,正好or不写代表public
  - 先写名字，在写类型（如果必要）