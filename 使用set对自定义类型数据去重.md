# 使用set对自定义类型数据去重

## 需求

我的需求是有一个自定义类型Address，它有两个成员变量

```c++
//Address的成员变量
string name;
int number;
```

我想要使用一个set来存储各个Address，Address不能重复（要name和number都不相等才算不等）

```c++
//存储各个Address，不能重复
set<Address> myset;
```

## bug代码

我一开始参考了[c++中std::set自定义去重和排序函数](https://blog.csdn.net/wzzfeitian/article/details/70171512)中提到的，