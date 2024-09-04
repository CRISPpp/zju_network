#!/bin/bash
source bond.conf
ip link set $BOND_NAME down
ip link set $IFACE1 nomaster
ip link set $IFACE2 nomaster
ip link delete $BOND_NAME type bond
ip link set $IFACE1 up
ip link set $IFACE2 up