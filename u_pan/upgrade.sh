#!/bin/sh

rm /HNApp/*
/usr/bin/tar xzvf /mnt/usb_sda1/upgrade.tar.gz -C /
reboot

