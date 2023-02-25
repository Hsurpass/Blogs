安装perl CGI

```
perl -e shell -MCPAN
<cpan> install CGI
```

```
apt-get install perl-CGI
```

```
1.执行　perl -MCPAN -e shell

2.执行　install CGI.pm    （这里我试过install CGI，发现不行）

3.没有以外的话这个模块也就安装成功了

可以在终端里执行　perl -MCGI -e 'print "CGI.pm version $CGI::VERSION\n";'  这条命令来验证是否安装成功

如果出现　CGI.pm version 4.26　这种显示CGI版本的文本，恭喜你．

如果出现　Can't locate CGI.pm in @INC.......   这种东西的话，那么很不幸．．．你可以去找其他办法了
```

# 解决 Can‘t locate CGI.pm in @INC (you may need to install the CGI module)

```
sudo apt install libcgi-ajax-perl
sudo apt install libcgi-application-perl
```





reference:

https://blog.csdn.net/weixin_45808445/article/details/117161707

https://www.it610.com/article/1187546210265833472.htm

https://blog.huati365.com/803f7878598e3e87

https://www.cnblogs.com/pengdonglin137/articles/6994912.html