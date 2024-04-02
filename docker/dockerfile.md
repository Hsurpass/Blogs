# Dockerfile

Docker 按顺序在 Dockerfile 中运行指令。Dockerfile 必须以 `FROM` 指令开头。

-   ADD: 添加本地或远程文件和目录

    下面的示例使用相对路径，并将“test.txt”添加到 `<WORKDIR>/relativeDir/` ：

    ```dockerfile
    ADD test.txt relativeDir/
    ```

    而此示例使用绝对路径，并将“test.txt”添加到 `/absoluteDir/`

    ```dockerfile
    ADD test.txt /absoluteDir/
    ```

    

-   ARG: 使用生成时变量

    在dockerfile中以k-v的形式定义：

    ```dockerfile
    ARG <name>[=<default value>]
    ```

    -   设置默认值

        ```dockerfile
        FROM busybox
        ARG user1=someuser
        ARG buildno=1
        # ...
        ```

    也可以通过--build-arg选项传参：

    ```dockerfile
    docker build --build-arg k=v
    ```

    -   不设置默认值

        ```dockerfile
        FROM busybox
        ARG user1
        ARG buildno
        # ...
        ```

    

    
-   ARG与FROM交互
    
    ```dockerfile
        ARG  CODE_VERSION=latest
        FROM base:${CODE_VERSION}
        CMD  /code/run-app
        
        FROM extras:${CODE_VERSION}
        CMD  /code/run-extras
        ```
    
    第一个FROM可以使用在它前面出现的所有ARG变量。由于在第一个FROM之前声明的变量不在构建阶段，所以第二个FROM不能使用这些变量。要想使用：
    
    ```dockerfile
        ARG VERSION=latest
        FROM busybox:$VERSION
        ARG VERSION
        RUN echo $VERSION > image_version
        ```


    **`ARG` 变量不会像变量那样 `ENV` 持久化到构建的映像中。但是， `ARG` 变量确实以类似的方式影响生成缓存。**
    
    ARG的作用域：
    
    预定义的ARG：


​    

-   CMD:指定默认命令

    `RUN` 、 `CMD` 和 `ENTRYPOINT` 指令都有两种可能的形式：

    -   `INSTRUCTION ["executable","param1","param2"]` (exec form) 
    -   `INSTRUCTION command param1 param2` (shell form)

    exec 形式被解析为 JSON 数组，这意味着您**必须在单词两边使用双引号** （“），而不是单引号 （'）。

    CMD有三种格式：

    `CMD ["executable","param1","param2"]` (exec 表单)

    `CMD ["param1","param2"]` （exec 形式，作为ENTRYPOINT的==**默认参数**==），这种情况需要指定ENTRYPOINT。

    `CMD command param1 param2` (shell 表单)

    ==Dockerfile中只能有一条CMD指令。如果列出多个CMD，则只有最后一个生效。== 

    使用场景：

    希望容器每次都运行相同的可执行文件，则应考虑CMD和ENTRYPOINT结合使用。如果用户通过`docker run`指定参数则将覆盖CMD提供的默认参数，但仍使用默认的ENTRYPOINT。

-   COPY: 复制文件和目录

    下面的示例使用相对路径，并将“test.txt”添加到 `<WORKDIR>/relativeDir/` ：

    ```dockerfile
    COPY test.txt relativeDir/
    ```

    而此示例使用绝对路径，并将“test.txt”添加到 `/absoluteDir/`

    ```dockerfile
    COPY test.txt /absoluteDir/
    ```

-   ENTRYPOINT: 指定默认的可执行文件

    Dockerfile中只有最后一条 `ENTRYPOINT` 指令才会生效。

    可以使用 `docker run --entrypoint` 标志覆盖 `ENTRYPOINT` 指令。

    ENTRYPOINT有两种格式：

    -   exec形式：

        ```dockerfile
        ENTRYPOINT ["executable", "param1", "param2"]
        ```

        例：

        ```dockerfile
        FROM ubuntu
        ENTRYPOINT ["top", "-b"]
        CMD ["-c"]
        ```

    -   shell形式：

        ```dockerfile
        ENTRYPOINT command param1 param2
        ```

        

    

    exec 表单最适合用于指定 `ENTRYPOINT` 指令。

    ```dockerfile
    ENTRYPOINT ["/bin/bash", "-c", "echo", "hello"]
    ```

    

-   ENV: 设置环境变量

    ```dockerfile
    ENV <key>=<value> ...
    ```

    可以一次设置多个环境变量。

    当从该镜像运行容器时，使用 `ENV` 设置的环境变量将保留。您可以使用 `docker inspect` 查看这些值，并使用 更改它们 `docker run --env <key>=<value>` 。

    **环境变量持久性可能会导致意想不到的副作用**。例如，设置 `ENV DEBIAN_FRONTEND=noninteractive` 会更改 `apt-get` 的行为，并且可能会使图像的用户感到困惑。

    如果仅在生成期间需要环境变量，而不是在最终映像中，请考虑为单个命令设置一个值：

    ```dockerfile
    RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y ...
    ```

    或者使用 `ARG` ，它不会保留在最终映像中：

    ```dockerfile
    ARG DEBIAN_FRONTEND=noninteractive
    RUN apt-get update && apt-get install -y ...
    ```

-   EXPOSE: 描述您的应用程序正在监听哪个端口

    ```dockerfile
    EXPOSE 80/tcp # 默认
    EXPOSE 80/udp
    ```

    无论设置如何 `EXPOSE` ，都可以在运行时使用 `-p` 标志覆盖它们。

    ```dockerfile
    docker run -p 80:80/tcp -p 80:80/udp ...
    ```

    

