# 安装go

## linux

```bash
tar -C /usr/local -xzf go1.21.0.linux-amd64.tar.gz

vi ~/.bashrc
GOROOT=/usr/local/go/bin
export PATH=$GOROOT:$PATH


go version

# https://goproxy.cn/ # go env -w GO111MODULE=auto
## or
# https://proxy.golang.com.cn/zh/
# https://goproxy.io/

ctrl + shift + p
>Go: Install/Update Tools

ctrl + ,
go: format tool # select goimports
go: lint tool # select staticcheck
Go: Use Language Server # select

mkdir mygo_workspace && cd mygo_workspace 
go mod init mygo(模块名) # 生成gomod go1.11解决依赖问题 
```

reference:

https://go.dev/dl

https://go.dev/doc/install

https://go-zh.org/doc/install



安装问题：

1. vscode 在安装 go 插件后会在页面的右下角显示 **The "gopls" command is not available. Run "go install -v golang.org/x/tools/gopls@latest" to install.**

   ```bash
   #GOPROXY默认值
   GOPROXY='https://proxy.golang.org,direct'
   ```
   
   解决：
   
   ```bash
   go env -w GO111MODULE=on
   go env -w GOPROXY=https://goproxy.io,direct
   or
   go env -w GOPROXY=https://proxy.golang.com.cn,direct
   or
   go env -w GOPROXY=https://goproxy.cn,direct # ping goproxy.cn
   ```

GO111MODULE 开启或关闭模块支持，它有三个可选值：`off`、`on`、`auto`，默认值是 `auto`：

- `GO111MODULE=off` 无模块支持，go 会从 `GOPATH` 和 `vendor` 文件夹寻找包。
- `GO111MODULE=on` 模块支持，go 会忽略 `GOPATH` 和 `vendor` 文件夹，只根据 go.mod 下载依赖。
- `GO111MODULE=auto` 在 `$GOPATH/src` 外面且根目录有 go.mod 文件时，开启模块支持。

reference:

https://l2m2.top/2020/05/26/2020-05-26-fix-golang-tools-failed-on-vscode/

https://goproxy.io/zh/

https://goproxy.cn/



# go环境变量

## GOPATH

如果使用了模块在pkg/mod存放一些我们`go install/get`或者 `go mod tidy`下来的包，我们称之为模块缓存，如果想清理这些模块缓存使用`go clean -modcache`

### 设置局部GOPATH

```bash
#linux:
export GOPATH=$HOME/workspace/my_project_path/gopath
#windows:
set GOPATH=%USERPROFILE%\go
```

在设置完GOPATH之后，你将会发现在指定的目录下出现了三个子目录：src、pkg和bin。其中，src目录用于存放Go项目的源代码，pkg目录用于存放编译好的包文件，bin目录用于存放可执行文件。你可以按照这种目录结构组织你的代码，以便更好地管理和维护。



| 命令                     | 作用                             | 使用场景                |
| :----------------------- | :------------------------------- | :---------------------- |
| `go mod tidy`            | 整理依赖，添加缺失的，删除未用的 | 日常维护，保持干净      |
| `go mod download`        | 下载依赖到本地缓存               | 快速下载，不修改 go.mod |
| `go get package@version` | 添加特定版本的依赖               | 明确要添加的依赖        |
| `go mod vendor`          | 创建 vendor 目录                 | 离线部署                |

```bash
# 1. 初始化新项目
go mod init myproject

# 2. 编写代码，添加 import
# 3. 整理依赖
go mod tidy

# 4. 检查变化
git diff go.mod go.sum

# 5. 提交到版本控制
git add go.mod go.sum # 校验和：更新 go.sum 文件确保安全性
git commit -m "更新依赖"
```



# go

## 基本类型

Go语言的基本类型有：

- bool
- string
- int、int8、int16、int32、int64
- uint、uint8、uint16、uint32、uint64、uintptr
- **byte** // uint8 的别名
- **rune** // int32 的别名 代表一个 Unicode 码
- float32、float64
- complex64、complex128

## 关键字

### new

 new 关键字对类型（包括结构体、整型、浮点数、字符串等）进行实例化，结构体在实例化后会形成指针类型的结构体

使用 new 的格式如下：

```go
ins := new(T)
```

其中：

- T 为类型，可以是结构体、整型、字符串等。
- ins：T 类型被实例化后保存到 ins 变量中，ins 的类型为 ***T**，属于**指针**。

在Go语言中，访问结构体指针的成员变量时可以继续使用`.`，这是因为Go语言为了方便开发者访问结构体指针的成员变量，使用了语法糖（Syntactic sugar）技术，将 **ins.Name 形式转换为 (*ins).Name**。



### defer

作用：延迟函数调用。

