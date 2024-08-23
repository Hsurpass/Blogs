

.
install
├── MPC	# 指的是OpenDDS的MPC，cp OpenDDS/MPC .  or ln -s share/dds/MPC MPC
│   ├── config
│   └── modules
├── bin
│   └── PerlDDS # cp Opendds/bin/PerlDDS PerlDDS
├── dds	# ln -s share/dds/dds dds or cp share/dds/dds .
│   └── idl
├── include
│   ├── FACE
│   ├── ace
│   │   └── os_include
│   ├── dds
│   │   ├── CorbaSeq
│   │   ├── DCPS
│   │   ├── FACE
│   │   ├── InfoRepo
│   │   ├── monitor
│   │   └── rtpsrelaylib
│   ├── model
│   ├── orbsvcs
│   ├── rapidjson
│   │   ├── error
│   │   ├── internal
│   │   └── msinttypes
│   └── tao
│       ├── AnyTypeCode
│       ├── BiDir_GIOP
│       ├── CSD_Framework
│       ├── CSD_ThreadPool
│       ├── CodecFactory
│       ├── Codeset
│       ├── DynamicInterface
│       ├── IORManipulation
│       ├── IORTable
│       ├── ImR_Client
│       ├── Messaging
│       ├── PI
│       ├── PortableServer
│       └── Valuetype
├── lib
│   └── pkgconfig
└── share
    ├── ace
    │   ├── MPC	# cp OpenDDS/ACE_wrappers/MPC share/ace/
    │   ├── bin
    │   ├── docs
    │   ├── include
    │   └── lib
    ├── cmake
    │   └── OpenDDS
    ├── dds
    │   ├── MPC
    │   ├── bin
    │   └── dds
    └── tao
        ├── MPC
        └── docs



编译安装

- 使用configure

  ```bash
  git clone git@github.com:OpenDDS/OpenDDS.git
  ./configure
  ./configure --prefix=$PWD/install
  ./configure --prefix=$PWD/install --ace=download
  sudo make -j 4
  sudo make install
  source setenv.sh
  ```

  
  
- 使用cmake

  二选一

  ```bash
  CMake Error at CMakeLists.txt:20 (message): It looks like OpenDDS was already built here using MPC.  This could cause issues with a CMake build.  Please clean this source tree or use a separate one.
  
  cmake -B build -DCMAKE_UNITY_BUILD=TRUE
  sudo cmake --build build -j4 #需要sudo权限
  cmake --install build --prefix install
  ```

  

https://opendds.readthedocs.io/en/latest-release/devguide/building/index.html

https://www.dre.vanderbilt.edu/~schmidt/DOC_ROOT/ACE/ACE-INSTALL.html#installpre



编译Messenger

-   使用cmake

    ```bash
    cmake -B build 
    cmake --build build -j2
    ```

-   使用MPC

    ```bash
    opendds_idl Messenger.idl
    mwc.pl -type gnuace .
    make no_opendds_safety_profile=1
    ```




编译ishape

```bash
cmake -B build -DCMAKE_PREFIX_PATH=/opt/Qt/5.15.2/gcc_64
```

[OpenDDS/docs/qt.md at DDS-3.27 · OpenDDS/OpenDDS (github.com)](https://github.com/OpenDDS/OpenDDS/blob/DDS-3.27/docs/qt.md)





# reference

[What’s in the DDS Standard? (dds-foundation.org)](https://www.dds-foundation.org/omg-dds-standard/)

https://opendds.org/

https://www.omg.org/spec/DDS/1.4/PDF#nameddest=G5.1028274

