# 引用

引用：某个变量的别名，使用时必须初始化，且后续不能变更。

**使用上一切都完全和变量一样**，包括sizeof，包括取地址符&，**但是这些是假象**，它本质实现上用的const pointer，所以作为参数或者返回返回类型时，**传递的是地址**，能够减小消耗，而使用上又能像变量一样。

![image-20211220120625078](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220120625078.png)

## 常见用途

用在参数和返回。

要注意二义性。

![image-20211220205121969](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220205121969.png)

## 易错点

1. 当返回类型为引用时，如果返回的变量为函数内部变量，则不能返回，因为函数结束该变量的资源被释放了。如下所示：

   ```c++
   string& toMorse(string word) const {
       // res为内部变量
       string res;
       for (char &ch:word){
           res.append(MAP[ch-'a']);
       }
       // 返回res的引用会出问题
       return res;
   }
   ```

   

2. 