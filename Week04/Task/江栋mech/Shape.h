#ifndef __MYREShape__
#define __MYREShape__

#include <iostream>
#include <iomanip>
using namespace std; 

class Shape
{                   
public:
	Shape() {no = ++ cnt;}
	Shape(const Shape& other)  { no = other.no; ++cnt; } 
	Shape& operator=(const Shape& other) { no = other.no; return *this; }
	int getNo() const { return no; } 
	virtual ~Shape()  {--cnt;}
	virtual int getArea() const =0;
	virtual Shape* copy() = 0;
	virtual void print() const = 0;
private:
	int no;
	static int cnt;
};
int Shape::cnt = 0;        // 静态变量要在类的body外面赋值 
              
class Point
{
private:
    int x;
    int y;
public:
    Point(int x1 = 0, int y1 = 0): x(x1), y(y1) { }
	int get_x() const { return x;}
	int get_y() const { return y;}
};

// Rectangle 类定义 
class Rectangle: public Shape
{
private:   
    int width;
    int height;
    Point * leftUp;
public:
    Rectangle(int w, int h, int x, int y);
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    ~Rectangle();
    int get_width() const { return width;}  
    int get_height() const { return height;} 
    Point* get_leftUp() const { return leftUp;} 
    virtual int getArea() const { return width*height;}
    virtual Shape* copy() { return new Rectangle(*this); }
    virtual void print() const { cout <<"Rectangle No." << setw(2) << setfill('0') << this->getNo() << "\'s area: "<< setw(3) << this->getArea() << "     "
	                             "(" << this->get_width() << "," << this->get_height() << "," << this->get_leftUp()->get_x() << "," << this->get_leftUp()->get_y() << ")"<< endl;;}
     
};

inline
Rectangle::Rectangle(int w = 0, int h = 0, int x = 0, int y = 0): width (w), height (h), leftUp (new Point (x,y)) {}
 
inline
Rectangle::~Rectangle()
{
	delete leftUp;    // new的对象是指针，不是array new 
	leftUp = nullptr;
}

inline
Rectangle::Rectangle(const Rectangle& other): Shape(other),        // Shape(other) 其实是copy了父类（具体是other）的一份数据。 
width(other.width), height(other.height)
{
    if(other.leftUp != nullptr){
    	this->leftUp = new Point(*(other.leftUp));    
	}
	else{
		this->leftUp = nullptr;
	}
}

inline
Rectangle& Rectangle::operator=(const Rectangle& other)
{
	if(this == &other)  
	    return *this;
	Shape::operator=(other);       // 对this用了基类的operator=，为this copy了父类（具体是other）的no。第9行。 
	width = other.width;     
	height = other.height;
	
	if(leftUp != nullptr)
	{
		if(other.leftUp != nullptr){
			*leftUp = *(other.leftUp);
		}
		else{
			delete leftUp;
			leftUp = nullptr;
		}
	}
	else
	{
		if(other.leftUp != nullptr)
		{
			leftUp = new Point(*(other.leftUp));
		}
	}
	return *this;
 } 



// Circle 类定义，和 Rectangle 类结构一致 
extern const double PI;

class Circle: public Shape
{
private:
	int radius;
	Point* center;
public:
    Circle(int r, int x, int y);
    Circle(const Circle& other);
    Circle& operator=(const Circle& other);
    ~Circle();
    int get_radius() const { return radius;}  
	Point* get_center() const { return center;} 
    virtual int getArea() const { return PI * radius * radius;}
    virtual Shape* copy() { return new Circle(*this); } 
    virtual void print() const { cout << "Circle    No." << setw(2) << setfill('0') << this->getNo() << "\'s area: " << setw(3) << this->getArea() << "     "
	                             "(" << this->get_radius() << "," << this->get_center()->get_x() << "," << this->get_center()->get_y() << ")"<< endl;;}

};
  
inline
Circle::Circle(int r = 0, int x = 0, int y = 0): radius (r), center (new Point (x,y)) {}
 
inline
Circle::~Circle()
{
	delete center;     
	center = nullptr;
}

inline
Circle::Circle(const Circle& other): Shape(other),       
radius(other.radius)
{
    if(other.center != nullptr){
    	this->center = new Point(*(other.center));    
	}
	else{
		this->center = nullptr;
	}
}

inline
Circle& Circle::operator=(const Circle& other)
{
	if(this == &other)  
	    return *this;
	Shape::operator=(other); 
	radius = other.radius;     
	
	if(center != nullptr)
	{
		if(other.center != nullptr){
			*center = *(other.center);
		}
		else{
			delete center;
			center = nullptr;
		}
	}
	else
	{
		if(other.center != nullptr)
		{
			center = new Point(*(other.center));
		}
	}
	return *this;
 }

 
 #include <iostream>
 using namespace std;
 
 ostream& operator<<(ostream& os, const Rectangle& rec)
 {
 	os << "Rectangle No." << setw(2) << setfill('0') << rec.getNo() << "\'s area: " << rec.getArea() << endl;
 	return os;
 }

 ostream& operator<<(ostream& os, const Circle& cir)
 {
 	os << "Circle No." << setw(2) << setfill('0') << cir.getNo() << "\'s area: " << cir.getArea() << endl;
 	return os;
 }
 
#endif 
