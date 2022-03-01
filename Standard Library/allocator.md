# 分配器allocator

分配内存空间等资源。container中都用了，默认是使用std::allocator，所以不需要自己指定。如下所示。allocator的指定在模板参数中。

![image-20211222110251034](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211222110251034.png)

## 指定allocator

编译器（比如gnu，vc）中会实现一些特定的allocator可以使用。如下所示是gnu的。

![image-20211222110447305](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211222110447305.png)

## 不要直接用allocator，因为释放的时候还要指定释放的内存大小！