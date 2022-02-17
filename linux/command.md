

## cut

- 

- references: 

  http://linux.51yip.com/search/cut

## cp

- 复制某个文件并且重命名

```
cp a.txt /tmp/b.txt
```




## grep

- **-A<显示行数> 或 --after-context=<显示行数>** : print NUM lines of leading context  (除了显示符合范本样式的那一列之外，并显示该行之后的内容。)
- **-B<显示行数> 或 --before-context=<显示行数>** :  print NUM lines of trailing context (除了显示符合样式的那一行之外，并显示该行之前的内容。)
- **-E 或 --extended-regexp** : PATTERN is an extended regular expression (将样式为延伸的正则表达式来使用。)
- **-i 或 --ignore-case** : ignore case distinctions (忽略字符大小写的差别。)
- **-n 或 --line-number** :print line number with output lines (在显示符合样式的那一行之前，标示出该行的列数编号。)


- **-o 或 --only-matching** :show only the part of a line matching PATTERN (只显示匹配PATTERN 部分。)
- **-P 或 --perl-regexp** : PATTERN is a Perl regular expression
- **-r 或 --recursive**: like --directories=recurse (此参数的效果和指定"-d recurse"参数相同。)
- **-v 或 --invert-match** : select non-matching lines (显示不包含匹配文本的所有行。)



- **匹配关键字之前和之后的N个字符**

```
这种适用于一个大文件中只有一行的情况下查找匹配项
grep -E -o ".{0,5}test_pattern.{0,5}" test.txt 
cat test.txt | grep -E -o ".{0,5}test_pattern.{0,5}"
grep -P -o ".{0,5}test_pattern.{0,5}" test.txt 
```

example:

```
这将匹配"string"的前三个字符和后四个字符
echo "some123_string_and_another" | grep -o -P '.{0,3}string.{0,4}'
23_string_and
```

```
test.txt:

abcd
0123_45_6789
efgh
```

```
这将匹配 test.txt文件中 “45” 的前4个字符和后5个字符
grep -E -o ".{0,4}45.{0,5}" test.txt
123_45_6789
```



- **匹配关键字之前的n行和之后的n行**

  ```
  grep -Bn An "test_pattern" test.txt
  ```

  example:

  ```
  test.txt:
  
  eretrtrt
  sdsdfsddf
  abcd
  0123_45_6789
  efgh
  errterer
  vdghdbdvsd
  vvdhbrfwewec
  ```

  

  ```
  grep -B1 -A1 "45" test.txt
  
  abcd
  0123_45_6789
  efgh
  ```

  

- references:

   https://cloud.tencent.com/developer/ask/29626

   https://www.runoob.com/linux/linux-comm-grep.html



## head

- 

- 查看文件前几行内容

  ```
  head -n 10 xx.txt
  ```




## man



![image-20210516110533025](image/image-20210516110533025.png)

1. **用户命令**

   ```
   man 1 cd
   ```

2. 系统调用

   ```
   man 2 read
   ```

3. 标准库调用

   ```
   man 3 sleep
   ```

4. 特殊文件(设备文件)

   ```
   man 4 tty
   ```

5. 文件格式(配置文件的语法)

   ```
   man 5 passwd
   ```

6. 游戏

7. 杂项

8. 系统管理员命令

   ```
   man 8 fdisk
   ```

9. 和内核有关的文件



references: https://cloud.tencent.com/developer/article/1725969?from=information.detail.linux%20man%201%202%203



## nc (可以快速构建网络连接。既可以以服务器的方式运行，也可以以客户端的方式运行。默认以客户端的方式运行)

-p: 当nc命令以客户端的方式运行时，强制其使用指定的端口号。

```
nc -p 12345 SERVERHOST PORT
```

-l: 以服务器方式运行，监听指定端口

```
nc -l 12345
```



## scp

- -r： 递归复制整个目录。
- -P port：注意是大写的P, port是指定数据传输用到的端口号





- 从远程拷贝多个文件到本地

  ```
  scp -P port USER@HOST:/\{ 1.txt,2.json,3.py,4.sh \}
  ```

