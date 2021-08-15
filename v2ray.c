#include <stdio.h>
#include <stdlib.h>


FILE* config;
char uuid[40];
int mode;

int main(){
Menu:UI();
    system("clear");
    if (mode == 1) {
        install_xray();
        goto Menu;
    }
    else if (mode == 2) {
        system("systemctl stop xray");
        system("systemctl start xray");
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则xray运行正常------------------\n");
        system("ss -lp | grep xray");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 3) {
        config = fopen("/usr/local/etc/xray/uuid.conf", "r");
        fscanf(config, "%s", uuid);
        fclose(config);
        printf("----------Server Info----------\n");
        printf("port: 80\n");
        printf("UUID: %s\n", uuid);
        printf("alterId: 0\n");
        printf("tls: false\n");
        printf("network: ws\n");
        printf("ws-path: /\n");
        printf("Host: 自由修改免流参数\n");
        printf("----------Server Info----------\n");
        goto Menu;
    }
    else if (mode == 4) {
        system("vi /usr/local/etc/xray/config.json");
        system("systemctl restart xray");
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则xray运行正常------------------\n");
        system("ss -lp | grep xray");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 5) {
        printf("正在更新xray主程序. . .\n");
        system("systemctl stop xray");
        system("curl -sSL https://cdn.jsdelivr.net/gh/XTLS/Xray-install/install-release.sh | sh");
        system("systemctl start xray");
        printf("xray主程序更新完成！\n");
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则xray运行正常------------------\n");
        system("ss -lp | grep xray");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 6) {
        system("systemctl stop xray");
        goto Menu;
    }
    else {
        exit(0);
    }
    return 0;
}

int UI() {
    printf("-----------------------------------------------------------\n");
    printf("-----------------xray安装工具(80免流版)--------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("----------------------当前Kernel版本-----------------------\n");
    system("uname -sr");
    printf("-----------------------------------------------------------\n");
    printf("1.安装xray\n2.运行xray\n3.显示配置\n4.修改xray配置\n5.更新xray\n6.关闭xray\n0.退出\n");
    printf("-----------------------------------------------------------\n");
    printf("请输入:");
    scanf("%d", &mode);
    return 0;
}

int install_xray() {
    KernelUpdate(); 
    system("setenforce 0");
    system("yum install -y uuidgen bind-utils");
    printf("正在运行xray安装脚本. . .\n");
    system("curl -sSL https://cdn.jsdelivr.net/gh/XTLS/Xray-install/install-release.sh | sh");
    system("rm -rf TCPO.sh");
    printf("正在生成配置文件. . .\n");
    system("curl https://cdn.jsdelivr.net/gh/HXHGTS/xray-websocket-no-tls/config.json.1 > /usr/local/etc/xray/config.json");
    printf("正在生成UUID. . .\n");
    system("uuidgen > /usr/local/etc/xray/uuid.conf");
    config = fopen("/usr/local/etc/xray/uuid.conf", "r");
    fscanf(config, "%s", uuid);
    fclose(config);
    config = fopen("/usr/local/etc/xray/config.json", "a");
    fprintf(config, "                        \"id\": \"%s\"\n", uuid);
    fclose(config);
    system("curl https://cdn.jsdelivr.net/gh/HXHGTS/xray-websocket-no-tls/config.json.2 >> /usr/local/etc/xray/config.json");
    printf("正在启动xray并将xray写入开机引导项. . .\n");
    system("systemctl enable xray");
    system("systemctl start xray");
    system("setsebool -P httpd_can_network_connect 1");
    printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
    printf("--------------以下输出不为空则xray运行正常------------------\n");
    system("ss -lp | grep xray");
    printf("--------------------------------------------------------\n");
    printf("----------Server Info----------\n");
    printf("port: 80\n");
    printf("UUID: %s\n", uuid);
    printf("alterId: 0\n");
    printf("tls: false\n");
    printf("network: ws\n");
    printf("ws-path: /\n");
    printf("Host: 自由修改免流参数\n");
    printf("----------Server Info----------\n\n");
    printf("xray部署完成！\n");
    return 0;
}

int KernelUpdate() {
    if ((fopen("KernelUpdate.sh", "r")) == NULL) {
        printf("正在升级新内核. . .\n");
        system("wget https://cdn.jsdelivr.net/gh/HXHGTS/TCPOptimization/KernelUpdate.sh -O KernelUpdate.sh");
        system("chmod +x KernelUpdate.sh");
        printf("正在升级，将自动触发重启以应用配置. . .\n");
        system("bash KernelUpdate.sh");
    }
    else {
        system("curl -sSL https://cdn.jsdelivr.net/gh/HXHGTS/TCPOptimization/TCPO.sh | sh");
    }
    return 0;
}

