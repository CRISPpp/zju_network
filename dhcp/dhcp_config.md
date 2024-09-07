# By the way you can modify your hotspot network segment to control the assigned IP addresses or use the tool below

# change NetworkManagerConf
```
vim /etc/NetworkManager/NetManager.conf
```
```
[main]
plugins=ifupdown,keyfile
dns=dnsmasq
```

# add dhcp config
```
vim /etc/NetworkManager/dnsmasq.d/dnsmasq.conf
```
```
interface=wlp2s0
dhcp-range=192.168.100.10,192.168.100.200,24h
```
# restart NetworkManager
```
systemctl restart NetworkManager
```