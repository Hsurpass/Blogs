[Workspace](d:/Workspace)

# C

## 指针

悬挂指针：当指针所指向的对象被释放，但是该指针没有任何改变，以至于其仍然指向已经被回收的内存地址，这种情况下该指针被称为悬挂指针；

野指针：未初始化的指针被称为野指针。可能指向任意地址。

## stdarg.h

### 可变参函数

variable_parameter_function.c

### 可变参宏

```c++
// 宏定义的参数允许用"...", 表示是可变参数，在宏替换的时候用__VA_ARGS__表示"..."位置的所有参数
#define test1(...) printf(__VA_ARGS__)
#define test2(fmt, ...) printf(fmt, __VA_ARGS__)

// 很多编译器扩展了可变参数的宏替换，这样的写法更容易记忆，
// 宏定义的参数后面可以带三个小数点，表示这里是可变参数，
// 宏替换的时候，直接写这个参数就表示这个位置是所有的可变参数了。
// 注：某些编译器需要用 ##args 表示 args... 位置所有的参数的宏替换。
#define test3(fmt...) printf(fmt)
#define test4(fmt, args...) printf(fmt, args)
```

variable_parameter_macro.c

##__VA_ARGS__

C语言指针危险在哪？

​	指针可以自增，自减。++p, --p



## references:

[零基础入门C语言-王桂林.pdf](../wangguilin/-1- C 语言--从放弃到入门/零基础入门C语言-王桂林.pdf)

[-2- 你懂C语言，我不信--C提高篇](../wangguilin/-2- 你懂C语言，我不信--C提高篇)



# C++

函数重载

​	函数同名不同参，不同参包括参数的类型，个数，顺序， ==const==

虚函数覆写

同名同参同返回。

## 关键字

### new/delete 和 malloc/free 区别：

1. new/delete是关键字，malloc/free是函数
2. new/delete会调用构造和析构函数。
3. 内存分配失败，new会抛异常bad_alloc

### static
1.修饰全局变量：作用域和生命周期都是全局的，不能跨文件使用。

1.修饰局部变量：作用域在函数内, 生命周期是全局的。

2.修饰普通函数：不能跨文件使用，只能在当前文件使用，限制了函数的作用域。

3.修饰类成员变量：类内定义，类外初始化，全部对象共享一个static成员变量。

 								 静态成员变量是命名空间属于类的全局变量，存储在data区的rw段。

4.修饰类成员函数：静态成员函数只能访问static成员变量(没有this指针)， 不能访问非static成员变量(没有this指针)。



### const

1.修饰变量：该变量不可改变。

2.修饰指针：`const int *p` : p所指向的值不可变；  `int* const p`:  p这个地址不可变。

3.修饰引用：常量引用，常用作函数形参，避免了拷贝且不能对其修改。

4.const修饰成员函数：只能用const对象访问, 不可在成员函数内改变成员变量。嵌套调用的函数也只能是const的。

5.const修饰类对象：const对象只能调用const成员函数，不能调用非const成员函数。

​									非const对象两者都能调用，如果有const构成函数重载，则优先调用非const成员函数。

6.const可以作为函数重载的条件。

### 宏定义#define与const的区别

| 宏定义 #define             | const 常量   |
| -------------------------- | ------------ |
| 宏定义，==相当于字符替换== | 常量声明     |
| 预处理器处理               | 编译器处理   |
| 存储在代码段               | 存储在数据段 |
| 可通过 `#undef` 取消       | 不可取消     |

### inline

优点：相当于把函数体直接写在调用内联函数的地方。省去了进入/退出函数体的操作（压栈、出栈）。

缺点：代码膨胀，而且加了inline只是对编译的建议，是否该函数是内联的由编译器决定。

### volatile

使用volatile声明的变量，每次访问都必须从内存取值(没有用volatile声明的变量由于编译器的优化，可能直接从寄存器取值)

const可以是volatile的(如只读的状态寄存器)

指针可以是volatile的。

