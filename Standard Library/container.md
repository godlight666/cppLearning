# 容器container

用来存储数据结构的。

模板类，一般有两个模板参数，第一个是元素类型，第二个是使用的allocator（一般会省略）

## 整体结构

整体就是常见的数据结构

1. sequence containers（顺序容器）:
   1. array：普通数组，长度不可变
   2. vector：可变长度数组，连续存储
   3. deque：双向队列，连续存储(假象)。**stack和queue是用deque实现的**，因为deque功能最强大。
   4. list：双向链表（实现上是双向循环链表），离散存储
   5. forward-list：单向链表
2. associative containers（关联容器key-value，都是不定序的）:
   1. Set/MultiSet
   2. Map/MultiMap
   3. Multi-表示可以key值可以重复。
   4. 实现方式：一般都用的红黑树。
3. unoredered containers （是2的一种）
   1. unordered set/multiset
   2. unordered Map/Multimap
   3. 实现方式：HashTable，拉链法，发生冲突时用一个链表存。找的时候先索引到对应链表，再遍历链表。当链表长度超过某个值，就会扩充长度（直接全部打乱）

![image-20211221200451949](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221200451949.png)

## 组织结构

缩进表示composition。左右两边是一个容器object的大小（bytes）

![image-20211224192354418](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211224192354418.png)

## Sequence containers

一般没有自己实现find，插入比较方便。

### Array

常规数组，存储空间连续，长度不可变。**初始化时需要指定长度。**

1. Array.size(): 元素个数
2. Array.front(): 第一个元素
3. Array.back()：最后一个元素
4. Array.data(): 返回存放该数组的第一个元素的地址。

### Vector

可变长数组，向后扩展，每次扩展大小都x2。

成长过程非常耗资源，因为要整体迁移，因为是连续空间。

添加元素用push_back()，**c++11有了emplace_back，效率更高**

.capacity()表示容量，一般大于数组所需，因为会提前扩充。（会导致浪费许多空间）

### priority queue

优先队列，composition了一个heap，heap composition了vector。

### List

双向链表。

内部自己实现了sort。

#### List内部实现

注意下图中的灰色节点，是一个

![image-20211224193924531](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211224193924531.png)

### Forward-list

单向链表，只有头指针，添加元素用push_front，访问的时候也只能.front()，不能.back()，也不能.size()

![image-20211221222138976](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221222138976.png)

### Deque

连续是假象，只是分段式连续。

![image-20211221222753638](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221222753638.png)

### Stack(容器的adapter)

只puch_back()和pop_back()的deque。无iterator

push()

pop()	

top()

size()

![image-20211221224253192](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221224253192.png)

### queue（容器的adapter)

只push_back()和pop_front()的deque。无iterator

push()

pop()

front()

back()

size()

![image-20211221224240301](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211221224240301.png)

## Associative containers

插入比较慢，查找快。一般都有自己实现find（）

### Set/MultiSet

集合。**红黑树实现。插入慢，查找快。**

insert()

find()自己实现的，比全局的find快很多。

**自动根据Compare<>()类进行排序，根据key的值来排序**。

有iterator，iterator就会根据顺序来遍历，**但是不能用iterator修改值**。

![image-20220113191340244](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20220113191340244.png)

下图是set的底层实现，可以看到就是创建了一个红黑树，然后所有操作都调用红黑树的操作。

![image-20220113192529379](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20220113192529379.png)

### Map/Multimap

key-value。也是红黑树实现，查找快，插入慢

find()自己实现的，很快。

**map能用[]方式访问、修改value，multimap不能**

使用方式：

```c++
multimap<long,string> m;
//注意insert要构建一个pair，pair也是标准库中的数据类型
//multimap不能用[]方式访问
m.insert(pair<long,string> (1,"hello"));

map<long,string> m2;
//map能够以这种方式访问，修改，但是本质上还是会形成pair
m2[1] = "hello";
//pair的key是first，value是second
```

**map有key和data，使用iterator可以改data不能改key。**key被自动的设置为const了，所以不能通过iterator修改

![image-20220113201235460](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20220113201235460.png)

#### map底层实现

map底层实现如下所示，也是一个红黑树，可以指定compare类从而根据需求比大小排序。

![image-20220113201409903](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20220113201409903.png)

#### map中的[]

![image-20220113202602531](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20220113202602531.png)

map[key]使用时，如果map中不存在key，则会调用value的默认构造函数，并且在map中新建这个key和value，并返回该value（默认构造函数的默认值）。

### unordered_set/multiset

hash table实现的set，hash冲突用拉链法解决。

### unordered_map/multimap

hash table实现的set，hash冲突用拉链法解决。

### map与unordered_map对比

map特有的：

1. map始终保证遍历的时候是按key的大小顺序的，这是一个主要的功能上的差异
2. map可以做范围查找，而unordered_map不可以。
3. map的iterator除非指向元素被删除，否则永远不会失效。unordered_map的iterator在对unordered_map修改时有时会失效。
4. 因为3，所以对map的遍历可以和修改map在一定程度上并行（一定程度上的不一致通常可以接受），而对unordered_map的遍历必须防止修改
5. map的iterator可以双向遍历，这样可以很容易查找到当前map中刚好大于这个key的值，或者刚好小于这个key的值

谈谈hashmap和map的区别，我们知道hashmap是平均O(1),map是平均O(lnN)的，实践上是不是hashmap一定优于map呢？这里面有几个因素要考虑：

1. hashmap的内存效率比map差，这是显而易见的
2. map的查找效率实践上是非常高的，如在1M数据中查找一个元素，需要多少次比较呢？20次。
3. map的查找效率比hashmap稳定。
4. hashmap查找时候要算hash，这个最坏时间复杂度是O(M)（M是key字符串的长度），如果你的key非常非常非常非常非常非常……长，基于比较的map通常只使用头几个字符进行比较，而hashmap要O(M)地算出hash
5. 内存布局会影响内存局部性，对性能会有影响