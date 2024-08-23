###  #!/usr/bin/python

关于脚本第一行的 **#!/usr/bin/python** 的解释，相信很多不熟悉 Linux 系统的同学需要普及这个知识，脚本语言的第一行，只对 Linux/Unix 用户适用，用来指定本脚本用什么解释器来执行。

有这句的，加上执行权限后，可以直接用 **./** 执行，不然会出错，因为找不到 python 解释器。

\#!/usr/bin/python 是告诉操作系统执行这个脚本的时候，调用 /usr/bin 下的 python 解释器。

\#!/usr/bin/env python 这种用法是为了防止操作系统用户没有将 python 装在默认的 /usr/bin 路径里。当系统看到这一行的时候，首先会到 env 设置里查找 python 的安装路径，再调用对应路径下的解释器程序完成操作。

**#!/usr/bin/python** 相当于写死了 python 路径。

**#!/usr/bin/env python** 会去环境设置寻找 python 目录，可以增强代码的可移植性，推荐这种写法。

分成两种情况：

（1）如果调用 python 脚本时，使用:

```
python script.py 
```

#!/usr/bin/python 被忽略，等同于注释

（2）如果调用python脚本时，使用:

```
./script.py 
```

\#!/usr/bin/python 指定解释器的路径

PS：shell 脚本中在第一行也有类似的声明。

### python中文编码

Python中默认的编码格式是 ASCII 格式，在没修改编码格式时无法正确打印汉字，所以在读取中文时会报错。

解决方法为只要在文件开头加入 **# -\*- coding: UTF-8 -\*-** 或者 **# coding=utf-8** 就行了。

当然你也可以为源码文件指定不同的编码：

```
# -*- coding: cp-1252 -*-
```

上述定义允许在源文件中使用 Windows-1252 字符集中的字符编码，对应适合语言为保加利亚语、白罗斯语、马其顿语、俄语、塞尔维亚语。

**注意:** #coding=utf-8 的 **=** 号两边不要空格。

**注意：**Python3.X 源码文件默认使用utf-8编码，所以可以正常解析中文，无需指定 UTF-8 编码。

**注意：**如果你使用编辑器，同时需要设置 py 文件存储的格式为 UTF-8，否则会出现类似以下错误信息：

```
SyntaxError: (unicode error) ‘utf-8’ codec can’t decode byte 0xc4 in position 0:
invalid continuation byte
```

### python数据类型

#### Numbers

- 长整型也可以使用小写 l，但是还是建议您使用大写 L，避免与数字 1 混淆。Python使用 L 来显示长整型。
- Python 还支持复数，复数由实数部分和虚数部分构成，可以用 a + bj,或者 complex(a,b) 表示， 复数的实部 a 和虚部 b 都是浮点型。

> **注意：**long 类型只存在于 Python2.X 版本中，在 2.2 以后的版本中，int 类型数据溢出后会自动转为long类型。在 Python3.X 版本中 long 类型被移除，使用 int 替代。

#### String

加号（+）是字符串连接运算符，星号（*）是重复操作。

1. python的字串列表有2种取值顺序:

- 从左到右索引默认0开始的，最大范围是字符串长度少1
- 从右到左索引默认-1开始的，最大范围是字符串开头

```
-6 -5  -4  -3  -2  -1
 0	1	2	3	4	5
 a	b	c	d	e	f	
```

2. 截取子串

   - **[头下标:尾下标]** 来截取相应的字符串，其中下标是从 0 开始算起，可以是正数或负数，$\color{red} {下标可以为空表示取到头或尾。}$

   - **[头下标:尾下标]** 获取的子字符串包含头下标的字符，但不包含尾下标的字符。

3. Python 列表截取可以接收第三个参数，$\color{red} {参数作用是截取的步长}$，以下实例在索引 1 到索引 4 的位置并设置为步长为 2（间隔一个位置）来截取字符串：

![img](image/python_list_slice_2.png)

4. Python中的字符串不能改变。

   **word[0] = 'm'** 会导致错误。
   
5. 如果第三个参数为负数表示逆向读取，可以用于翻转

   ```
   #翻转列表
   l = ["abc", 10, 20.5]
   print(l[-1::-1])    #[20.5, 10, "abc"]
   #翻转字符串
   str = "abcdefg"
   print(str[-1::-1])  #gfedcba
   #翻转元组
   tuple = ["ab", 100, 10.5]
   print(tuple[-1::-1]) #[10.5, 100, "ab"]
   ```

##### f-string

   f-string 是 python3.6 之后版本添加的，称之为字面量格式化字符串，是新的格式化字符串的语法。

   之前我们习惯用百分号 (%):

   **实例:**

```
>>> name = 'Runoob'
>>> 'Hello %s' % name
'Hello Runoob'
```

**f-string** 格式化字符串以 **f** 开头，后面跟着字符串，字符串中的表达式用大括号 {} 包起来，它会将变量或表达式计算后的值替换进去，实例如下：

**实例**

```
>>> name = 'Runoob'
>>> f'Hello {name}' # 替换变量
'Hello Runoob'
>>> f'{1+2}'     # 使用表达式
'3'

>>> w = {'name': 'Runoob', 'url': 'www.runoob.com'}
>>> f'{w["name"]}: {w["url"]}'
'Runoob: www.runoob.com'
```

用了这种方式明显更简单了，不用再去判断使用 %s，还是 %d。

在 Python 3.8 的版本中可以使用 **=** 符号来拼接运算表达式与结果：

**实例**

```
>>> x = 1
>>> print(f'{x+1}')  # Python 3.6
2

>>> x = 1
>>> print(f'{x+1=}')  # Python 3.8
x+1=2
```









#### List

列表可以完成大多数集合类的数据结构实现。它支持字符，数字，字符串甚至可以包含列表（即嵌套）。

列表用 **[ ]** 标识，是 python 最通用的复合数据类型。

列表中值的切割也可以用到变量 **[头下标:尾下标]** ，就可以截取相应的列表，从左到右索引默认 0 开始，从右到左索引默认 -1 开始，下标可以为空表示取到头或尾。

![img](image/list_slicing1_new1.png)

加号 **+** 是列表连接运算符，星号 ***** 是重复操作。

#### Tuple

- 元组是另一个数据类型，类似于 List（列表）。

- 元组用 **()** 标识。内部元素用逗号隔开。$\color{red} {但是元组不能二次赋值，相当于只读列表。}$元组不允许更新，而列表是允许更新的。$\color{red} {其实，可以把字符串看作一种特殊的元组。}$

  ```
  >>> tup1 = ("all")
  >>> print tup1
  all
  ```
  
  输出字符串 all，这是因为括号()既可以表示tuple，又可以表示数学公式中的小括号。
  
  所以，如果元组只有1个元素，就必须加一个逗号，防止被当作括号运算：
  
  ```
  >>> tup1 = ("all",)
  >>> print tup1
  ('all',)
  >>> 
  ```
  
  

#### Set

集合（set）是由一个或数个形态各异的大小整体组成的，构成集合的事物或对象称作元素或是成员。

基本功能是进行成员关系测试和删除重复元素。

可以使用大括号 **{ }** 或者 **set()** 函数创建集合。$\color{red} {注意：}$创建一个空集合必须用 **set()** 而不是 **{ }**，因为 **{ }** 是用来创建一个空字典。

创建格式：

```
parame = {value01,value02,...}
或者
set(value)
```

```
#!/usr/bin/python3

sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Baidu', 'Zhihu', 'Baidu'}
print(sites)    #{'Taobao', 'Runoob', 'Zhihu', 'Facebook', 'Baidu', 'Google'}

if 'Runoob' in sites :
    print('Runoob in sites')
else :
    print('Runoob not in sites')

#类似于std::unordered_set 元素不重复且无序
print(set())    #set()
a = set('abracadabra')
b = set('alacazam')
print(a)    # a b r c d     #{'c', 'd', 'b', 'r', 'a'}
print(b)    # a l c z m     #{'c', 'm', 'l', 'z', 'a'}

print(a - b)    # a相对于b的差集 b r d  #{'b', 'r', 'd'}
print(b - a)    # b相对于a的差集 l z m  #{'m', 'l', 'z'}
print(a | b)    # a与b的并集 a b c d l r z m  #{'z', 'c', 'd', 'b', 'l', 'r', 'm', 'a'}
print(a & b)    # a与b的交集 a c    #{'c', 'a'}
print(a ^ b)    # a与b中不同时存在的元素 b d l r z m    #{'d', 'm', 'l', 'r', 'b', 'z'}
```

**s.update( "字符串" ) 与 s.update( {"字符串"} ) 含义不同:**

-  **s.update( {"字符串"} )** 将字符串添加到集合中，有重复的会忽略。

-  **s.update( "字符串" )** 将字符串拆分单个字符后，然后再一个个添加到集合中，有重复的会忽略。

**创建一个元素**

```
d = set(('apple',))
d = set({'apple'})
d = set({'apple',})
```

如无必要，不要写成如下形式

```
>>> my_set = set('apple')
>>> my_set
{'l', 'e', 'p', 'a'}
>>> my_set1 = set(('apple'))
>>> my_set1
{'l', 'e', 'p', 'a'}
```

#### Dictionary

字典(dictionary)是除列表以外python之中最灵活的内置数据结构类型。$\color{red} {列表是有序的对象集合，字典是无序的对象集合。}$

**两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。**

字典用"{ }"标识。字典由索引(key)和它对应的值value组成。

键(key)必须使用不可变类型。

在同一个字典中，键(key)必须是唯一的。

###### 字典键的特性

字典值可以是任何的 python 对象，既可以是标准的对象，也可以是用户定义的，但键不行。

两个重要的点需要记住：

1）不允许同一个键出现两次。创建时如果同一个键被赋值两次，后一个值会被记住，如下实例：

**实例**

```
#!/usr/bin/python3  
tinydict = {'Name': 'Runoob', 'Age': 7, 'Name': '小菜鸟'}  
print ("tinydict['Name']: ", tinydict['Name'])
```

以上实例输出结果：

```
tinydict['Name']:  小菜鸟
```

2）$\color{red} {键必须不可变}$，所以可以用数字，字符串或元组充当，而用列表就不行，如下实例：

**实例**

```
#!/usr/bin/python3  
tinydict = {['Name']: 'Runoob', 'Age': 7}  
print ("tinydict['Name']: ", tinydict['Name'])
```

以上实例输出结果：

```
Traceback (most recent call last):
  File "test.py", line 3, in <module>
    tinydict = {['Name']: 'Runoob', 'Age': 7}
TypeError: unhashable type: 'list'
```

#### type()和isinstance()

type() 函数可以用来查询变量所指的对象类型。

isinstance 和 type 的区别在于：

- type()不会认为子类是一种父类类型。
- isinstance()会认为子类是一种父类类型。

### python运算符

#### 算数运算符

1. 除法 /

2. 取整除（向下取接近商的整数） // 

   ```
   python2
   ##python2里整数除整数只能得到整数
   print(9 / 2)    # 4
   print(9 // 2)   # 4
   print(9.0 / 2)  # 4.5
   print(9.0 // 2) # 4.0
   print(-9 / 2)    # -5 (向下取整)
   print(-9 // 2)   # -5 (向下取整)
   print(-9.0 / 2)  # -4.5
   print(-9.0 // 2) # -5.0(向下取整)
   print(float(9) / 2)    # 4.5
   print(float(9) // 2)   # 4.0
   print(float(-9) / 2)    # -4.5
   print(float(-9) // 2)   # -5.0   
   ```

**注意：**Python2.x 里，整数除整数，只能得出整数。如果要得到小数部分，把其中一个数改成浮点数即可。

```
>>> 1/2
0
>>> 1.0/2
0.5
>>> 1/float(2)
0.5
```



#### 成员运算符

   Python还支持成员运算符，测试实例中包含了一系列的成员，包括字符串，列表或元组。

| 运算符 | 描述                                                    | 实例                                              |
| :----- | :------------------------------------------------------ | :------------------------------------------------ |
| in     | 如果在指定的序列中找到值返回 True，否则返回 False。     | x 在 y 序列中 , 如果 x 在 y 序列中返回 True。     |
| not in | 如果在指定的序列中没有找到值返回 True，否则返回 False。 | x 不在 y 序列中 , 如果 x 不在 y 序列中返回 True。 |

#### 身份运算符

身份运算符用于比较两个对象的存储单元。**比较两个对象的地址**

| 运算符 | 描述                                        | 实例                                                         |
| :----- | :------------------------------------------ | :----------------------------------------------------------- |
| is     | is 是判断两个标识符是不是引用自一个对象     | **x is y**, 类似 **id(x) == id(y)** , 如果引用的是同一个对象则返回 True，否则返回 False |
| is not | is not 是判断两个标识符是不是引用自不同对象 | **x is not y** ， 类似 **id(a) != id(b)**。如果引用的不是同一个对象则返回结果 True，否则返回 False。 |

```
python2和python3结果相同:

>>> a=256
>>> b=256
>>> print(a is b)
True
>>> a=257
>>> b=257
>>> print(a is b)
False
>>> a=1.0
>>> b=1.0
>>> print(a is b)
False
```

- Python出于对性能的考虑，但凡是$\color{red} {不可变对象}$，在同一个代码块中的对象，只有是值相同的对象，就不会重复创建，而是直接引用已经存在的对象。

  ```
  c = 10000000000000000000000000000000000000000
  d = 10000000000000000000000000000000000000000
  print("1.", c is d, id(c), id(d))    #True
  print("1.", c is not d, id(c), id(d))  #False
  
  e = 2000000000000000000000000000000000000000.0
  f = 2000000000000000000000000000000000000000.0 
  print("1.", e is f, id(e), id(f))       #True
  print("1.", e is not f, id(e), id(f))   #False
  
  e = -2000000000000000000000000000000000000000.0
  f = -2000000000000000000000000000000000000000.0 
  print("2.", e is f, id(e), id(f))       #True
  print("2.", e is not f, id(e), id(f))   #False
  
  ```

- Python 中会实现创建一个小型的$\color{red} {整型池}$，范围为 [-5,256]，为这些整形开辟好内存空间，当代码中定义该范围内的整形时，不会再重新分配内存地址。

  ```
  # 正整数最大到256
  c = 2 ** 8
  d = 2 ** 8
  print("2.", c is d, id(c), id(d))       #True
  print("2.", c is not d, id(c), id(d))   #False
  
  c = 2 ** 8 + 1
  d = 2 ** 8 + 1
  print("7.", c is d, id(c), id(d))       #False
  print("7.", c is not d, id(c), id(d))   #True
  
  # 负整数最小到-5
  e = -2 ** 2
  f = -2 ** 2
  print("1.", e is f, id(e), id(f))       #True
  
  e=-2 ** 2 -1
  f=-2 ** 2 -1
  print("2.", e is f, id(e), id(f))       #True
  
  e=-2 ** 2 -2
  f=-2 ** 2 -2
  print("3.", e is f, id(e), id(f))       #False
  ```

  

#### python运算符优先级

以下表格列出了从最高到最低优先级的所有运算符， 相同单元格内的运算符具有相同优先级。 运算符均指二元运算，除非特别指出。 相同单元格内的运算符从左至右分组（除了幂运算是从右至左分组）：

| 运算符                                                       | 描述                               |
| :----------------------------------------------------------- | :--------------------------------- |
| `(expressions...)`,`[expressions...]`, `{key: value...}`, `{expressions...}` | 圆括号的表达式                     |
| `x[index]`, `x[index:index]`, `x(arguments...)`, `x.attribute` | 读取，切片，调用，属性引用         |
| await x                                                      | await 表达式                       |
| `**`                                                         | 乘方(指数)                         |
| `+x`, `-x`, `~x`                                             | 正，负，按位非 NOT                 |
| `*`, `@`, `/`, `//`, `%`                                     | 乘，矩阵乘，除，整除，取余         |
| `+`, `-`                                                     | 加和减                             |
| `<<`, `>>`                                                   | 移位                               |
| `&`                                                          | 按位与 AND                         |
| `^`                                                          | 按位异或 XOR                       |
| `|`                                                          | 按位或 OR                          |
| `in,not in, is,is not, <, <=, >, >=, !=, ==`                 | 比较运算，包括成员检测和标识号检测 |
| `not x`                                                      | 逻辑非 NOT                         |
| `and`                                                        | 逻辑与 AND                         |
| `or`                                                         | 逻辑或 OR                          |
| `if -- else`                                                 | 条件表达式                         |
| `lambda`                                                     | lambda 表达式                      |
| `:=`                                                         | 赋值表达式                         |

**注意：**Python3 已不支持 **<>** 运算符，可以使用 **!=** 代替，如果你一定要使用这种比较运算符，可以使用以下的方式：

```
>>> from __future__ import barry_as_FLUFL
>>> 1 <> 2
True
```

### python语句

#### 循环使用else语句

在 python 中，for … else 表示这样的意思，for 中的语句和普通的没有区别，else 中的语句会在循环正常执行完（$\color{red} {即 for 不是通过 break 跳出而中断的}$）的情况下执行，while … else 也是一样。

### python推导式

#### 列表推导式

#### 集合推导式

#### 字典推导式

#### 元组推导式

元组推导式可以利用 range 区间、元组、列表、字典和集合等数据类型，快速生成一个满足指定需求的元组。

元组推导式基本格式：

```
(expression for item in Sequence )
或
(expression for item in Sequence if conditional )
```

元组推导式和列表推导式的用法也完全相同，只是元组推导式是用 **()** 圆括号将各部分括起来，而列表推导式用的是中括号 **[]**，$\color{red} {另外元组推导式返回的结果是一个生成器对象。}$

例如，我们可以使用下面的代码生成一个包含数字 1~9 的元组：

**实例**

```
>>> a = (x **for** x **in** range(1,10))
>>> a
<generator object <genexpr> at 0x7faf6ee20a50> # 返回的是生成器对象

>>> tuple(a)    # 使用 tuple() 函数，可以直接将生成器对象转换成元组
(1, 2, 3, 4, 5, 6, 7, 8, 9)
```



### python模块

- 1、import sys 引入 python 标准库中的 sys.py 模块；这是引入某一模块的方法。

- 2、sys.argv 是一个包含命令行参数的列表。

  ```
  >>>python3 module.py 1 1.0 "ab" [1,2,3] {}
  module.py
  1
  1.0
  ab
  [1,2,3]
  {}
  
  >>>./module.py 1 1.0 "ab" [1,2,3] {}
  ./module.py
  1
  1.0
  ab
  [1,2,3]
  {}
  ```

- 3、sys.path 包含了一个 Python 解释器自动查找所需模块的路径的列表。

一个模块只会被导入一次，不管你执行了多少次 **import**。这样可以防止导入模块被一遍又一遍地执行。

当我们使用 import 语句的时候，Python 解释器是怎样找到对应的文件的呢？

$\color{red} {这就涉及到 Python 的搜索路径，搜索路径是由一系列目录名组成的，Python 解释器就依次从这些目录中去寻找所引入的模块。}$

这看起来很像环境变量，事实上，也可以通过定义环境变量的方式来确定搜索路径。

搜索路径是在 Python 编译或安装的时候确定的，安装新的库应该也会修改。搜索路径被存储在 sys 模块中的 path 变量，做一个简单的实验，在交互式解释器中，输入以下代码：

```
>>> import sys
>>> sys.path
['', '/usr/lib/python3.4', '/usr/lib/python3.4/plat-x86_64-linux-gnu', '/usr/lib/python3.4/lib-dynload', '/usr/local/lib/python3.4/dist-packages', '/usr/lib/python3/dist-packages']
>>> 
```

$\color{red} {sys.path 输出是一个列表，其中第一项是空串''，代表当前目录}$   (若是从一个脚本中打印出来的话，可以更清楚地看出是哪个目录），亦即我们执行python解释器的目录（对于脚本的话就是运行的脚本所在的目录）。

#### import 与 from...import

在 python 用 **import** 或者 **from...import** 来导入相应的模块。

将整个模块(somemodule)导入，格式为： **import somemodule**

从某个模块中导入某个函数,格式为： **from somemodule import somefunction**

从某个模块中导入多个函数,格式为： **from somemodule import firstfunc, secondfunc, thirdfunc**

将某个模块中的全部函数导入，格式为： **from somemodule import \***

<u>**from module import ***</u> 

可以一次性的把模块中的所有==（函数，变量）==名称都导入到当前模块的字符表

这将把所有的名字都导入进来，$\color{red} {但是那些由单一下划线（_）开头的名字不在此例。}$大多数情况， Python程序员不使用这种方法，因为引入的其它来源的命名，很可能覆盖了已有的定义。

#### __ __name__ __属性

$\color{red} {一个模块被另一个程序第一次引入时，其主程序将运行。}$如果我们想在模块被引入时，模块中的某一程序块不执行，我们可以用__ name __ 属性来使该程序块仅在该模块自身运行时执行。

```
#!/usr/bin/python3
# Filename: using_name.py

if __name__ == '__main__':
   print('程序自身在运行')
else:
   print('我来自另一模块')
```

运行输出如下：

```
$ python using_name.py
程序自身在运行
$ python
>>> import using_name
我来自另一模块
>>>
```

**说明：** 每个模块都有一个__name__属性，当其值是'__main__'时，表明该模块自身在运行，否则是被引入。

说明：**__name__** 与 **__main__** 底下是双下划线， **_ _** 是这样去掉中间的那个空格。

#### dir函数

内置的函数 dir() 可以找到模块内定义的所有名称。以一个字符串列表的形式返回。

```
>>>import sys
>>>dir(sys)
```

如果没有给定参数，那么 dir() 函数会罗列出当前定义的所有名称。

#### 包

包是一个分层次的文件目录结构，它定义了一个由模块及子包，和子包下的子包等组成的 Python 的应用环境。

**简单来说，包就是文件夹，但该文件夹下必须存在 __ __init.py__ __ 文件, 该文件的内容可以为空。__ __init.py__ __ 用于标识当前文件夹是一个包。**

包是一种管理 Python 模块命名空间的形式，采用"点模块名称"。

比如一个模块的名称是 A.B， 那么他表示一个包 A中的子模块 B 。

就好像使用模块的时候，你不用担心不同模块之间的全局变量相互影响一样，采用点模块名称这种形式也不用担心不同库之间的模块重名的情况。

这里给出了一种可能的包结构（在分层的文件系统中）:

```
sound/                          顶层包
      __init__.py               初始化 sound 包
      formats/                  文件格式转换子包
              __init__.py
              wavread.py
              wavwrite.py
              aiffread.py
              aiffwrite.py
              auread.py
              auwrite.py
              ...
      effects/                  声音效果子包
              __init__.py
              echo.py
              surround.py
              reverse.py
              ...
      filters/                  filters 子包
              __init__.py
              equalizer.py
              vocoder.py
              karaoke.py
              ...
```

在导入一个包的时候，Python 会根据 sys.path 中的目录来寻找这个包中包含的子目录。

目录只有包含一个叫做 `__init__.py` 的文件$\color{red} {才会被认作是一个包}$，主要是为了避免一些滥俗的名字（比如叫做 string）不小心的影响搜索路径中的有效模块。

**最简单的情况，放一个空的 `:file:__init__.py`就可以了。**当然这个文件中也可以包含一些初始化代码或者为（将在后面介绍的） `__all__`变量赋值。

用户可以每次只导入一个包里面的特定模块，比如:

```
import sound.effects.echo
```

这将会导入子模块:sound.effects.echo。 他必须使用全名去访问:

```
sound.effects.echo.echofilter(input, output, delay=0.7, atten=4)
```

还有一种导入子模块的方法是:

```
from sound.effects import echo
```

这同样会导入子模块: echo，并且他不需要那些冗长的前缀，所以他可以这样使用:

```
echo.echofilter(input, output, delay=0.7, atten=4)
```

还有一种变化就是直接导入一个函数或者变量:

```
from sound.effects.echo import echofilter
```

同样的，这种方法会导入子模块: echo，并且可以直接使用他的 echofilter() 函数:

```
echofilter(input, output, delay=0.7, atten=4)
```

注意当使用 **from package import item** 这种形式的时候，$\color{red} {对应的 item 既可以是包里面的子模块（子包），或者包里面定义的其他名称，比如函数，类或者变量。}$

import 语法会首先把 item 当作一个包定义的名称，如果没找到，再试图按照一个模块去导入。如果还没找到，抛出一个 **:exc:ImportError** 异常。

反之，如果使用形如 **import item.subitem.subsubitem** 这种导入形式，*除了最后一项，都必须是包*，<u>而最后一项则可以是模块或者是包</u>，$\color{red} {但是不可以是类，函数或者变量的名字。}$

#### 从一个包中导入*

如果我们使用 **from sound.effects import \*** 会发生什么呢？

Python 会进入文件系统，找到这个包里面所有的子模块，然后一个一个的把它们都导入进来。

但这个方法在 Windows 平台上工作的就不是非常好，因为 Windows 是一个不区分大小写的系统。

在 Windows 平台上，我们无法确定一个叫做 ECHO.py 的文件导入为模块是 echo 还是 Echo，或者是 ECHO。

为了解决这个问题，我们只需要提供一个精确包的索引。

$\color{red} {导入语句遵循如下规则}$：如果包定义文件 **__init__.py** 存在一个叫做 **__all__** 的列表变量，那么在使用 **from package import \*** 的时候就把这个列表中的所有名字作为包内容导入。

作为包的作者，可别忘了在更新包之后保证 **__all__** 也更新了啊。

以下实例在 file:sounds/effects/__init__.py 中包含如下代码:

```
__all__ = ["echo", "surround", "reverse"]
```

这表示当你使用`from sound.effects import *`这种用法时，$\color{red} {你只会导入包里面这三个子模块。}$

如果 `__all__` 真的没有定义，那么使用**from sound.effects import \***这种语法的时候，<u>就不会导入包 sound.effects 里的任何子模块</u>。**他只是把包sound.effects和它里面定义的所有内容导入进来**（可能运行`__init__.py`里定义的初始化代码）。

这会把 __init__.py 里面定义的所有名字导入进来。并且他不会破坏掉我们在这句话之前导入的所有明确指定的模块。看下这部分代码:

```
import sound.effects.echo
import sound.effects.surround
from sound.effects import *
```

这个例子中，在执行 from...import 前，包 sound.effects 中的 echo 和 surround 模块都被导入到当前的命名空间中了。（当然如果定义了` __all__` 就更没问题了）

通常我们并不主张使用 ***** 这种方法来导入模块，因为这种方法经常会导致代码的可读性降低。不过这样倒的确是可以省去不少敲键的功夫，而且一些模块都设计成了只能通过特定的方法导入。

记住，使用 **from Package import specific_submodule** 这种方法永远不会有错。事实上，这也是推荐的方法。除非是你要导入的子模块有可能和其他包的子模块重名。

如果在结构中包是一个子包（比如这个例子中对于包sound来说），而你又想导入兄弟包（同级别的包）你就得使用导入绝对的路径来导入。比如，如果模块sound.filters.vocoder 要使用包 sound.effects 中的模块 echo，你就要写成 **from sound.effects import echo**。

```
from . import echo
from .. import formats
from ..filters import equalizer
```

无论是隐式的还是显式的相对导入都是从当前模块开始的。主模块的名字永远是"`__main__`"，$\color{red} {一个Python应用程序的主模块，应当总是使用绝对路径引用。}$

包还提供一个额外的属性`__path__`。这是一个目录列表，里面每一个包含的目录都有为这个包服务的`__init__`.py，你得在其他`__init__`.py被执行前定义哦。可以修改这个变量，用来影响包含在包里面的模块和子包。这个功能并不常用，一般用来扩展包里面的模块。

#### 例

举个例子，一个`abc.py`的文件就是一个名字叫`abc`的模块，一个`xyz.py`的文件就是一个名字叫`xyz`的模块。

现在，假设我们的`abc`和`xyz`这两个模块名字与其他模块冲突了，于是我们可以通过包来组织模块，避免冲突。方法是选择一个顶层包名，比如`mycompany`，按照如下目录存放：

```ascii
mycompany
├─ __init__.py
├─ abc.py
└─ xyz.py
```

引入了包以后，只要顶层的包名不与别人冲突，那所有模块都不会与别人冲突。现在，`abc.py`模块的名字就变成了`mycompany.abc`，类似的，`xyz.py`的模块名变成了`mycompany.xyz`。

请注意，每一个包目录下面都会有一个`__init__.py`的文件，这个文件是必须存在的，否则，Python就把这个目录当成普通目录，而不是一个包。`__init__.py`可以是空文件，也可以有Python代码，因为`__init__.py`本身就是一个模块，而它的模块名就是`mycompany`。

类似的，可以有多级目录，组成多级层次的包结构。比如如下的目录结构：

```ascii
mycompany
 ├─ web
 │  ├─ __init__.py
 │  ├─ utils.py
 │  └─ www.py
 ├─ __init__.py
 ├─ abc.py
 └─ utils.py
```

文件`www.py`的模块名就是`mycompany.web.www`，两个文件`utils.py`的模块名分别是`mycompany.utils`和`mycompany.web.utils`。

 **自己创建模块时要注意命名，不能和Python自带的模块名称冲突。例如，系统自带了sys模块，自己的模块就不可命名为sys.py，否则将无法导入系统自带的sys模块。**



### python面向对象

```
class Student(object):

    def __init__(self, name, score):
        self.__name = name
        self.__score = score

    def print_score(self):
        print('%s: %s' % (self.__name, self.__score))
```

双下划线开头的实例变量是不是一定不能从外部访问呢？其实也不是。不能直接访问`__name`是因为Python解释器对外把`__name`变量改成了`_Student__name`，所以，仍然可以通过`_Student__name`来访问`__name`变量：

```
>>> bart._Student__name
'Bart Simpson'
```

但是强烈建议你不要这么干，因为不同版本的Python解释器可能会把`__name`改成不同的变量名。

总的来说就是，Python本身没有任何机制阻止你干坏事，一切全靠自觉。

最后注意下面的这种*错误写法*：

```
>>> bart = Student('Bart Simpson', 59)
>>> bart.get_name()
'Bart Simpson'
>>> bart.__name = 'New Name' # 设置__name变量！
>>> bart.__name
'New Name'
```

表面上看，外部代码“成功”地设置了`__name`变量，但实际上这个`__name`变量和class内部的`__name`变量*不是*一个变量！内部的`__name`变量已经被Python解释器自动改成了`_Student__name`，而外部代码给`bart`新增了一个`__name`变量。不信试试：

```
>>> bart.get_name() # get_name()内部返回self.__name
'Bart Simpson'
```



- private属性: __attr
- protect属性: _attr

**Python3 类方法总结**

-  普通方法：对象访问
-  私有方法：两个下划线开头，只能在类内部访问: __func()
-  保护方法：一个下划线开头，只能在类内部访问: _func()
-  静态方法：类和对象访问，不能和其他方法重名，不然会相互覆盖，后面定义的会覆盖前面的
-  类方法：类和对象访问，不能和其他方法重名，不然会相互覆盖，后面定义的会覆盖前面的
-  多继承情况下：从左到右查找方法，找到为止，不然就抛出异常

__ __str__ __函数:

__ __str__ __ 是一个类的方法，在打印类对象，获取其属性信息时调用。打印一个实例化对象时，默认打印的其实时一个对象的地址，但是我们可以对其进行重载，打印我们想要的信息。例如上面的例子中进行的重载。

#### python 对象销毁(垃圾回收)

Python 使用了引用计数这一简单技术来跟踪和回收垃圾。

在 Python 内部记录着所有使用中的对象各有多少引用。

一个内部跟踪变量，称为一个引用计数器。

当对象被创建时， 就创建了一个引用计数， 当这个对象不再需要时， 也就是说， 这个对象的引用计数变为0 时， 它被垃圾回收。但是回收不是"立即"的， 由解释器在适当的时机，将垃圾对象占用的内存空间回收。

```
a = 40      # 创建对象  <40>
b = a       # 增加引用， <40> 的计数
c = [b]     # 增加引用.  <40> 的计数

del a       # 减少引用 <40> 的计数
b = 100     # 减少引用 <40> 的计数
c[0] = -1   # 减少引用 <40> 的计数
```

垃圾回收机制不仅针对引用计数为0的对象，同样也可以处理循环引用的情况。循环引用指的是，两个对象相互引用，但是没有其他变量引用他们。**这种情况下，仅使用引用计数是不够的。**$\color{red} {Python 的垃圾收集器实际上是一个引用计数器和一个循环垃圾收集器。}$作为引用计数的补充， 垃圾收集器也会留心被分配的总量很大（即未通过引用计数销毁的那些）的对象。 <u>在这种情况下， 解释器会暂停下来， 试图清理所有未引用的循环。</u>

析构函数 __ __del__ __ ，__ __del__ __ 在对象销毁的时候被调用，当对象不再被使用时，__ __del__ __方法才被运行

#### 多继承

Python同样有限的支持多继承形式。多继承的类定义形如下例:

```
class DerivedClassName(Base1, Base2, Base3):<statement-1> ...<statement-N>
```

需要注意圆括号中父类的顺序，若是父类中有相同的方法名，而在子类使用时未指定，python从左至右搜索 即方法在子类中未找到时，从左到右查找父类中是否包含方法。

### python命名空间

一般有三种命名空间：

- **内置名称（built-in names**）， Python 语言内置的名称，比如函数名 abs、char 和异常名称 BaseException、Exception 等等。
- **全局名称（global names）**，模块中定义的名称，记录了模块的变量，包括函数、类、其它导入的模块、模块级的变量和常量。
- **局部名称（local names）**，函数中定义的名称，记录了函数的变量，包括函数的参数和局部定义的变量。（类中定义的也是）

![img](image/types_namespace-1.png)

#### 命名空间查找顺序:

假设我们要使用变量 runoob，则 Python 的查找顺序为：**局部的命名空间去 -> 全局命名空间 -> 内置命名空间**。

如果找不到变量 runoob，它将放弃查找并引发一个 NameError 异常:

```
NameError: name 'runoob' is not defined。
```

#### 命名空间的生命周期：

命名空间的生命周期取决于对象的作用域，如果对象执行完成，则该命名空间的生命周期就结束。

因此，我们无法从外部命名空间访问内部命名空间的对象。

**实例**

```
# var1 是全局名称
var1 = 5
def some_func():

	# var2 是局部名称
	var2 = 6
	
	def some_inner_func():
		# var3 是内嵌的局部名称
		var3 = 7
```



### python 作用域

有四种作用域：

- **L（Local）**：最内层，包含局部变量，比如一个函数/方法内部。
- **E（Enclosing）**：包含了非局部(non-local)也非全局(non-global)的变量。比如两个嵌套函数，一个函数（或类） A 里面又包含了一个函数 B ，那么对于 B 中的名称来说 A 中的作用域就为 nonlocal。
- **G（Global）**：当前脚本的最外层，比如当前模块的全局变量。
- **B（Built-in）**： 包含了内建的变量/关键字等，最后被搜索。

规则顺序： **L –> E –> G –> B**。

在局部找不到，便会去局部外的局部找（例如闭包），再找不到就会去全局找，再者去内置中找。

![img](image/1418490-20180906153626089-1835444372.png)

```
g_count = 0  # 全局作用域
def outer():
    o_count = 1  # 闭包函数外的函数中
    def inner():
        i_count = 2  # 局部作用域
```

内置作用域是通过一个名为 builtin 的标准模块来实现的，但是这个变量名自身并没有放入内置作用域内，所以必须导入这个文件才能够使用它。在Python3.0中，可以使用以下的代码来查看到底预定义了哪些变量:

```
>>> import builtins
>>> dir(builtins)
```

**Python 中只有模块（module），类（class）以及函数（def、lambda）才会引入新的作用域，** $\color{red} {其它的代码块（如 if/elif/else/、try/except、for/while等）是不会引入新的作用域的，也就是说这些语句内定义的变量，外部也可以访问，}$如下代码：

```
>>> if True:
...  msg = 'I am from Runoob'
... 
>>> msg
'I am from Runoob'
>>> 
```

实例中 msg 变量定义在 if 语句块中，但外部还是可以访问的。

如果将 msg 定义在函数中，则它就是局部变量，外部不能访问：

```
>>> def test():
...     msg_inner = 'I am from Runoob'
... 
>>> msg_inner
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
NameError: name 'msg_inner' is not defined
>>> 
```

从报错的信息上看，说明了 msg_inner 未定义，无法使用，因为它是局部变量，只有在函数内可以使用。

#### global 和 nonlocal关键字

当内部作用域想修改外部作用域的变量时，就要用到 global 和 nonlocal 关键字了。

以下实例修改全局变量 num：

````
#!/usr/bin/python3
 
num = 1
def fun1():
    global num  # 需要使用 global 关键字声明
    print(num) 
    num = 123
    print(num)
fun1()
print(num)
````

以上实例输出结果：

```
1
123
123
```

如果要修改嵌套作用域（enclosing 作用域，外层非全局作用域）中的变量则需要 nonlocal 关键字了，如下实例：

```
#!/usr/bin/python3
 
def outer():
    num = 10
    def inner():
        nonlocal num   # nonlocal关键字声明
        num = 100
        print(num)
    inner()
    print(num)
outer()
```

以上实例输出结果：

```
100
100
```

另外有一种特殊情况，假设下面这段代码被运行：

```
#!/usr/bin/python3
 
a = 10
def test():
    a = a + 1
    print(a)
test()
```

以上程序执行，报错信息如下：

```
Traceback (most recent call last):
  File "test.py", line 7, in <module>
    test()
  File "test.py", line 5, in test
    a = a + 1
UnboundLocalError: local variable 'a' referenced before assignment
```

错误信息为局部作用域引用错误，因为 test 函数中的 a 使用的是局部，未定义，无法修改。

修改 a 为全局变量：

**实例**

```
#!/usr/bin/python3  
a = 10 
def test():    
	global a    
	a = a + 1    
	print(a) 
test()

执行输出结果为：
11
```



### python 内置模块

#### time模块

python中时间日期格式化符号：

- %y 两位数的年份表示（00-99）
- %Y 四位数的年份表示（000-9999）
- %m 月份（01-12）
- %d 月内中的一天（0-31）
- %H 24小时制小时数（0-23）
- %I 12小时制小时数（01-12）
- %M 分钟数（00-59）
- %S 秒（00-59）
- %a 本地简化星期名称
- %A 本地完整星期名称
- %b 本地简化的月份名称
- %B 本地完整的月份名称
- %c 本地相应的日期表示和时间表示
- %j 年内的一天（001-366）
- %p 本地A.M.或P.M.的等价符
- %U 一年中的星期数（00-53）星期天为星期的开始
- %w 星期（0-6），星期天为星期的开始
- %W 一年中的星期数（00-53）星期一为星期的开始
- %x 本地相应的日期表示
- %X 本地相应的时间表示
- %Z 当前时区的名称
- %% %号本身

#### calendar模块

