## static

1. 全局静态变量：在全局变量前加上关键字static，在静态存储区，整个程序运行期间⼀直存在。未初始化会被自动初始化为0，作用域是声明它的源文件访问。

2. 局部静态变量：在代码块内部的声明的变量前面加上static，由自动变量变为静态变量。作用域仍为局部作用域，当定义它的函数或者语句块结束的时候，作用域结束。**但是当局部静态变量离开作用域后，并没有销毁，而是仍然驻留在内存当中，只不过不能再对它进行访问，直到该函数再次被调用， 并且值不变。**

3. 对于一个类的多个对象，非静态的变量每个对象都有一份，**非静态的函数却也只有一份**，大家共用，**通过隐含的this来区分**，而静态的成员则都只有一份。

4. 什么时候使用静态变量：该变量不会随着对象不同而改变。

5. static变量初始化要在类外面，不能在类内部。

6. 静态函数：**静态函数没有this指针**，所以不能使用非静态的变量。

7. 设定静态变量的两种方式：
   
   1. 通过类中定义的静态函数设定
   2. **通过实例化的对象调用函数设定**
   
   ```c++
   class Account{
   public:
       static double m_rate;
       static void set_rate(double rate){m_rate = rate;}
   }
   // static变量初始化要在类外面，不能在类内部。
   double Account::m_rate = 0.8;
   
   int main(){
       //通过类中定义的静态函数设定
       Account::set_rate(0.5);
   
       //通过类实例中定义的静态函数设定
       Account a;
       a.set_rate(0.5);
   }
   ```

8. static的应用：单例模式singleton
   
   ```c++
   Class A{
   public:
       static A& getInstance();
       setup(...) {...};
   private:
       //构造函数是私有的，只有自己能调用
       A(...){...}
       ...
   };
   static A& A::getInstance(){
       //创建静态实例，并返回
       static A a;
       return a;
   }
   
   int main(){
       //只能通过调用类的static函数来使用该实例，该实例是唯一的。
       A::getInstance().setup(...);
   }
   ```
