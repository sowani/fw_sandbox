#!/bin/bash

cp 80-local.rules /etc/udev/rules.d
cp trigger1.sh trigger2.sh /usr/local/bin
chmod +x /usr/local/bin/trigger1.sh
chmod +x /usr/local/bin/trigger2.sh
