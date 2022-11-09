# C++标准库

c++ standard library 与 c++ standard template library不一样。前者包含后者，但是后者是前者的大部分。

## STL总览

1. 容器：放数据，各种数据结构
2. 分配器：为容器服务，分配空间
3. 算法：使用容器中的数据进行运算
4. 迭代器：算法访问容器中的数据的中介。泛化的指针。指针能做它也能做。
5. 仿函数：为算法服务，算法实现的需要，像函数的类。
6. 适配器：三种适配器，将类转化为其他的样子，从而方便调用。

![image-20211221163239694](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221163239694.png)

## 简单例子

![image-20211221190108307](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221190108307.png)

## 注意点

1. 每个container都有.begin(), end()函数，返回值都是iterator。**包括begin不包括end**
2. 