[volatile.md](<../ElegantTest/test_cpp/keyword/volatile/volatile.md>)

### explicit

禁止“单参构造函数”(拷贝构造、转化构造) 的隐式转换。

### extern 

1.extern修饰的是变量的声明，说明此变量将在==文件以外==或者==文件后面部分==定义。变量的声明不分配内存，定义的时候才分配。

2.extern “C”{}

c++编译器默认是对函数进行命名倾轧(name mangling)的(就是编译完后函数名字都变了)，要想有的函数不进行倾轧使用extern “C” {}。

```c++
#ifdef __cplusplus
extern "C" {
#endif

void *func(void *, int, size_t);

#ifdef __cplusplus
}
#endif
```

### reference &

引用一经声明不可变更。初始化时为谁的引用就是谁的引用，不可中间在更改引用的对象。



## 友元friend

1.能访问私有成员，破坏了封装性。

2.友元关系不能被继承

3.友元关系不可传递：B是A的友元，C是B的友元，C不是A的友元。

4.且是单向的：B是A的友元，A不是B的友元。

友元函数、友元类：

-   声明为谁的友元，==就可以通过谁的对象，==访问谁的私有成员。

-   友元的声明位置可以是类中的任意位置，不受public/private/protected的影响。

-   全局函数做友元，只需在类中做声明即可；成员函数做友元在做声明的同时还需加上类作用域,如：A::。

子类使用父类的友元函数：

​	由于友元函数不能继承，但是子类又想使用父类的友元函数，==可以通过强制类型转换，将子类的指针或引用强转为父类的指针或引用（赋值兼容），==然后再去调用父类中的友元函数。







## 内存



### 内存四区

### 内存对齐

设定结构体、联合以及类成员变量以 n 字节方式对齐。#pragma pack(n)

```c++
#pragma pack(push)  // 保存对齐状态
#pragma pack(4)     // 设定为 4 字节对齐

struct test
{
    char m1;
    double m4;
    int m3;
};
// sizeof(test) == 16
// 不设置4字节对齐 sizeof(test) == 24
#pragma pack(pop)   // 恢复对齐状态
```

 

### 内存泄漏



## 面向对象

类

​	类的构造顺序：先父类，再成员变量，最后子类。

​	初始化参数列表

​		类内成员变量的初始化顺序与初始化列表的顺序无关，与其自身定义的顺序有关。

​		效率更高，少了一次调用默认构造和赋值。

​		引用类型成员要用初始化列表，因为引用必须在定义时初始化。 

​		const成员必须要用初始化列表，因为const也是在定义时初始化，且const变量不可更改。	

​	深拷贝

​	6大构造/赋值：默认构造、拷贝构造、拷贝赋值、移动构造、移动赋值、析构。

​	转换构造、转换赋值：convert_constructor.cpp

```c++
A(const B& b){ m_a = b.m_b; }	// 转换构造
A& operator=(const B& b){ m_a = b.m_b; return *this; }	//转换赋值

 B b(10); A a = b;	// 隐式调用转换构造

B b1(100); a = b1;	// 隐式调用转换赋值

const A& a1 = b1;	// 隐式调用转换构造
```



​	



this指针

指向当前对象的指针。

this指针被隐式的声明为：`T* const this`,这就意味着this不可修改；

而const成员函数：`const T* const this `,表明this和this指向的成员变量都不可修改。



==用空指针调用空函数体的成员函数不会崩(因为this指针没调用任何成员变量)。==

指向类成员变量/成员函数的指针

​	pointer_to_memfunc.cpp

```c++
int A::*pa = &A::m_a;
void (A::*paf)() = &A::dis;
```

​	==指向类成员的指针，本质存放的不是地址，存放的是偏移量==



指向类静态成员变量/静态成员函数的指针

​	指向静态成员的指针定义方法和普通指针相同，无需和类名关联，调用时也无需和类对象关联。

```c++
int *pb = &A::m_b;
void (*pbf)() = &A::dis_static; 
```



封装

