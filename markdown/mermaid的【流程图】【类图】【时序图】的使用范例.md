流程图实例，

流程图分成多种方向：

- TB-从上到下
- TD-自顶向下/从上至下相同
- BT-从下到上
- RL-从右到左
- LR-从左到右

```mermaid
graph LR
A[Hard]
B(Round)
C{Decision}
A--实线-->B
B-.->C
A-.加文字虚线.->C
C-->|One| D[Result 1]
C-->|Two| E[Result 2]
```

```mermaid
graph TD
A[Hard]
B(Round)
C{Decision}
A--实线-->B
B-.->C
A-.加文字虚线.->C
C-->|One| D[Result 1]
C-->|Two| E[Result 2]
```





-------------





类图实例【泛化，继承关系，子类与父类】

```mermaid
classDiagram
    Animal <|-- Duck
    Animal <|-- Fish
    Animal <|-- Zebra
    Animal : +int age
    Animal : +String gender
    Animal: +isMammal()
    Animal: +mate()
    class Duck{
      +String beakColor
      +swim()
      +quack()
    }
    class Fish{
      -int sizeInFeet
      -canEat()
    }
    class Zebra{
      +bool is_wild
      +run()
    }
```

实现实例【类与接口的关系】，不过Typora的接口没有使用虚线

```mermaid
classDiagram
   class IFlyable{
     <<interface>>
     + flying()
   }
   IFlyable<|..Bat
   Bat:+flying()
```

组合实例【整体与部分的关系，部分不能离开整体】

```mermaid
classDiagram
  Computer *-- CPU
  Computer *-- Mainboard
  Computer *-- HardDisk
  Computer *-- MemeryCard
```

聚合实例【整体与部分的关系，部分可以离开整体单独存在】

```mermaid
classDiagram
  Company o-- Empolyee
```

关联实例【一种拥有关系，一个类知道另一个类的属性和方法，弱相关，但是不从属不包含】

```mermaid
classDiagram
  Reader "1..*" -- "1..*" Book
  Book "1..*"--> "1"Author
```

依赖实例【一种使用关系，一个类的实现需要另一个类的协助】

```mermaid
classDiagram
  Animal..>Food
```







------------------

时序图实例

```mermaid
sequenceDiagram
Alice->>John: hello John, how are you?
loop HealthCheck
	John->>John: Fight against hypochondria
end
Note right of John: Rational thoughts!
John-->>Alice: Great!
John-->>Bob: How about you?
Bob-->>John: Jolly good!
```

