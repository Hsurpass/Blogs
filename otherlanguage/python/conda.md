



https://www.runoob.com/python-qt/anaconda-tutorial.html

https://docs.anaconda.com/miniconda/miniconda-hashes/

https://repo.anaconda.com/archive/



```bash
conda create --name myenv python=3.8
```



```bash
~/miniconda3/bin/conda init bash
```

命令 `~/miniconda3/bin/conda init bash` 用于初始化 Conda 以与 Bash shell 集成。当你执行这个命令时，它会修改你的 Bash 配置文件（通常是 `~/.bashrc` 或 `~/.bash_profile`，取决于你的系统和配置），以便在每次启动新的 Bash 会话时自动激活 Conda 环境。

具体来说，==这个命令会添加几行代码到你的 Bash 配置文件中==，这些代码会在 Bash 启动时执行 `conda activate base`（或者如果你设置了默认环境，则会激活那个环境）。然而，从 Conda 4.6 版本开始，默认行为是在启动时不自动激活任何环境，而是让用户手动选择激活哪个环境（如果需要的话）。不过，`conda init` 命令仍然会设置一些环境变量和函数，以便你可以方便地管理你的 Conda 环境。

执行这个命令后，你可能需要关闭并重新打开你的 Bash 会话，或者通过运行 `source ~/.bashrc`（或相应的配置文件）来重新加载你的 Bash 配置，以便让更改生效。

请注意，如果你使用的是其他类型的 shell（如 zsh、fish 等），你需要使用相应的命令来初始化 Conda（例如，`conda init zsh` 用于 zsh）。

另外，如果你已经安装了 Miniconda 并希望为所有用户（而不仅仅是当前用户）设置 Conda 环境，你可能需要使用 `sudo` 来执行 `conda init` 命令，并将配置文件修改为全局配置文件（如 `/etc/bash.bashrc`，但这通常不推荐，因为它可能会影响系统上的所有用户）。然而，在大多数情况下，为单个用户设置 Conda 环境是更常见和推荐的做法。
