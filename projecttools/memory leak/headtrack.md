- 使用方法
  - `heaptrack $执行文件`
  - `heaptrack -p $PID`
  - 会动态生成heaptrack.$进程名.$进程ID.zst 文件
  - 使用heaptrack_gui 导入zst文件，可以针对此次生成的zst进行分析，也可以多次采集zst文件进行比较

 使用 heaptrack_gui 重点关注 Bottom-Up, 从底层函数进行的统计的。

![image-20251110192343494](/home/user/me/Blogs/linuxBasic/headtrack/image/image-20251110192343494.png)

- Allocations 申请内存的次数
- Temporary 临时申请内存的次数。比如在函数执行中，申请了内存，就立即释放了。应该重点关注下，内存申请是很耗性能的，尽量减少此值，使用缓存或者内存池等
- Peak 内存申请的高峰，最高点申请了多少内存
- Leaked 截止统计，目前没有释放的内存。有可能是真正的泄露，也有可能内存会一直保留直到程序结束

  **也可以查看FrameGraph查看相关的热点**

![image-20251110192419443](/home/user/me/Blogs/linuxBasic/headtrack/image/image-20251110192419443.png)





https://github.com/KDE/heaptrack