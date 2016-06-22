#!/bin/sh

passwd root<<EOF
0
0
EOF

/usr/bin/ts_calibrate
/usr/bin/tar xzvf /mnt/usb_sda1/upgrade.tar.gz -C /
reboot

