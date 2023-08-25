# 安装go

## linux

```bash
tar -C /usr/local -xzf go1.21.0.linux-amd64.tar.gz

vi ~/.bashrc
GOROOT=/usr/local/go/bin
export PATH=$PATH:$GOROOT

go version
```



安装问题：

1. vscode 在安装 go 插件后会在页面的右下角显示 **The "gopls" command is not available. Run "go install -v golang.org/x/tools/gopls@latest" to install.**

   解决：

   ```bash
   go env -w GO111MODULE=on
   go env -w GOPROXY=https://goproxy.io,direct
   or
   go env -w GOPROXY=https://proxy.golang.com.cn,direct
   or
   go env -w GOPROXY=https://goproxy.cn,direct
   ```

GO111MODULE 开启或关闭模块支持，它有三个可选值：`off`、`on`、`auto`，默认值是 `auto`：

- `GO111MODULE=off` 无模块支持，go 会从 `GOPATH` 和 `vendor` 文件夹寻找包。
- `GO111MODULE=on` 模块支持，go 会忽略 `GOPATH` 和 `vendor` 文件夹，只根据 go.mod 下载依赖。
- `GO111MODULE=auto` 在 `$GOPATH/src` 外面且根目录有 go.mod 文件时，开启模块支持。

https://l2m2.top/2020/05/26/2020-05-26-fix-golang-tools-failed-on-vscode/

https://goproxy.io/zh/

https://goproxy.cn/

# reference

https://go-zh.org/

https://go-zh.org/doc/

https://go-zh.org/doc/install



https://go.dev/doc/install

https://go.dev/dl



[golang github](https://github.com/golang/go)

[官网](https://go.dev/)

[go语言中文网](https://studygolang.com/)

[C语言中文网golang教程](http://c.biancheng.net/golang/)