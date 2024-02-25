cmake 命令中添加的参数 -DENABLE_SIGNAL_HANDLING=1 可以确保终止 vsomeip 应用程序的时候不出问题，否则当使用 Ctrl-c 停止应用时，共享内存段 /dev/shm/vsomeip 可能未被正确删除。

```bash
cmake -DENABLE_SIGNAL_HANDLING=1 -B build
```







https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes