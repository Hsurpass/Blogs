## linux编译安装boost

```
./bootstrap.sh --help
```

![image-20210606170217002](image/image-20210606170217002.png)

```
./bootstrap.sh --show-libraries
```

![image-20220506154316743](image/image-20220506154316743.png)



1. ```
   ./bootstrapsh
   ```

2. ``` 
   ./b2 --help
   ```

   ![image-20210609230132294](image/image-20210609230132294.png)

   ![image-20210609230215737](image/image-20210609230215737.png)

   ![image-20210609230257136](image/image-20210609230257136.png)

   ![image-20210609230318655](image/image-20210609230318655.png)

3. install or stage

   + install: 会拷贝头文件并编译所有库 (会在linux目录下生成include、lib子目录)

   ```
   ./b2 --prefix=../linux --build-dir=../linux install
   ```

   + stage: 只会编译库（只会生成lib目录）

   ```
   ./b2 --stagedir=../linux --build-dir=../linux stage
   ```

   


