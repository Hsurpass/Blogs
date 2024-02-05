ubuntu安装eigen

```bash
apt show libeigen3-dev # apt show libeigen3-dev
sudo apt install libeigen3-dev 
pkg-config --modversion eigen3 # 查询当前版本
```



手动编译

```bash
git clone https://gitlab.com/libeigen/eigen.git
cd eigen && mkdir build
cmake -B build
cmake --build build -j2
cmake --install build --prefix _install
```





| 模块        | 头文件                       | 内容                                                         |
| ----------- | ---------------------------- | ------------------------------------------------------------ |
| Core        | #include <Eigen/Core>        | 矩阵和数组 (向量) 类 (Matrix, Array)，基于线性代数还有数组操作 |
| Geometry    | #include <Eigen/Geometry>    | 变换，平移，缩放，2D 旋转和 3D 旋转 (包括四元数和角轴)       |
| LU          | #include <Eigen/LU>          | 使用求解器进行求逆，行列式，LU 分解操作                      |
| Cholesky    | #include <Eigen/Cholesky>    | 使用求解器进行 LLT, LT, Cholesky 分解                        |
| Householder | #include <Eigen/Householder> | Householder 变换；被用作几个线性代数模块                     |
| SVD         | #include <Eigen/SVD>         | SVD 分解与最小二乘求解器                                     |
| QR          | #include <Eigen/QR>          | QR 分解                                                      |
| Eigenvalues | #include <EIgen/Eigenvalues> | 特征值，特征向量分解                                         |
| Sparse      | #include <Eigen/Sparse>      | 稀疏矩阵存储以及相关的基本线性代数                           |
| Dense       | #include <Eigen/Dense>       | 包括 Core, Geometry, LU, Cholesky, SVD, QR, Eigenvalues 的头文件 |
| Eigen       | #include <Eigen/Eigen>       | 包括 Dense 和 Sparse 的头文件                                |





# reference

http://eigen.tuxfamily.org/index.php?title=Main_Page

[Eigen的介绍、安装与入门操作](https://zhuanlan.zhihu.com/p/462494086?utm_id=0)

https://blog.51cto.com/u_6725876/5134436