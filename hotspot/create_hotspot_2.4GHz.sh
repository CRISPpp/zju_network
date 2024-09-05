#!/bin/bash

source hotspot.conf
nmcli connection add type wifi ifname $IFACE1 con-name $HOTSPOT_NAME autoconnect no ssid $HOTSPOT_SSID
nmcli connection modify $HOTSPOT_NAME 802-11-wireless.mode ap 802-11-wireless.band bg ipv4.addresses 192.168.100.1/24 ipv4.method shared
nmcli connection modify $HOTSPOT_NAME 802-11-wireless-security.key-mgmt wpa-psk 802-11-wireless-security.psk $HOTSPOT_PASSWORD
nmcli connection up $HOTSPOT_NAME
