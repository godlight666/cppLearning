### 普通类定义

1. 多个头文件，用来include,.h

2. 一些源程序，.cpp

3. 头文件中的防卫式声明（保证自己的运行环境）

   ```c++
   #ifndef __COMPLEX__		//如果之前没有定义complex
   #define __COMPLEX__		//就开始定义
   ...		//这里就可以是complex类的实现
   #endif
   ```

4. 接第3点，complex类的实现有三部分

   ```c++
   //前置声明
   #include <cmath>
   class ostream;
   class complex;
   complex&
       __doap1 (complex* ths, const complex& r);
   
   //类声明
   class complex{
       ......
   }
   
   //类定义
   complex::function...
   ```

5. 类声明怎么写

   ```c++
   class complex{
   public:
       //构造函数等一些函数...也可以有一些变量
       
       //注意构造函数的写法，它的初始化，还有函数重载，还可以放在private中
       complex(double r=0,double i=0):re(r),im(i){
           ...
       }
       //本体内实现的直接就是inline候选（不一定inline)
       //注意const，表示该函数不会修改变量的值，如果不加，当类的实例为const时，就会出错，不能调用该函数
       double real() const {return re;}
       double imag() const {return im;}
       //传递引用，只传地址，比较快，用const不让使用方修改
       complex& operator += (const complex&)
   private:
       double re,im;	//私有变量，变量尽量私有，访问修改靠函数
       //可以自由取得friend的private成员
       //同一个class的Objects互为friend
       friend complex& __doapl(complex*, const complex*);
   }
   ```

6. 函数（类定义部分）

   ```c++
   //实现操作符重载 +=
   //前面没有带class的名称，说明是全域部分
   inline complex& __doapl(complex* ths, const complex& r){
       ths->re += r.re;
       ths->im += r.im;
       //返回的是一个对象，但是返回类型是一个reference，没问题，这就是用reference的好处
       return *ths;
   }
   //带了class的名称，说明是类的函数，成员函数
   inline complex& complex::operator += (const compolex& r){
       //每个class中的函数，默认会有一个this变量指针，指向自己这个实例，所以能用this
       return __doapl(this,r);
   }
   ```

   ### 总结

   1. 构造函数的初始化可以特殊
   2. 函数该加const的就要加，参数该加的也要加
   3. 参数传递，返回值尽量考虑pass by reference
      1. 好处：速度快（只传地址，4字节），不用管接收者的接收形式，reference或value都可以
      2. 不能用：函数内的本地对象，返回时只能pass by value，不然会消失
   4. 数据放private