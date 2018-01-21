## Object Oriented Programming(OOP)

### 类与类的关系
- Inheritance(继承)
- Composition(复合)
- Delegation(委托)

---
### 1. Composition(复合)，表示 has-a
#### Adapter
*容器 queue 包含实现多种功能的类 deque， queue 可选择性包含部分 deque 中需要的部分* 
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

#### Composition 关系下的构造和析构 
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
#### Handle / Body (point to implementation)
*容器 A 中只包含指向功能 B 的指针，需要使用时才实例化 B 对象（可在任何时候将任务“委托”）。“编译防火墙”，需要修改时修改 B 即可。*
- ![Delegation](http://upload-images.jianshu.io/upload_images/9987091-348821d1b596641f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- Reference Counting(共享技术)
![Reference Counting](http://upload-images.jianshu.io/upload_images/9987091-0c3a75954b5c03bf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


  
---
#### 未整理
1. Composition+Inheritance 关系下的构造和析构
  - 做一个练习--Derived有一个Component,考虑是Base先构造还是先Component
2. Delegation+Inheritance
  - Composite---add不能写成纯虚函数，因为Primitive没有add的动作，如文件是不能有+的动作的，只有文件夹才有
  - Prototype
    - 创建未来的对象，需要每个子类自己创建一个自己给父类，让父类可以看到
    - 利用addPrototype挂到父类上去

  - 代码图：
    - 先写名字，在写类型（如果必要）
    - 负号代表private,#代表protected,正好or不写代表public