​	就是把属性和方法都写到类中，并且用public/protected/private赋予访问权限。

继承

子类public/protected/private继承父类中的私有成员都是不可访问的。

​	复制兼容：

​	子类对象可以直接赋值给父类对象

​	子类对象的指针或引用可以直接赋值给父类对象的指针或引用。



​	同名隐藏：

​		如果子类父类中有同名的==变量、函数名==(无关乎返值和参数)，则子类调用时默认使用的时子类的；要想使用父类的以==父类名+作用域运算符==的方式来调用。



​	多重继承

​		构造顺序



多态

​	虚函数

​	虚析构

## 编译过程

​	编译静态库，动态库



## 模板

### 模板特化

template.cpp

### 嵌套从属类型需要加typename

template_nested_type.cpp

### 可变参数模板

当我们既不知道参数的数目又不知道参数的类型的时候，就可以使用可变参数模板。

默认参数都是传值的，如果参数是类，效率很低，所以改成传引用 `ARGS&... args` or `ARGS&&... args`

C++Primer 第5版 16.4

variadic_template.cpp

https://www.modb.pro/db/463275

### 非类型模板参数

```c++
template<typename T, int N> func(T (&arr)[N])
```

nonType_template_param.cpp



## references:

[C++基础与提高-王桂林-4rd.pdf](../wangguilin/-3- 这可能是你见过的最NB的C++课程/C++基础与提高-王桂林-4rd.pdf)

[C++基础与提高-王桂林-3rd.pdf](../wangguilin/-3- 这可能是你见过的最NB的C++课程/C++基础与提高-王桂林-3rd.pdf)

[1RecommendedBooks](../../1RecommendedBooks)

[EffectiveC++第3版中文版.pdf](../../1RecommendedBooks/Effective C++/EffectiveC++第3版中文版.pdf)

[C++ Primer（第5版）_带书签_高清完整版.pdf](../../1RecommendedBooks/C++Primer 第5版/C++ Primer（第5版）_带书签_高清完整版.pdf)

