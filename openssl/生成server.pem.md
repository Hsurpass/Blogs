`server.pem`文件通常是一个包含服务器证书和私钥的PEM格式文件。要生成这个文件，你需要首先创建一个自签名的SSL证书，并将其与私钥合并到一个文件中。 以下是一种使用OpenSSL工具来生成自签名SSL证书和私钥的基本步骤：

1. 安装OpenSSL：如果你还没有安装OpenSSL，请先下载并安装它。

2. 创建私钥：

   运行以下命令以创建一个名为`server.key`的私钥文件：

   ```bash
   openssl genpkey -algorithm RSA -out server.key
   or
   openssl genrsa -out server.key 2048		# 生成一个2048位的RSA私钥
   
   openssl rsa -in server.key -pubout # 查看公钥 
   ```

3. 创建**自签**名SSL证书：

   运行以下命令以创建一个名为`server.crt`的自签名SSL证书文件：

   ```bash
   openssl req -new -x509 -key server.key -out server.crt -days 365 -subj "/C=US/ST=State/L=City/O=Organization/CN=localhost"
   or
   openssl req -new -key server.key -out cert.csr
   
   openssl x509 -text -in server.crt #查看证书信息
   openssl x509 -in server.crt -noout -dates #查看证书有效时间
   ```

   其中，`-days 365`表示该证书的有效期为365天，`-subj "/C=US/ST=State/L=City/O=Organization/CN=localhost"`表示证书的主题信息。

4. 合并私钥和证书：

   运行以下命令将私钥和证书合并到一个名为`server.pem`的文件中：

   ```bash
   cat server.crt server.key > server.pem
   or
   openssl x509 -req -days 365 -in cert.csr -signkey server.key -out cert.pem
   ```

现在，你就可以在你的应用程序中使用`server.pem`文件了。