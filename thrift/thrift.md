```bash
sudo apt-get install automake bison flex g++ git libboost-all-dev libevent-dev libssl-dev libtool make pkg-config

./bootstrap.sh
./configure --prefix=./installThrift_ --without-java --with-boost=/mnt/d/WorkSpace/4openSourceCode/Boost/installLinuxBoost183 PY_PREFIX=./installThrift_

#只编译c++
./configure --prefix=./installThrift_ --with-cpp --without-java --without-python --without-go --without-py3 --without-nodejs --with-boost=/mnt/d/WorkSpace/4openSourceCode/Boost/installLinuxBoost183 PY_PREFIX=./installThrift_

make 
make install
make uninstall

cmake -B buildThrift/ -DBUILD_JAVASCRIPT=OFF -DBUILD_NODEJS=OFF -DCMAKE_BUILD_TYPE=Debug
cmake --build buildThrift/ -j4
cmake --install buildThrift
#cmake --install buildThrift --prefix installThrift
```





[Debian/Ubuntu install](https://thrift.apache.org/docs/install/debian.html)

[Building from source](https://thrift.apache.org/docs/BuildingFromSource)

https://github.com/apache/thrift



thrift IDL

https://thrift.apache.org/docs/idl

https://thrift.apache.org/docs/types

https://diwakergupta.github.io/thrift-missing-guide/#_types