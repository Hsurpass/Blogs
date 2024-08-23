##### windows下nodejs进程的查看、删除

1. 查看指定端口下的进程

   ```
   netstat -ano | findstr "8000"
   ```

2. 根据PID获取进程名称

   ```
   tasklist | findstr PID
   ```

3. 根据进程名称结束进程

   ```
   taskkill /f /im node.exe
   ```

##### linux结束node进程

```
ps -ef | grep node
kill xxxx
```

