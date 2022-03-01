# Virtual

## 虚函数

```c++
class Shape{
public:
    //pure virtual，即父类中完全没有该函数的实现，要求子类必须覆写override
    virtual draw() const = 0;
    //impure virtual，父类中有该函数的实现，子类可以override也可以不override
    virtual error() {...}
    //non virtual，就是普通函数，在父类中实现。
    int object(){}
}
//子类
class Rectangle: Shape{...}
```

## 虚函数指针与虚函数表

当一个类有虚函数或者父类有虚函数（即有虚函数的使用权）的时候，该类的object的内存中除了有data，还有一个**指针vptr虚函数指针，该指针指向一个虚函数表vtbl**，vtbl中有各个虚函数的地址。通过这种方式索引到对应的虚函数实现调用。

如下图所示，子类对象会包含父类变量，也只有一个虚函数指针。**虚函数表中会有父类的虚函数地址**。

这种调用函数的方式称为**动态绑定。**传统的函数在编译的时候就会call 函数地址，这称为静态绑定。

这种实现方式完成了c++的**多态**。

动态绑定三个条件：

1. 一个指针p指向该对象
2. 该指针p在声明的时候使用up-cast，即声明的时候是父类，new的时候是对应的子类
3. 调用虚函数。

![image-20211220214524945](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220214524945.png)

![image-20211220214458074](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220214458074.png)

## 关于virtual和this的另一个例子

如图所示，myDoc调用父类的普通函数，该普通函数中用了一个虚函数，虚函数在myDoc中有实现。

在一个类中，每个类的成员函数都默认有this指针，该函数中调用所有其他的函数，除非指定，否则默认调用this-> method()，所以下面的例子能成立，即子类即有父类的成员函数（继承使用权），又有自己实现的虚函数，并通过上一阶段提到的方式进行动态绑定，调用。

![image-20211220215931483](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220215931483.png)

## 动态绑定

必须是指针的方式调用虚函数，不然还是静态绑定，注意上面说到的动态绑定的三个条件。

![image-20211220220410163](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220220410163.png)