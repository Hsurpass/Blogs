# 参数

- -d, --data：发送post请求数据体

  ```bash
  $ curl -d'login=emma＆password=123'-X POST https://google.com/login
  # 或者
  $ curl -d 'login=emma' -d 'password=123' -X POST  https://google.com/login
  ```

  ```bash
  curl -d '@data.txt' https://google.com/login	# 读取本地文本文件data.txt的数据向服务器发送，
  ```

- --data-binary：发送二进制请求数据体

  ```bash
  curl -i -X POST --data-binary  "@post.bin" http://xxx.com
  ```

- -H, --header：添加 HTTP 请求的标头

  ```bash
  curl --header "Content-Type: application/json" -H 'Accept-Language: en-US' # 添加了两个请求的标头
  ```

- -i, --include：打印出协议响应头

- -X, --request：指定 HTTP 请求的方法

  ```bash
   curl -X POST https://www.example.com  curl -X GET https://www.example.com
   or
   curl --request POST https://www.example.com  curl --request GET https://www.example.com
  ```

  



# reference

[curl用法指南](https://www.ruanyifeng.com/blog/2019/09/curl-reference.html)

https://catonmat.net/cookbooks/curl

https://www.lmlphp.com/user/64824/article/item/2671567/