[Microsoft C/C++ 文档 | Microsoft Learn](https://learn.microsoft.com/zh-cn/cpp/?view=msvc-170)



# STL

stl容器存在的效率问题：

​	1.push要完成一次对象的拷贝

​	2.内存不足的时候，自动开辟新空间，对原来的数据做一次深拷贝。

解决：

emplace

移动构造，移动赋值

## 容器
### 序列式容器(Sequence Containers)

#### vector

 底层是数组，超过容量后会成倍增长，resize会调用构造函数，随机访问迭代器，取元素比较高效，在尾部插入元素比较高效，中间插入比较低效(会有元素的搬移)

#### deque

一个管理器和多个缓冲区，支持随机访问，首尾增删比较高效。

#### list
底层是双向链表，双向迭代器，不支持随机访问，插入删除元素比较高效。

### 容器适配器(Adapter)

#### stack

容器适配器，底层结构可以选用vector,deque, list 

#### queue
容器适配器，底层结构可以选用deque, list. vector没有pop_back

#### priority_queue: 底层可以使vector, 算法为二叉堆

### 关联式容器(Associative Containers)

#### set
红黑树, 自定义类型需要重载operator<()

#### map
rb operator[]需要有默认的构造函数, 查找复杂度O(logn)

####  multimap

#### multiset
rb

### 无序容器(Unordered Containers)
#### unordered_map
hash表, 自定义类型需要重载operator==()，并提供hash-func

#### unordered_set
hash表

#### unordered_multimap
hash表

#### unordered_multiset
hash表



## 迭代器

迭代器失效

## 算法







## references:

[-4- 用好STL才是王道](../wangguilin/-4- 用好STL才是王道/)

[STL-王桂林-3nd.pdf](../wangguilin/-4- 用好STL才是王道/STL-王桂林-3nd.pdf)

[C++-STL使用例子大全.pdf](../wangguilin/-4- 用好STL才是王道/C++-STL使用例子大全.pdf)



# C++11
## &ensp;1. KeyWord

### &ensp;&ensp;1.1 auto

auto.cpp

使用场景：

1. 迭代器类型
2. lambda类型
3. std::bind返回值类型(functional)

### &ensp;&ensp;1.2 decltype

decltype.cpp

### &ensp;&ensp;1.3 nullptr

nullptr.cpp

解决NULL和0的二义性，NULL通常被定义为(void*)0

### &ensp;&ensp;1.4 final

两个用途: final.cpp

​	1.阻止从类继承。

​	2.组织虚函数的覆写。

### &ensp;&ensp;1.5 override

帮助检查是否正确覆写了父类的虚函数。若此种覆写关系不成立，则以报错的形式提示给coder。

### &ensp;&ensp;1.7 =default/=delete

在函数声明后面加上=delete就能禁用该函数。`A()=delete;`

### &ensp;&ensp;1.8 initializer_list

可以接受多个参数，但必须是同一类型

```c++
double sum(const initializer_list<double> &il);	// 可以接受多个同一类型的参数，函数内再用for(auto d: il);遍历
```

### &ensp;&ensp;1.9 lambda

```c++
[captures](params) specifiers exception -> ret { body }
```

1.捕获列表捕获的是自动存储变量(局部变量)

2.对于全局变量和静态局部变量，放在捕获列表中编译会报错；直接用就行了(作用域本来就是全局的), 也不必在参数列表传参。

3.捕获this指针，可以在lambda内部使用this类型的成员函数和变量。

### &ensp;&ensp;1.10 closure

lambda表达式和其外部的局部变量合起来叫做闭包。

==好处：1.可以读取外层函数内的局部变量；2.让这些变量的值始终保存在内存中。==

### &ensp;&ensp;1.11 assert/static_assert

assert(expression)	//运行期断言，不能在编译器发现错误。

static_assert(expression，提示字符串)	//编译期断言，也叫动态断言。如果expression为false,则打印提示字符串。





## &ensp;2. 左值右值

### &ensp;&ensp;2.1 判断左值右值

左值：可以取地址(&)的一定是左值。字符串字面量(“abcd”)是左值(存在静态数据区，是一块连续的内存，可以取地址)；++i

右值：不能取地址的是右值。字面量(10)一般是右值； 返回的局部对象；i++; 算数/逻辑/比较表达式。

```c++
int func(int val) // val是左值
int func(int&& val)	//val还是左值

A func() { A a; return a; }	//如果开启了RVO(return value optimization)优化，好像a就不会复制给临时对象了. g++ -fno-elide-constructors:关闭rvo优化
```

### &ensp;&ensp;2.2 左值引用

​	扩展了对象的作用域

#### &ensp;&ensp;&ensp;2.2.1非常量左值引用

绑定的必须是一个左值，int &aa = a;

#### &ensp;&ensp;&ensp;2.2.2常量左值引用(万能引用)

既能引用左值，又能引用右值

```c++
const T& aa = a;	 	const T& aa = 1;
const auto& aa = a;	 	const auto& aa = 1;
```

缺点：常量性，一旦使用了常量左值引用就不能修改对象中的数据了(除非强制类型转换)。

### &ensp;&ensp;2.3 右值引用

​	右值引用的特点:

​			1.是延长临时对象的生命周期

​			2.减少对象copy,提升程序性能。

​	c++编译器 编译器将已命名的右值引用视为左值，而将未命名的右值引用视为右值。

#### &ensp;&ensp;&ensp;2.3.1 移动语义

​	将左值转换为右值引用:   ==`std::move(t)`== *≈* ==`static_cast<T&&>(t)`==,  std::move调用时不需要指定模板参数

#### &ensp;&ensp;&ensp;2.3.2 万能引用

```c++
T& aa = a;	 	T& aa = 1;
auto& aa = a;	auto& aa = 1;
```

```c++
// 如果参数传的是左值，则T推导的是左值
// 如果参数传的是右值，则T推导的是类型本身
// 如果参数传的是左值引用，则T推导的是左值引用
// 如果参数传的是右值引用，则T推导的是类型本身
template<typename T>
void func(T&& obj)
{}
```



#### &ensp;&ensp;&ensp;&ensp;2.3.2.1引用折叠

​	遇左则左

#### &ensp;&ensp;&ensp;2.3.3 完美转发

​	保持值的原有属性(左值右值)：std::forward<T>调用时需要指定模板参数

​	 ==`std::forward<T>(t)`== *≈* ==`static_cast<T &&>(t)`==



## &ensp;3.bind/function

`using namespace std::placeholders;`

### &ensp;&ensp;3.1bind

1.   bind绑定顺序就是函数形参的顺序，placeholders::_x中的序列是实参的顺序。

```c++
auto fn_invert = std::bind (myDivide, _2, _1);	// _2/_1 ==> 2/10 
cout << fn_invert(10,2) << endl;	// _1是10，_2是2
```

2. 对于预先绑定好的参数，是传值的，对象会引发拷贝。
2. 对于未预先绑定好的参数，使用placeholders::_x做占位符, 是传引用的。
2. std::bind(&A::func, std::ref(shared_ptr))：  std::ref传的是引用。
2. ==对于绑定的指针，引用类型的参数，需要在调用时确保其是可用的。== 这就引出了下面的`enable_shared_from_this`



## &ensp;4.Smart Pointer

RAII:资源获取即初始化。==资源==：内存、文件句柄、网络连接、互斥量。

### &ensp;&ensp;4.1auto_ptr
(被废弃的) 复制和复制都会改变所有权
### &ensp;&ensp;4.2unique_ptr
1.不能拷贝构造和赋值，但是可以使用std::move转移所有权。

2.可以用于托管数组(**重载了`std::unique_ptr::operator[]`**)

```c++
unique_ptr<int[]> up(new int[10]{1,2,3,4});
```

​	release：放弃托管，返回资源指针。

​	reset: 如果传参了，释放旧资源托管新资源；如果没传参，释放旧资源。

 3.unique_ptr 在默认情况下和裸指针的大小是一样的。所以**内存上没有任何的额外消耗，性能是最优的。**



### &ensp;&ensp;4.3share_ptr
引用计数为0释放资源。

没有所谓的share_ptr<T[]>,以array vector string替代，但是unique_ptr有unique_ptr<T[]>

#### &ensp;&ensp;&ensp;4.3.1reset

​	有参数：如果引用计数>1，引用计数减一，托管新对象。

​				   如果引用计数==1，引用计数减一，释放旧资源，托管新资源。

​	无参数：引用计数减一==同时放弃托管==，如果减到0了，就释放资源。

#### &ensp;&ensp;&ensp;4.3.2make_shared

https://developer.aliyun.com/article/321323

​	优点： 1.使用make_shared<>减少一次内存分配，它会申请一个内存块同时存放托管的资源和引用计数，不用分别分配一次内存。

​				2.解决分开分配内存，而shared_ptr没及时获得裸指针，就抛出异常导致的内存泄漏问题。

​	缺点:	1.如果构造函数不是public的，则编译报错。

​				2.要等弱引用计数 == 0才能把资源全部释放。而对于分开分配内存的方式，强引用计数为0就把托管的资源释放，弱引用计数为0再把引用计数的内存释放。(?? 源码中没看到，等待验证。)



#### &ensp;&ensp;&ensp;4.3.3enable_shared_from_this

```c++
class A : public enable_shared_from_this<A> {}
```

1.为什么要使用enable_shared_from_this

​	1).解决绑定this指针失效的问题(std::bind(&A::func, this))：使用std::bind(&A::func, shared_from_this()).