- 从远程拷贝多个文件，多个文件夹到本地

  ```
  scp -r USER@HOST:/\{ 1.txt,2.json,3.py,4.sh,folder \}
  ```

- 从本地拷贝文件到远程

	```
scp local_file remote_username@remote_ip:remote_folder 
	或者 
	scp local_file remote_username@remote_ip:remote_file 
	或者 
	scp local_file remote_ip:remote_folder 
	或者 
	scp local_file remote_ip:remote_file 
	```
	
	- 第1,2个指定了用户名，命令执行后需要再输入密码，第1个仅指定了远程的目录，文件名字不变，第2个指定了文件名；
	- 第3,4个没有指定用户名，命令执行后需要输入用户名和密码，第3个仅指定了远程的目录，文件名字不变，第4个指定了文件名；
	
- **references:**

  https://www.binarytides.com/linux-scp-command/



## sed

- 

- 查看文件第a行到第b行的内容。

  - 第一种方法：

    ```
    sed -n 'a,bp' xxx.txt
    sed -n '5,10p' xxx.txt	//查看第5行到第10行的内容
    ```

  - 第二种方法

    ```
    cat xxx.txt | tail -n +a | head -n b-a
    cat xxx.txt | tail -n +3000 | head -n 1000 	// 显示从第3000行到3999行
    ```

    ```
    cat xxx.txt | head -n b | tail -n +a
    cat xxx.txt | head -n 4000 | tail -n +3000	// 显示从第3000行到4000行
    ```


  ```
  tail -n 1000 	// 显示最后1000行的内容。
  tail -n +1000	// 从第1000行开始显示，显示之后的内容。
  head -n 1000 	// 显示前面1000行内容。
  ```

- 批量替换文件中指定的字符串

  ```
  sed -i 's/Search_String/Replacement_String/g' Input_File
  
  sudo sed -i 's/archive.ubuntu.com/mirrors.163.com/g' sources.list
  sudo sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' sources.list
  ```



**references:** 

https://linux.cn/article-11367-1.html

https://www.linuxprobe.com/sed-find-replace.html



## strip

移除可执行程序中的调试信息。



## tail

- 

- 查看文件的最后几行内容

  ```
  tail -n 10 xxx.txt
  ```



## tcpdump

- -c: 仅抓取指定数量的数据包。
- -e: 显示以太网帧头部信息。
- -i: 指定要监听的网卡接口。“-i any” 表示抓取所有网卡接口上的数据包。
- -n: 使用IP地址表示主机，而不是主机名；使用数字表示端口号，而不是服务名称。
- -r: 从文件读取数据包信息并显示之。
- -s: 设置抓包时的抓取长度。当数据包的长度超过抓取长度时，tcpdump抓取到的将是被截断的数据包。在4.0以及之前的版本中，默认的抓包长度是68字节。这对于IP、TCP和UDP等协议就已经足够了，但对于像DNS、NFS这样的协议，68字节通常不能容纳一个完整的数据包。不过4.0之后的版本，默认的抓包长度被修改为65535字节，因此不用再担心抓包长度的问题了。
- -t：不打印时间戳。
- -v: 输出一个稍微详细的信息，例如，显示IP数据包中的TTL和TOS信息。
- -w: 将tcpdump的输出已特殊的格式定向到某个文件。
- -x: 以十六进制数显示数据包的内容，但不显示包中以太网帧的头部信息。
- -X: 与-x选项类似，不过还打印每个十六进制字节对应的ASCII字符。
- -XX, 与-X相同，不过还打印以太网帧的头部信息。

```
tcpdump -nt -i eth0 port 12345 -w tmp.pcap
```



## time

time + 可执行程序：可以统计程序的运行时间



## ulimit

永久修改 ulimit参数，修改`/etc/security/limits.conf`

程序崩溃时，系统默认不会生成core文件

- -a: 查看系统参数。
- -c : ulimit -c unlimited 把core文件的大小设置为无限制。(临时修改)
- 



## whatis

- 可以使用 `whatis` 查看某个命令都有哪些功能。

  ```
  whatis sleep
  ```

  ![image-20210516110024368](image/image-20210516110024368.png)







