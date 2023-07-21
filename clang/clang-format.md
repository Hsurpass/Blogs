

# 生成.clang-format

windows的clang-format默认放在下面这个路径：

```bash
C:\Users\admin\.vscode\extensions\ms-vscode.cpptools-1.16.3-win32-x64\LLVM\bin\clang-format.exe
```

ubuntu的clang-format默认放在这个路径：

```bash
$HOME/.vscode-server/extensions/ms-vscode.cpptools-1.16.3-linux-x64/LLVM/bin/clang-format
```

在vscode的`settings.json`需要配置一下 `clang-format.executable` 字段：

```json
"clang-format.executable": "$HOME/.vscode-server/extensions/ms-vscode.cpptools-1.16.3-linux-x64/LLVM/bin/clang-format",
```

.clang-format有多种格式，可以通过 `clang-format --help` 命令查看--style 字段。

生成 .clang-format 文件的命令：

```bash
./clang-format --style=LLVM --dump-config > .clang-format
```







# reference

https://clang.llvm.org/docs/ClangFormat.html