​	2).重析构的问题：在类内使用this指针构造shared_ptr对象，引用计数不是共享的，会造成重析构。

2.使用enable_shared_from_this需要注意的地方

- 不能在构造/析构函数中调用shared_from_this, 构造时对象还没初始化完，析构时对象已经消失了。

- 要使用shared_from_this()必须先构造一个shared_ptr对象。

    ```c++
    // enable_shared_from_this中有个weak_ptr成员变量weak_this, shared_from_this()函数就是通过weak_ptr来生成shared_ptr;
    // (weak_ptr中保存着引用计数，这样生成的shared_ptr就能共用引用计数了，不会再出现重析构的问题)
    // 而weak_this则是在shared_ptr的构造函数中被赋值的，
    // 所以要使用shared_from_this()必须先构造一个shared_ptr对象。
    // 这也是为什么不能在构造函数中使用shared_from_this()的原因。
    ```

- 使用shared_from_this对象的生命周期被意外的延长了。解决办法：使用weak_ptr作为函数参数。std::bind(&A::func, std::weak_ptr<A>(shared_from_this())  ) .

std::bind(&A::func, shared_from_this()), std::bind(&A::func, shared(this)): 传的是值，会在std::function中copy一份

std::bind(&A::func, _1),  std::bind(&A::func, std::ref(shared_ptr)):传的是引用。



