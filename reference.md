# 引用

引用：某个变量的别名，使用时必须初始化，且后续不能变更。

**使用上一切都完全和变量一样**，包括sizeof，包括取地址符&，**但是这些是假象**，它本质实现上用的const pointer，所以作为参数或者返回返回类型时，**传递的是地址**，能够减小消耗，而使用上又能像变量一样。

![image-20211220120625078](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220120625078.png)

## 常见用途

用在参数和返回。

要注意二义性。

![image-20211220205121969](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220205121969.png)