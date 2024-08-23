

```bash
# 创建一个新的私钥文件 ca.key
openssl genpkey -algorithm RSA -out ca.key -aes256
or
openssl genrsa -out ca.key 2048	

# 创建一个新的证书请求文件 ca.csr
openssl req -new -key ca.key -out ca.csr

openssl x509 -req -in ca.csr -extensions v3_ca -signkey ca.key -out ca.crt
# 使用私钥和证书请求文件创建自签名的 CA 证书
openssl x509 -req -days 365 -in ca.csr -signkey ca.key -out ca.crt

# 将 CA 证书转换为 PEM 格式，并将其保存到 ca.pem 文件中
openssl x509 -in ca.crt -out ca.pem -outform pem


```



```bash
openssl genrsa -out server.key 2048	

openssl genrsa -des3 -out server.key 2048	
openssl req -new -key server.key -out server.csr

#对服务器证书进行签名
openssl x509 -req -days 365 -in server.csr -CAkey ca.key -CA ca.crt -CAcreateserial -out server.crt

cat server.crt server.key > server.pem
openssl x509 -in server.key server.crt -out server.pem -outform pem

```

