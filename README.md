# xray-websocket--no-tls

## 警告⚠：此技术仅限用于个人搭建游戏加速器使用！！！若用于其他违法目的，后果自负！！！

手动搭建xray服务器(vmess+websocket)，基于ws实现免流

KVM/XEN机器执行(CentOS7):

`yum install -y gcc wget && wget https://raw.githubusercontent.com/HXHGTS/xray-websocket-no-tls/main/v2ray.c -O v2ray.c && chmod +x v2ray.c && gcc -o v2ray v2ray.c && ./v2ray`

第一次点击安装后会自动升级系统内核并触发重启，重启后输入

`./v2ray`

### 安装前准备：

1.脚本仅支持CentOS7系统

2.脚本执行需要root权限登录系统，AWS等特殊机型打开root权限方法[看这里](https://hxhgts.github.io/AWSECSRoot/)

3.请在服务器后台防火墙放行tcp80(http)端口
