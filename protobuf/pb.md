http://www.52im.net/thread-323-1-1.html

https://www.jianshu.com/p/a24c88c0526a

https://www.jianshu.com/p/b33ca81b19b5

http://www.cppblog.com/sunicdavy/archive/2014/12/16/209189.html    // pb language service

https://marketplace.visualstudio.com/items?itemName=mreu.ProtobufLanguageService	//vs插件

https://blog.csdn.net/majianfei1023/article/details/45371743

https://cloud.tencent.com/developer/article/1056432

https://cloud.tencent.com/developer/article/1602549

https://blog.csdn.net/liangjisheng/article/details/84646949

https://blog.csdn.net/liangjisheng/article/details/84646949

https://www.freesion.com/article/8599353804/

https://blog.csdn.net/huakai16/article/details/79583150

https://blog.csdn.net/liangjisheng/article/details/84646949





```
cd protobuf
cd cmake
mkdir build & cd build
```

```
mkdir release & cd release
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../../install/release ../..
```

```
mkdir debug & cd debug
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../../install/debug ../..
```

```
C:\Path\to\protobuf\cmake\build> mkdir solution & cd solution
cmake -G "Visual Studio 12 2013" -DCMAKE_INSTALL_PREFIX=../../../../install ../..
```

```
nmake
nmake install
```



```
g++ addressbook.pb.cc main.cpp `pkg-config --cflags --libs protobuf` -std=c++11
```

