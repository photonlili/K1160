#!/bin/sh

rm -f ../sysroot/HNApp/K1160PRO
cp -f ../build-K1160PRO-mips_32-Release/K1160PRO ../sysroot/HNApp/
rm -f upgrade.tar.gz
mkdir -p sysroot
cp -fr ../sysroot/* sysroot 
rm -fr sysroot/HNApp/db
rm -fr sysroot/HNApp/conf
tar czvf upgrade.tar.gz -C sysroot/ HNApp etc/init.d


