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
  cmake --build build -j4
  cmake --install install
  ```

  

https://opendds.readthedocs.io/en/latest-release/devguide/building/index.html

https://www.dre.vanderbilt.edu/~schmidt/DOC_ROOT/ACE/ACE-INSTALL.html#installpre







# reference

https://opendds.org/

https://www.omg.org/spec/DDS/1.4/PDF#nameddest=G5.1028274

