#!/bin/bash
source bond.conf
nmcli con down $BOND_NAME
nmcli con down bond0-slave1
nmcli con down bond0-slave2
nmcli con del $BOND_NAME
nmcli con del bond0-slave1
nmcli con del bond0-slave2
ip route del default
ip route add default via 10.82.29.1 dev $IFACE1 proto dhcp metric 100 
ip route add default via 10.82.29.1 dev $IFACE2 proto dhcp metric 200 
# ip link set $BOND_NAME down
# ip link set $IFACE1 nomaster
# ip link set $IFACE2 nomaster
# ip link delete $BOND_NAME type bond
# ip link set $IFACE1 up
# ip link set $IFACE2 up
