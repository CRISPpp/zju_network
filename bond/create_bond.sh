#!/bin/bash
source bond.conf
modprobe bonding
nmcli con add type bond con-name $BOND_NAME ifname  $BOND_NAME mode balance-rr
ip addr add 10.82.29.235/24 dev bond0
nmcli con add type ethernet con-name bond0-slave1 ifname  $IFACE1  master bond0
nmcli con add type ethernet con-name bond0-slave2 ifname  $IFACE2  master bond0
nmcli con down $BOND_NAME
nmcli con up bond0-slave1
nmcli con up bond0-slave2
nmcli con up $BOND_NAME
ip route del default
ip route add default via 10.82.29.1 dev bond0 proto static metric 100000
# ip link add $BOND_NAME type bond
# echo balance-rr > /sys/class/net/$BOND_NAME/bonding/mode
# ip addr add 10.82.29.235/24 dev bond0
# ip link set $IFACE1 down
# ip link set $IFACE2 down
# ip link set $IFACE1 master $BOND_NAME
# ip link set $IFACE2 master $BOND_NAME
# ip link set $BOND_NAME up