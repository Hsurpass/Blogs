

```bash
sudo docker run -d 
	--name gitlab 
	--hostname 127.0.0.1 
	-p 443:443 # https
	-p 88:80   # http
	-p 2222:22 # ssh
	--restart always
	-v /opt/gitlab/config:/etc/gitlab # 主机:docker
	-v /opt/gitlab/logs:/var/log/gitlab
	-v /opt/gitlab/data:/var/opt/gitlab
	gitlab/gitlab-ce:latest
```





reference:

https://docs.gitlab.cn/docs/jh/ci/#step-1-create-a-.gitlab-ci.yml-file