#### &ensp;&ensp;&ensp;4.3.4shared_ptr的线程安全性

​	shared_ptr有两个数据成员，一个是指向托管的资源的指针，一个是指向引用计数的指针，引用计数本身是安全且无锁的(原子的->atomic)。但是shared_ptr对象(前面两个两个加起来)就不是线程安全的了，多个线程可以同时读不能同时写。



#### &ensp;&ensp;&ensp;4.3.5share_ptr的错误用法

​	1.使用栈上的地址来构造shared_ptr, 造成重析构。

​	2.使用一个指针构造两个及以上的shared_ptr, 造成多个shared_ptr对象托管同一个指针，重析构。

​	3.类内使用this指针构造shared_ptr, 重析构。



#### &ensp;&ensp;&ensp;4.3.6refcount.ptr

​	为什么refcount也有指向资源的指针？

​	实际上 shared_ptr.ptr 和 ref_count.ptr 可以是不同的类型（==只要它们之间存在隐式转换==），这是 shared_ptr 的一大功能。分3点来说：

​	1.无需虚析构

​		即使没有虚析构函数也能正确释放子类内存。

​	2.shared_ptr<void>

​		可以指向并安全地管理（析构或防止析构）任何对象。

​		可以把任意shared_ptr对象赋值给shared_ptr<void>，并且不会造成内存泄漏。

​	 3. 多继承

​		多继承情况下，可以把子类的shared_ptr赋值给给任意一个父类的shared_ptr，而不会造成内存泄漏。

以上3点之所以不会发生错误是因为shared_ptr对象析构时delete的是refcount.ptr, refcount.ptr保存的是实际类型的资源的指针。 



### &ensp;&ensp;4.4weak_ptr

两个作用：

- 监视share_ptr, 不会增加引用计数，lock()函数提升为shared_ptr,引用计数加1. 
- 解决share_ptr循环引用造成的内存泄漏问题。



## references

[Modern C++(C++11_14)-王桂林-3nd.pdf](../wangguilin/-12- C++11C++14C++17 视频精讲/Modern C++(C++11_14)-王桂林-3nd.pdf)

[现代c++语言核心特性解析.md](./pdf/c++11/md/现代c++语言核心特性解析.md)



# Algorithm

## 数据结构
### 数组
### 链表
### 栈
### 队列
### 树 
#### 二叉树
#### 二叉搜索树
左子树都比根节点小，右子树都比根节点大。
#### 平衡搜索二叉树
(解决二插搜索树退化成链表的问题)
  1. 左子树都比根节点小，右子树都比根节点大。
  2. 左右子树高度差不超过1

#### AVL-tree:
  平衡因子：导致不平衡的最小子树的根节点

  ```
        5       5               5       5
       /         \             /         \
      3           8           3           8
     /             \           \         /
    1              10           4       7
  1.左旋：以某个节点的右子树为根节点的右子树插入节点导致不平衡     
  2.右旋: 以某个节点的左子树为根节点的左子树插入节点导致不平衡
  3.左右旋: 以某个节点的左子树为根节点的右子树插入节点导致不平衡
  4.右左旋: 以某个节点的右子树为根节点的左子树插入节点导致不平衡
  ```

