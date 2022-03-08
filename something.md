# 一些杂项

## struct和class的区别

1. 默认的继承访问权。class默认的是private,strcut默认的是public。
2. 默认访问权限：struct作为数据结构的实现体，它默认的数据访问控制是public的，而class作为对象的实现体，它默认的成员变量访问控制是private的。
3. “class”这个关键字还用于定义模板参数，就像“typename”。但关建字“struct”不用于定义模板参数

## conversion function(转换函数)

### 转出去的转换函数

注意，该转换函数函数名为 operator target_class()，**返回类型就是函数名，不可以有参数**，该函数告诉编译器，当需要将我这个类转化为double的时候，就可以转化，编译器自动会完成。

```c++
//一个分数类
class Fraction{
public:
    Fraction (int num,int den)
     :m_numerator(num),m_denominator(den){
        
    }
    //转换函数，转成double,
    operator double() const {
        return (double)m_numerator/m_denominator;
    }
    
private:
    int m_numerator;//分子
    int m_denominator;//分母
}
//调用
Fraction f(3,4);
double result = 4+f;	//f被转化为0.75
    
```

### non-explict/explict -one-argument ctor

转进来的时候直接就用构造函数就可以。

```c++
//一个分数类
class Fraction{
public:
    //non-explict-one-argument ctor,den有默认值，所以是one argument，即一个实参
    Fraction (int num,int den=1)
     :m_numerator(num),m_denominator(den){
    }
    Fraction& operator+ (const Fraction& fra) const {
        return Fraction(...);
    }
private:
    int m_numerator;//分子
    int m_denominator;//分母
}
//调用
Fraction f(3,4);
Fraction result = f+4;	//用ctor将4转化为Fraction，再调用operator+
```

此时，如果加上上面的转换函数。**就会出错，有二义性**，可以把4转化为Fraction，也可以把f转化为double

```c++
//一个分数类
class Fraction{
public:
    //non-explict-one-argument ctor,den有默认值，所以是one argument，即一个实参
    Fraction (int num,int den=1)
     :m_numerator(num),m_denominator(den){
    }
    //转换函数，转成double,
    operator double() const {
        return (double)m_numerator/m_denominator;
    }
    Fraction& operator+ (const Fraction& fra) const {
        return Fraction(...);
    }
private:
    int m_numerator;//分子
    int m_denominator;//分母
}
//调用
Fraction f(3,4);
Fraction result = f+4;	//出错，有二义性，可以把4转化为Fraction，也可以把f转化为double
```

这是，如果给构造函数加上explicit，就表示只能显式地调用构造函数，4就不会默认转化为Fraction，上面的问题就解决了，但是double还是不会转化为Fraction，所以还是报错。

```c++
explict Fraction (int num,int den=1):m_numerator(num),m_denominator(den){}
```

## pointer-like classes

### 智能指针

用该类的时候，可以当做在用指针，所以一般要有operator*()和operator->()。

**注意**：operator->返回后，还会自动加上->，继续作用下去

![image-20211219211058684](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211219211058684.png)

### 迭代器

用来遍历，指向对象。相比于智能指针，多了++和--等。

*的时候取迭代器指的内容，所以加上.data

->的时候取data的地址。

**注意**：相当于用户将该类视为data，但是链表内部不只有data，为了遍历还需要有前项指针和后项指针，但是用户不需要知道。

![image-20211219211626593](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211219211626593.png)

![image-20211219211804765](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211219211804765.png)

## function-like classes

像一个函数的类，特点：需要实现operator()函数。

![image-20211219213307838](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211219213307838.png)

```c++
//调用
pair test(1,2);
selsect1st<pair> s1;
//这就是像函数一样
auto x = s1(test); //x=1;
```

## namespace

就是一个命名空间，用来区分。不同命名空间的类，函数或者变量都可以同名，不会干扰，用的时候要指定命名空间。

## const

const：常量修饰符，表示不会被修改。

图中内容有以下几点需要注意：

1. 表格内容，理解。常量对象不能调用非常量成员函数。
2. const是函数签名的一部分
3. 根据2，说明可能有const和无const的同名函数同时存在。所以加上规则，当他两同时存在时，const对象只能调用const，**非const对象只能调用非const**。
4. **3的使用**：如图右边所示，string的实现类，string可能多个对象指向同一个string（复用），所以需要copy on write，所以当有可能修改时，需要考虑cow，不可能修改时就不需要考虑（更快），所以就实现两个函数，用const区分，const时不考虑，非const时考虑，使用的时候const String 就会调用const函数。很好！

![image-20211220235655827](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211220235655827.png)

## new 和 delete

new和delete都是表达式，无法重载。

new的组成：1. 用operator new (malloc) 分配内存 2. 调用类的构造函数

delete的组成：1. 调用析构函数。 2. 用operator delete 释放内存（free)

可以自己重写operator new 和 delete

![image-20211221095740959](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221095740959.png)

![image-20211221101201318](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221101201318.png)

### []

new[] 和 delete[] 中，operator都是一次性分配（释放）整个array对象所需内存，并且还有4bytes作为计数（array的长度，比如下图中的5）

![image-20211221101948842](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221101948842.png)

### placement new new（）

就是相当于new有参数了。

![image-20211221103638794](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221103638794.png)

这是个标准库里的例子，用在string中扩充申请量。

![image-20211221104013792](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221104013792.png)

## ：：

：：除了用在类和namespace指定，还能表示全局变量和全局函数。

## i++与++i

c++中，operator++(int)用来表示i++的操作，operator++()用来表示++i的操作，这两个操作都没有参数，参数只是为了区分这两个。

## 空指针

传统的c中用空指针用NULL，等同于0，而这会引起二义性。

所以c++11中新增了nullptr来作为空指针。

## push_back和emplace_back

都可以在vector尾部添加元素，emplace_back效率更高。

## 用iterator遍历容器

```c++
for (auto it = map.begin();it!=map.end();it++){
    //it就相当于一个指针，指向容器内的每个元素。这里用的容器是map
    res.emplace_back(it->second);
}
```

## map[]

map[key]使用时，如果map中不存在key，则会调用value的默认构造函数，并且在map中新建这个key和value，并返回该value。

## static初始化

static变量初始化要在类外面，不能在类内部。

## hash

c++标准库中实现了一些hash类，都是function-like class（实现了operator()），但是没有对于string的实现，只有char*的实现。

## 注意点

1. 转换函数没有参数，没有返回类型，函数名是operator+函数名
2. 转出去要写转换函数，转进来用构造函数，都是编译器默认使用的。如果给构造函数加了explicit，编译器就不会默认使用，只能显式地使用。
3. operator->返回后，还会自动加上->，继续作用下去