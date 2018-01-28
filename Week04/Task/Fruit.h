#ifndef __MYFRUIT__
#define __MYFRUIT__
class Fruit {
 public: // 方便測試将数据设置为 public
  int no;
  double weight;
  char key;

  void print() {}
  virtual void process() {}
};

class Apple : public Fruit {
 public: // 方便測試将数据设置为 public
  int size;
  char type;

  void save() {}
  virtual void process() {}
};
#endif