#### rbtree
    rb-tree特性:
      
      1.每个节点或者是红色，或者是黑色。
      2.根节点是黑色。
      3.叶子结点是黑色。
      4.如果一个节点是红色，那么他的左右孩子为黑色。
      5.从一个节点到该节点的子孙节点的所有路径上包含$\color{red} {相同数目的黑节点}$。

### 二叉堆

### hash

## 算法

### sort

#### bubble sort



### search

#### linear search

#### binary search

### graph theory



## references:

[数据结构与算法(CC++实现)视频教程](../wangguilin/-3.5- 数据结构与算法(CC++实现)视频教程)

[数据结构与算法-王桂林-2nd .pdf](../wangguilin/-3.5- 数据结构与算法(CC++实现)视频教程/数据结构与算法-王桂林-2nd .pdf)



# Design Patterns

## 单例 singleton pattern
### 饿汉式
### 懒汉式
### pthread_once muduo

## 观察者 observer pattern
## 工厂模式 factor pattern
## 装饰模式 decorator pattern

## references:

[设计模式_王桂林_3rd .pdf](../wangguilin/-4.5- 设计模式/设计模式_王桂林_3rd .pdf)



# Linux Basic

[Linux 系统编程-基础篇12_05.pdf](../wangguilin/-5- linux基础课程/Linux 系统编程-基础篇12_05.pdf)

[linux](../ElegantTest/linux)

[command.md](../ElegantTest/linux/command.md)

[gcc_g++.md](../ElegantTest/linux/gcc_g++.md)

[ubuntu换源.md](../ElegantTest/linux/ubuntu换源.md)

# Linux System Programming
## Process
- 进程:最小的资源分配单位
### 进程间通信
#### 信号
#### 管道
(有名管道pipe,管道只能单工通信)

#### 消息队列
#### 信号量(命名信号量)
#### 共享内存 posix mmap
#### socket
#### eventfd

## Thread
- 线程:最小的程序执行单位
### 线程的创建，使用和回收
### 多线程的同步互斥
#### 	atomic

​	(多线程对一个变量进行++操作，使用atomic比使用mutex的效率高), gcc提供的同步函数

#### 	锁:
##### 		互斥锁
###### 			死锁

			1. 
			1. 

1. ​		一把锁，自己锁自己(递归调用)

2. 两把锁，两个线程调用锁的顺序相反， 解决c++11 std::  一起锁，一起释放
   
    pstack lock_wait查看调用栈是否有死锁现象。
##### 递归锁
##### 检错锁
读写锁 读共享，写独占，写锁优先级高(默认是读优先，需要改属性)， boost::shared_mutex内部实现就是读写锁
##### 自旋锁
##### 文件锁
#### 条件变量

(生产者消费者模型)  和mutex一起使用， 内部有加锁，解锁的操作，所以要使用unique_lock, lockguard没有lock(),unlock()成员函数，但是lockguard的开销最少。

#### 信号量(匿名信号量)
二值信号量可以模拟互斥锁 (生产者消费者模型)

### 线程的局部存储 
#### __thread
只能使用POD类型

#### pthread_key_t
非POD类型可以使用
### 线程池 (生产线程，消费线程)

  **条件变量+互斥锁能解决大部分的线程同步问题**



### 内存池



## references:

[linux系统编程.pdf](../wangguilin/-6- linux系统编程与网络编程/linux系统编程.pdf)

[C_C++多线程编程精髓.md](./fanli/C_C++多线程编程精髓.md)



# Linux Network Programming

  ### 如何判断大小端

```c++
  union bl
  {
      int data; // 0x12345678
      char byte;    // 0x78 -->低字节放在低地址：小端
      // uint8_t byte;
  };
```

- 2.



三次握手

四次挥手

