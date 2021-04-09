- **Python2.7 PIP升级后执行命令报错： sys.stderr.write(fERROR {exc})解决方法**

  **问题原因：**

  Python 2.7已于2020年1月1日到期，请停止使用。请升级您的Python，因为不再维护Python 2.7。pip 21.0将于2021年1月停止对Python 2.7的支持。pip 21.0将删除对此功能的支持。解决此问题并继续使用不受支持的Python 2.7，不应升级到最新的pip版本，而应升级到<21的版本。

  **解决方法**：

  ```bash
  pip install --upgrade "pip < 21.0"
  ```

  或者

  ```bash
  wget https://bootstrap.pypa.io/2.7/get-pip.py 或 curl https://bootstrap.pypa.io/2.7/get-pip.py --output get-pip.py
  python get-pip.py
  ```

  **references:**

  ​	https://www.cjavapy.com/article/1605/

  ​	https://www.pythonheidong.com/blog/article/859981/53f6c3678fac74a047bd/