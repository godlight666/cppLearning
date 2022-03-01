## 面向对象的思想设计

面向对象关注类之间的关系

### composition复合

简单定义：has a，即一个类里面包含了另一个类

![image-20211216152729378](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211216152729378.png)

构造函数要**由内而外构造**，即先调用component的构造函数

```c++
//Component()是编译器默认会帮你加的默认构造函数，如果要使用别的构造函数，则也可以自己指定
Container::Container(...): Component() {自己的构造函数;}
Container::Container(...): Component(a,b) {自己的构造函数;}
```

析构函数要由外到内释放，即先调用自己的，再调用component的

```c++
//编译器会默认自动帮你加
Container::~Container(){自己的析构；~Component();}
```

应用：**Adapter设计模式**，就是自己类（比如queue)的要实现的功能都在别的类中实现了（deque), 则可以直接调用，相当于一个适配器，转化一下接口。

### Delegation 委托 （Composition by reference)

简单定义：类中有另一个类的指针。

这样可以让另一个类对自己类进行实现，这样一个类就只是头文件，提供接口，**使得该接口可以有多种实现，并且实现的改动不会影响接口调用**

**Handle/Body (pImpl)**

![image-20211216153851397](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211216153851397.png)

### Inheritance 继承 与 virtual 虚函数

1. 子类继承父类，is a ，有父类的各个成员。在内存，构造函数，析构函数上与composition类似。

2. 函数在virtual上有三种分类：

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

3. **Template method**，即接口类提供模板，设计一个结构，子类根据这个模板来进行具体实现。如下所示。CMyDoc是CDocument的一个子类，实现特定的函数的serialize（）。调用的时候可以通过

   ![image-20211216222520932](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211216222520932.png)

### delegation+inheritance

#### observer设计模式

通过这种方式，能使得同一个接口多样化实现，适应不同的情况，即实现的类也是父类，父类可以有不同的子类实现。比如上图中，subject包含多个observer，即多个observer可以来观察subject，**这多个observer可以有不同的实现**，即多个子类。

![image-20211216223808691](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211216223808691.png)

#### Composite设计模式

这种方式可以用来设计类似文件系统，即文件系统中的每一个对象即可以是单个文件（Primitive），也可以是一个文件夹（文件的集合，Composite），而文件夹中又会包含很多对象。这种形式的方案设计就可以使用如下图所示的设计模式。

即a类可能包含多个b类，而a类和b类可能在同一个类中，就将a类和b类都设置为c类的子类，b类中可以包含c类。

![image-20211216225156104](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211216225156104.png)

#### prototype设计模式

这种设计模式很妙。**原型模式**要求对象实现一个可以**克隆自身**的接口(类型)。这样一来，通过**原型实例**创建新的对象，就不需要关心这个**实例本身**的类型，只需要实现**克隆自身**的方法，也而无需再去通过`new`来创建。

比如如下的结构中，Image类是之前写好的，下面两个类是后面实现的，但是要将新实现的类融入之前的接口中。可以看到，LandSatImage有一个静态对象，是自己本身的实例，然后类中有一个clone（）函数，能够新建一个LandSatImage对象并作为返回值。

LandSatImage调用Image的addPrototype将自己的静态实例加入Image的prototypes[]中，然后Image就能通过该实例调用clone()函数来新建LandSatImage对象（clone()中调用自己的构造函数来新建对象），然后Image就能通过这个新的对象来使用LandSatImage。

在这种情况下，在写Image的时候，都不知道LandSatImage存在，不知道它是什么样的，但是却能够在之后将它调用起来，很妙。

**注意**：可以看到LandSatImage()中有两个构造函数，默认调用中会addPrototype，但是新建对象的时候不能总add，所以需要第二个构造函数来区分开，新建对象的时候就用第二个。

![image-20211216230931761](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211216230931761.png)

![image-20211219174413832](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211219174413832.png)