滑动窗口

拥塞控制

粘包。



## references:

[linux网络基础.pdf](../wangguilin/-6- linux系统编程与网络编程/linux网络基础.pdf)

# HTTP

- cookie和session：
  cookie保存在客户端，session保存在服务端，当访问量增多session会影响服务器的的性能
  cookie不安全



# Boost

## asio

## reference

[md](../ElegantTest/test_boost/md)

[boost.md](../ElegantTest/test_boost/md/boost.md)

[linux下编译boost.md](../ElegantTest/test_boost/md/linux下编译boost.md)

[windows下编译boost.md](../ElegantTest/test_boost/md/windows下编译boost.md)



# Script Language

## Python

[md](../ElegantTest/test_python/md)

[notes.md](../ElegantTest/test_python/md/notes.md)

[pip.md](../ElegantTest/test_python/md/pip.md)

[编码.md](../ElegantTest/test_python/md/编码.md)



## Shell

[shell编程.pdf](../wangguilin/-5- linux基础课程/shell编程.pdf)

## JavaScript && Typescript

## Lua

# GDB

[test_gdb](../ElegantTest/test_gdb)

[Linux GDB调试指南.md](./fanli/Linux GDB调试指南.md)

[gdb.md](../ElegantTest/test_gdb/gdb.md)

## CGDB

[cgdb.md](../ElegantTest/test_gdb/cgdb.md)

[cgdb-manual-in-chinese](../../4openSourceCode/cgdb-manual-in-chinese)

# Cmake 

[cmake.md](../ElegantTest/test_cmake/md/cmake.md)

[Cmake入门到精通笔记(全).pdf](./pdf/cmake/Cmake入门到精通笔记(全).pdf)

[从零开始详细介绍CMake.pdf](./pdf/cmake/从零开始详细介绍CMake.pdf)

# Makefile

[LinuxMakefile.pdf](../wangguilin/-5- linux基础课程/LinuxMakefile.pdf)

# Git

[git.md](../ElegantTest/git/git.md)

[cherry_pick.md](../ElegantTest/git/cherry_pick.md)

# Muduo

[study.md](../../4openSourceCode/muduo/md/study.md)

[muduo-manual-20120626.pdf](./pdf/muduo-manual/muduo-manual-20120626.pdf)

[《Linux多线程服务端编程：使用muduo C++网络库》.(陈硕).[PDF]@ckook.pdf](../../1RecommendedBooks/Linux多线程服务端编程/《Linux多线程服务端编程：使用muduo C++网络库》.(陈硕).[PDF]@ckook.pdf)

# Redis

[redis.md](../ElegantTest/redis/redis.md)

# Mongodb





# Nginx



# Nodejs



# Protobuf

[test_protobuf](../ElegantTest/test_protobuf)

[protobuf.md](../ElegantTest/test_protobuf/protobuf.md)



# RPC

## grpc

## thrift

## brpc

## srpc

# Libevent

# Zeromq

# Qt

# Others

## &emsp;build environment

​	[buildEnvironment.md](./1buildEnvironment/buildEnvironment.md)

## &emsp;markdown

​	[markdown](./markdown)

​	[MarkDown.md](./markdown/MarkDown.md)

​	[mermaid的[流程图][类图][时序图]的使用范例.md](./markdown/mermaid的[流程图][类图][时序图]的使用范例.md)

​	[typora.md](./markdown/typora.md)

## &emsp;microsoft

​	[microsoft](./microsoft)

​	[win_command.md](./microsoft/win_command.md)

​	[windows快捷键.md](./microsoft/windows快捷键.md)

​	[wsl.md](./microsoft/wsl.md)

​	[下载vscode历史版本.md](./microsoft/下载vscode历史版本.md)

​	[vscode_shortcutKey.md](./microsoft/vscode_shortcutKey.md)

## &emsp;science surfing internet

​	[science surfing internet](./science surfing internet)

​	[science_surfing_internet.md](./science surfing internet/science_surfing_internet.md)

