#!/bin/bash

source interface.conf

if [[ -z "$IFACE1" || -z "$IFACE2" ]]; then
    echo "Interface names are not set in interface.conf."
    exit 1
fi

WEIGHT1=1
WEIGHT2=1

METRIC=1000000

sudo ip route add default scope global metric $METRIC \
    nexthop via $NEXTHOP1 dev $IFACE1 weight $WEIGHT1 \
    nexthop via $NEXTHOP2 dev $IFACE2 weight $WEIGHT2