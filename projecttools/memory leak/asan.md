# AddressSanitizer

https://github.com/google/sanitizers/wiki/AddressSanitizer

简称Asan，优势在于CPU开销小，程序性能损耗小(2倍左右)。缺点在于需要添加 `-fsanitize=address` 选项重新编译。

```bash
 #0 0x7f3b8ccbc587 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cc:104
    #1 0x564360c6125e in main /mnt/d/WorkSpace/tmp/test.cpp:9
    #2 0x7f3b8c693082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
```


