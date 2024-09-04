#!/bin/bash
source bond.conf
modprobe bonding
ip link add $BOND_NAME type bond
echo balance-rr > /sys/class/net/$BOND_NAME/bonding/mode
ip link set $IFACE1 down
ip link set $IFACE2 down
ip link set $IFACE1 master $BOND_NAME
ip link set $IFACE2 master $BOND_NAME
ip link set $BOND_NAME up