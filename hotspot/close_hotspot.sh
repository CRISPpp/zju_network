#!/bin/bash
source hotspot.conf
nmcli connection down $HOTSPOT_NAME
nmcli connection delete $HOTSPOT_NAME