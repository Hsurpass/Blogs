DBSCAN 算法是基于密度的算法，所以它将密集区域内的点看作核心点（核心样本）。主要有两个参数：min_samples和eps。
eps表示数据点的邻域半径，如果某个数据点的邻域内至少有min_sample个数据点，则将该数据点看作为核心点。
如果某个核心点的邻域内有其他核心点，则将它们看作属于同一个簇。

如果将eps设置得非常小，则有可能没有点成为核心点，并且可能导致所有点都被标记为噪声。
如果将eps设置为非常大，则将导致所有点都被划分到同一个簇。

如果min_samples设置地太大，那么意味着更少的点会成为核心点，而更多的点将被标记为噪声。

reference:
https://zhuanlan.zhihu.com/p/185623849
https://www.naftaliharris.com/blog/visualizing-dbscan-clustering/
https://zhuanlan.zhihu.com/p/94022640
https://zhuanlan.zhihu.com/p/459927289