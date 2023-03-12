# 启发函数

f(n) = g(n) + h(n)

g(n)：表示起点到结点n的距离。

h(n)：表示结点n到终点的预估距离。

1. 当h(n)=0时，A星算法就转化为了Dijkstra算法，即：每次只考虑距离起点最近的结点。
2. 如果估计值h(n)等于实际值，那么A星算法可以快速的找到最优路径(几乎不会走弯路)。
3. 如果估计值h(n)小于实际值，那么A星算法可以保证找到一条最短的路径。
4. 如果估计值h(n)大于实际值，那么A星算法不能保证找到一条最短的路径，但是运行的更快。

所以在使用A星算法时，应该把握准确性与速度的均衡。



## 预估距离

### 曼哈顿距离

x轴距离和y轴距离之和。

H(n) = | x(end) - x(n) | + | y(end) - y(n) |

### 欧氏距离

欧几里得距离：两点之间的直线距离。

二维空间公式：$\sqrt{(x2-x1)^2 + (y2-y1)^2}$

三维空间公式：$\sqrt{(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2}$

n维空间公式：$\sqrt{(x1-y1)^2 + (x2-y2)^2 + ... + (xn-yn)^2}$ = $\sqrt{\sum_{i=1}^n(xi-yi)^2}$



### 切比雪夫距离



# 算法原理

1. 把起点加入openlist。(openlist可以使用优先队列)
2. 在openlist中找到F值最小的结点，把它作为当前结点，并**把它移到closelist中**。
3. 处理当前结点的邻接点： 
   - 如果邻接点是==不可到达的==或==已经加入了closelist==，则不做处理。
   - **如果不在openlist中**，1.<u>则把邻接点添加进去</u>，2.<u>并记录当前结点为它的父节点</u>，3.<u>同时计算F、G、H值</u>。
   - **如果已经在openlist中**，1.则检查经过当前结点到邻接点的G值**是否比**邻接点现在的G值小(<u>*和Dijkstra一样*</u>)，2.<u>如果小则记录当前结点为邻接点的父节点</u>，3.<u>并更新F值和G值</u>。

4. 重复步骤2、3。如果==终点加入了closelist==说明路径找到了，则跳出循环；如果==openlist为空==说明没找到路径，则跳出循环。

从终点开始，沿着每个节点的父节点指针移动到起点，输出路径。



# reference

[==A星算法==](https://www.cnblogs.com/Cratial-fighting/p/4646577.html)

[==A星算法详解(个人认为最详细,最通俗易懂的一个版本)==](https://blog.csdn.net/hitwhylz/article/details/23089415)

[==A星算法详解(个人认为最详细,最通俗易懂的一个版本)==](https://zhuanlan.zhihu.com/p/225466669)

[==A* Pathfinding for Beginners==](https://www.gamedev.net/reference/articles/article2003.asp)

[==游戏中常用的寻路算法的分享（3）：A*算法的实现==](https://www.gameres.com/486993.html)

[【路径规划】Astart算法——图文直观解析](https://blog.csdn.net/weixin_41069437/article/details/106751806)

[A*寻路算法详细解读 ](https://www.cnblogs.com/iwiniwin/p/10793654.html)

[A星寻路算法](https://www.jianshu.com/p/65282bd32391)

[A星寻路算法代码--java版（A*搜索算法）](https://www.jianshu.com/p/571b20f61978)

[A* 算法实现及代码下载（多种方式实现，加路径修正）](https://blog.csdn.net/lmnxjf/article/details/8917679)

[32个重要算法之A星算法](http://blog.chinaunix.net/uid-28311809-id-3890698.html)

A星算法中的分层：

https://www.jianshu.com/p/91ea97f23c8e

https://blog.csdn.net/hclworld/article/details/83742261

https://blog.csdn.net/robotcat123/article/details/80552281

https://www.cnblogs.com/gisorange/p/4375888.html



