配置openssh免密登录：

```bash
# 远程机器：
sudo passwd
sudo apt update
sudo install net-tools
sudo apt install openssh-server # 安装openssh服务
vi /etc/ssh/sshd_config
PasswordAuthentication yes # 密码验证
PermitRootLogin yes #允许root登录
sudo service ssh restart # 重启ssh服务

# 本机：
ssh-keygen # 生成秘钥 ssh-keygen -t rsa -b 4096
cd .ssh
ssh-copy-id remote_name@remote_ip:port # 把公钥复制到远程机器
ssh remote_name:remote_ip # 配置完公钥后就可以直接登录到远程了，不用再输入密码
alias k3s='ssh remote_name@remote_ip' # 配置别名（只在当前shell有效） 永久生效：写在.bashrc

```

