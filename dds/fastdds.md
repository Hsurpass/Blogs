

安装

- 通过install.sh安装

  ```bash
  https://www.eprosima.com/index.php?option=com_ars&view=browses&layout=normal # 下载
  sudo ./install.sh --build-cores 4 --install-prefix $PWD/fastdds_install --install-examples # --install-prefix后面的路径必须是绝对路径
  sudo ./uninstall.sh --install-prefix [绝对路径] # 默认是/usr/local
  
  sudo apt install libtinyxml2-dev
  # sudo apt install openjdk-11-jdk
  sudo apt install openjdk-8-jdk
  ```
  
  https://fast-dds.docs.eprosima.com/en/latest/installation/binaries/binaries_linux.html





# reference

https://www.zhihu.com/search?type=content&q=dds

[fastdds docs](https://fast-dds.docs.eprosima.com/en/latest/)

[DDSI-RTPS](https://www.omg.org/spec/DDSI-RTPS/2.5/PDF)

[IDL](https://www.omg.org/spec/IDL/4.2/PDF)

[OMG Data Distribution Service](https://www.omg.org/spec/DDS/1.4/PDF)