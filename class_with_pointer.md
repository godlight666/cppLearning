## 带指针的类实现

```c++
class String{
public:
    String (const char* cstr=0);
    //拷贝构造函数 copy ctor
    String (const String& str);
    //拷贝赋值 
    String& operator= (const String& str);
    //析构函数，在生命周期结束的时候调用
    ~String ();
    char* get_c_str() const {return m_data;}
private:
    //有指针的类
    char* m_data;
};
```

```c++
//普通构造函数
inline
String::String (const char* cstr=0){
    if (cstr) {
        //分配空间
        m_data = new char[strlen(cstr)+1];
        strcpy(m_data,cstr);
    }else{	//未设定初值
        m_data = new char[1];
        *m_data = '\0';
    }
}
```

```c++
//析构函数，释放自己用的资源
inline
String::~String(){
    //当分配的空间的时候用的是array时，delete也要用array形式
    delete[] m_data;
}
```

```c++
//拷贝构造函数
inline
String::String(const String& str){
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
}
```

```c++
//拷贝赋值函数
inline
String& String::operator=(const String& str){
    //检查是否是自我赋值，如果是则会出错
    if (*this == str){
        return *this;
    }
    
    delete[] m_data;
    //String(str);
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
    return *this;
}

```

## 总结

1. 对于成员中有指针的类，有三个特殊的Big Three，即拷贝构造，拷贝赋值和析构函数。
2. 构造或者赋值的时候需要先用new分配空间，再赋值
3. 析构函数是生命周期结束的时候自动调用的，**要释放指针指向的内存占用，如果分配时是array，就要用delete[]**
4. new 用来在堆中分配空间，在vc中，一格子4bytes（32位），灰色的表示使用的，3表示数组长度为3,31h表示48+1，绿色的表示填充为16的倍数
5. new是先分配空间，再调用构造函数。delete是先调用析构函数（释放指向的空间），在调用operator delete释放空间（释放自身空间）
6. ![image-20211215181111343](C:\Users\Godlight666\AppData\Roaming\Typora\typora-user-images\image-20211215181111343.png)