-   FROM: 从基础镜像创建新的build阶段

    `FROM` 可以在单个 Dockerfile 中多次出现，以创建多个映像，或将一个生成阶段用作另一个生成阶段的依赖项。只需在每条新 `FROM` 指令之前记下提交输出的最后一个镜像 ID。每 `FROM` 条指令都会清除先前指令创建的任何状态。

    一个FROM是一个build阶段。

-   HEALTHCHECK: 在启动时检查容器的运行状况

-   LABEL: 向镜像添加元数据

    ```dockerfile
    LABEL <key>=<value> <key>=<value> <key>=<value> ...
    LABEL multi.label1="value1" multi.label2="value2" other="value3"
    ```

    LABEL是key-value键值对，一个镜像可以有多个标签。value必须使用”“

    

-   MAINTAINER: 指定镜像的作者

    已废弃。应使用LABLE。

    ```dockerfile
    LABEL org.opencontainers.image.authors="SvenDowideit@home.org.au"
    ```

-   ONBUILD:指定何时在构建中使用镜像的指令

-   RUN: 执行命令

    -   变量替换：

        ```dockerfile
        RUN [ "echo", "$HOME" ]
        ```

        使用 exec 表单不会自动调用`bin/sh`。这意味着不会发生正常的 shell 处理，例如变量替换。`RUN [ "echo", "$HOME" ]` 不会处理 `$HOME` 的变量替换。

        如果要进行 shell 处理，则使用 shell 表单或直接使用 exec 表单执行 shell，例如： `RUN [ "sh", "-c", "echo $HOME" ]` 。

    -   反斜线（‘\’）:

        在 exec 形式中，必须转义反斜杠。这在反斜杠是路径分隔符的 Windows 上尤为重要。否则，由于 JSON 无效，以下行将被视为 shell 形式，并以意外的方式失败：

        ```dockerfile
        RUN ["c:\windows\system32\tasklist.exe"]
        ```

        正确的写法应为：

        ```dockerfile
        RUN ["c:\\windows\\system32\\tasklist.exe"]
        ```

    -   命令换行写

        -   以转移字符连接下一行命令

            ```dockerfile
            RUN source $HOME/.bashrc && \
            echo $HOME
            ```

            ==

            ```dockerfile
            RUN source $HOME/.bashrc && echo $HOME
            ```

        -   以heredocs的格式

            ```dockerfile
            RUN <<EOF
            apt-get update
            apt-get install -y curl
            EOF
            ```

            

        

-   SHELL: 设置镜像默认的shell

    Linux 上的默认 shell 是`["/bin/sh", "-c"]` ，而在 Windows 上是 `["cmd", "/S", "/C"]` 。**该 `SHELL` 指令必须以 JSON 形式编写在 Dockerfile 中。**

    ```dockerfile
    SHELL ["/bin/bash", "-c"]  # 设置默认的shell为 /bin/bash
    RUN echo hello
    ```

    **该 `SHELL` 指令可以多次出现。每 `SHELL` 条指令都会覆盖所有先前 `SHELL` 的指令，并影响所有后续指令。**

-   STOPSIGNAL: 指定退出容器的系统调用信号

-   USER: 设置用户和组ID

    ```dockerfile
    USER <user>[:<group>]
    ```

    or

    ```dockerfile
    USER <UID>[:<GID>]
    ```

    

-   VOLUME: 创建挂载目录。

    该 `VOLUME` 指令创建具有指定名称的挂载点，并将其标记为保存来自本机主机或其他容器的外部挂载卷。该值可以是 JSON 数组， `VOLUME ["/var/log/"]` 也可以是具有多个参数的纯字符串，例如 `VOLUME /var/log` 或 `VOLUME /var/log /var/db` 。

    ```dockerfile
    FROM ubuntu
    RUN mkdir /myvol
    RUN echo "hello world" > /myvol/greeting
    VOLUME /myvol
    ```

    此 Dockerfile 会生成一个镜像，该镜像会导致 `docker run` 在 `/myvol` 创建新的挂载点并将 `greeting` 该文件复制到新创建的卷中。

-   WORKDIR: 更改工作目录。

    如果未指定，则默认工作目录为 `/` 。在实践中，如果您不是从头开始构建 Dockerfile （ `FROM scratch` ）， `WORKDIR` 则可能由您正在使用的基础映像设置。

    `WORKDIR` 指令为 Dockerfile 中的任何 `RUN` 、 、 `CMD` `ENTRYPOINT` `COPY` 和 `ADD` 后面的指令设置工作目录。 `WORKDIR` **如果不存在**，即使它未在任何后续 Dockerfile 指令中使用，**也会创建它**。

    该 `WORKDIR` 指令可以在 Dockerfile 中多次使用。如果提供了相对路径，则它将相对于上一条 `WORKDIR` 指令的路径。例如：

    ```dockerfile
    WORKDIR /a
    WORKDIR b
    WORKDIR c
    RUN pwd
    ```

    此 Dockerfile 中最后一个 `pwd` 命令的输出将是 `/a/b/c` 。

    该 `WORKDIR` 指令可以解析先前使用 `ENV` 设置的环境变量。只能使用 Dockerfile 中显式设置的环境变量，没设置的不能使用。例如：

    ```dockerfile
    ENV DIRPATH=/path
    WORKDIR $DIRPATH/$DIRNAME
    RUN pwd
    ```

    此 Dockerfile 中最后一个 `pwd` 命令的输出将是 `/path/$DIRNAME`。







[Dockerfile 参考 |Docker 文档 --- Dockerfile reference | Docker Docs](https://docs.docker.com/engine/reference/builder/)





