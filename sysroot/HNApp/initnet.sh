#!/bin/sh                                                                       
                                                                                
ip route | awk '{print $1}' | while read line; do ip route del $line; done      
#ifconfig eth0 0.0.0.0 up                                                       
#ifconfig eth0 192.168.0.104 netmask 255.255.255.0 up                           
#route add default gw 192.168.0.1 netmask 0.0.0.0 dev eth0                      
#echo nameserver 192.168.0.1 > /etc/resolv.conf                                 
                                                                                
ifconfig wlan0 0.0.0.0 up                                                       
ifconfig wlan0 192.168.69.145 netmask 255.255.255.0                             
route add default gw 192.168.69.1 netmask 0.0.0.0 dev wlan0                     
echo nameserver 192.168.69.1 > /etc/resolv.conf                                 
              
