# 包含wan聚合、热点开启、浙大网络认证、网卡流量监控的项目
# 项目结构
## bond：bond配置虚拟网卡进行wan口聚合
### 使用
```
在bond.conf修改你的物理网卡名称（通过ip link可以看到）
./create_bond.sh
```
### 关闭
```
./close_bond.sh
```
## hotspot：开启无线热点
### 使用
```
在hotspot.conf修改你的无线网卡名称（通过ip link可以看到），以及name、ssid、password
./create_hotspot.sh
```
### 关闭
```
./close_hotspot.sh
```
## common：通用类
## login：校园网认证
```
直接执行打包好的可执行文件（在release中）
./login -u username -p password
这里的password需要抓包获取
```
## route_table：通过route_table进行wan口聚合
```
同bond
```
## xdp：网卡包监控程序-参考https://github.com/xdp-project/xdp-tutorial
```
直接执行打包好的可执行文件（在release中）
./xdp_packet_load -d 网卡名
```
