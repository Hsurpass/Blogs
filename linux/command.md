## SCP

- 从远程拷贝多个文件到本地

  ```
  scp USER@HOST:/\{ 1.txt,2.json,3.py,4.sh \}
  ```
  
- 从远程拷贝多个文件，多个文件夹到本地

  ```
  scp -r USER@HOST:/\{ 1.txt,2.json,3.py,4.sh,folder \}
  ```

  



**references:**

https://www.binarytides.com/linux-scp-command/