- 只有在defer语句的外层函数执行完成后才会执行defer语句
- 如果有多条语句，则会先把它们依次压入栈中，等到外层函数执行结束后再按照后进先出的顺序依次调用
- 还可以用在互斥锁自动解锁，文件自动关闭等任何RAII的地方。

### panic

https://blog.go-zh.org/defer-panic-and-recover

### recover



## 控制语句

### select

select的控制结构类似于switch，结构中也有多个case，但是这些case中的表达式必须都是channel的收发操作：

```go
select {
  case <- channel1:
    // 执行的代码
  case value := <- channel2:
    // 执行的代码
  case channel3 <- value:
    // 执行的代码

    // 你可以定义任意数量的 case

  default:
    // 所有通道都没有准备好，执行的代码
}
```

- 无论哪个表达式返回都会立刻执行case中的代码。

- 如果多个表达式同时返回，则会随机的执行其中一个

- 如果没有表达式返回：

  - 但有default子句，则执行该语句；(利用default可以进行**非阻塞的收发**)
  - 如果没有default子句，则select阻塞，类似于linux中的select system-call

   

选择随机执行的好处是**防止饥饿问题**的发生：

```go
func main() {
	ch := make(chan int)
	go func() {
		for range time.Tick(1 * time.Second) {
			ch <- 0
		}
	}()

	for {
		select {
		case <-ch:
			println("case1")
		case <-ch:
			println("case2")
		}
	}
}

$ go run main.go
case1
case2
case1
...
```

在上面代码中两个case都是同时满足执行条件的，如果按照顺序依次判断，第二个case永远不会得到执行，所以要随机选择一个。

https://draveness.me/golang/docs/part2-foundation/ch05-keyword/golang-select/



## 结构体和接口

### 接口

接口也是一种类型，它所定义的变量也是一种值，这个变量也可以像值一样传递，作为函数的参数和返回值。

在内部，接口值可以看做包含**值**和具体**类型**的**元组**：

```go
(value, type)
```

#### 空接口	

指定了零个方法的接口值被称为 *空接口：*：

```go
interface{}
```

空接口可保存**任何类型**的值。（因为每个类型都至少实现了零个方法。）

**空接口被用来处理未知类型的值**。例如，`fmt.Print` 可接受类型为 `interface{}` 的任意数量的参数。

```go
func describe_nil(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}
func test_nil_interface() {
	var i interface{}
	describe_nil(i) // (<nil>, <nil>)

	i = 42
	describe_nil(i) // (42, int)

	i = "abc"
	describe_nil(i) // (abc, string)
}
```





## 数据结构

### 数组

长度固定

### 切片

动态数组

https://blog.go-zh.org/go-slices-usage-and-internals

### map

hash表 链地址法解决冲突，

### string

## 并发

### channel

### goroutine

不同的goroutine之间通过channel来进行通信



# reference

https://shell.cloud.google.com/

https://go-zh.org/

https://go-zh.org/doc/

[golang github](https://github.com/golang/go)

[官网](https://go.dev/)

[go语言中文网](https://studygolang.com/)

[C语言中文网golang教程](http://c.biancheng.net/golang/)

[runoob go教程](https://www.runoob.com/go/go-tutorial.html)

[500 + Go 语言开源项目合集（2021版）](https://zhuanlan.zhihu.com/p/424624289?utm_id=0)

https://topgoer.com/

[Golang标准库文档](http://word.topgoer.com/)



[Effective Go](https://go.dev/doc/effective_go?hl=zh-CN)

[How to Write Go Code](https://go.dev/doc/code?hl=zh-CN)

[如何使用go编程](https://go-zh.org/doc/code.html)

[实效go编程](https://go-zh.org/doc/effective_go.html)



[go指南 接下来去哪？](https://tour.go-zh.org/concurrency/11)

[build-web-application-with-golang](https://github.com/astaxie/build-web-application-with-golang)

[Go入门指南](https://github.com/Unknwon/the-way-to-go_ZH_CN)



[go语言标准库中文版](https://studygolang.com/pkgdoc)

[标准库中文版](https://go-zh.org/pkg/)

[go语言设计与实现](https://draveness.me/golang/)

goweb:

https://gowebexamples.com/

https://gobyexample.com/

gin:

https://pkg.go.dev/github.com/gin-gonic/gin?hl=zh-CN

https://gin-gonic.com/docs/?hl=zh-CN

开源项目：

[有哪些值得学习的 Go 语言开源项目？](https://www.zhihu.com/question/20801814/answer/2176873844)

https://github.com/redis/go-redis

https://github.com/zehuamama/tinyrpc

https://github.com/smallnest/rpcx

https://github.com/mattn/go-sqlite3

https://github.com/xiaogao67/gin-cloud-storage

https://github.com/ethushiroha/MyCloudDisk

https://github.com/beego/beego



https://github.com/golang/tools/blob/master/gopls/doc/workspace.md