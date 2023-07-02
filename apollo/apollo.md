由base_map生成routing_map:

```bash
dir_name=modules/map/data/xxx
./scripts/generate_routing_topo_graph.sh --map_dir ${dir_name}
```

由base_map生成sim_map:

```bash
dir_name=modules/map/data/xxx
bazel-bin/modules/map/tools/sim_map_generator --map_dir=${dir_name} --output_dir=${dir_name}
```





https://blog.csdn.net/xiaoma_bk/article/details/122585733

https://blog.csdn.net/weixin_44177594/article/details/126890190

https://blog.csdn.net/lh315936716/article/details/115112200





planning

https://www.cnblogs.com/longjiang-uestc/p/10189159.html

https://huaweicloud.csdn.net/637ef018df016f70ae4ca2ab.html#devmenu5

https://apollo.baidu.com/community/article/32

