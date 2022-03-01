# 模板template

## 基础

有模板函数和模板类，都写在对应声明的前面

输入的类型编译器就会生成不同的函数，会占空间。

```c++
//类模板
template <typename T1,typename T2>
class Account{
public:
    Account(const Account& acc);
    ...
private:
    T1 t1;
    T2 t2;
    ...
}
//函数模板
template <typename T1,typename T2>
bool min(T1 t1,T2 t2){...}
```

隐式实例化：调用函数的时候直接传进去，编译器自己识别是什么类型（实参推导），运行到该函数才会生成，效率低Swap(a,b)

显示实例化：Swap<int,double> (a,b)

## 成员模板 member template

成员模板：模板类中的成员也用了模板，比如模板函数。标准库中广泛用在构造函数中。

如下图所示，pair本身是模板类，它的一个构造函数也是模板函数。

这种方式使构造函数更有弹性，即构造函数的输入也是泛型。这时候就可以给参数加一些限制，比如模板函数的类必须是模板类的子类，不然初始化会失败（这是通过函数具体实现）

![image-20211220112441254](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220112441254.png)

## 模板特化 specialization

模板特化：就是使用模板后，又定义了对于该模板中一些特殊类型的不同的处理方式。使用 template<> 来定义。

如下图所示，有了hash模板类后，又为当类型是char，int或是long专门定义了hash。

**编译器会优先选择特化的。**

![image-20211220113910248](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220113910248.png)

## 模板偏特化 particial specialization

### 数量上的偏

在模板参数有多个时，只特化部分模板参数，剩下没特化的就要写在template<...>中，特化的就设定默认值，比如下面的bool，即第一个typename就被特化了，所以当T时bool时，就会调用该偏特化类。

![image-20211220114527836](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220114527836.png)

### 范围上的偏

就是制定某个范围用特定的类，其他的就用原本的类。

如下图，T*就能指定用指针的时候用这个类，其他的时候用原本的类。两个T并不是同一个东西。

![image-20211220114859674](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220114859674.png)

## 模板模板参数 template template parameter

就是某一个模板参数类，也是一个模板类。能够提供很大的灵活性。

如下图所示，SmartPtr就是一个模板类，它同时是模板参数。

**注意**：这个模板类必须只有指定个数个模板参数，比如SmartPtr，只有一个T，即一个模板参数，所以shared_ptr可以用，但是如果有多于1个模板参数，就不行，不能缺省。比如unique_ptr。

![image-20211220115500980](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220115500980.png)

而下面这个不是。是因为传进去的已经是list<int>了，完全确定的了。不像上面还是list，或者shared_ptr，还是灰色的，没有确定的。

![image-20211220115920160](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220115920160.png)