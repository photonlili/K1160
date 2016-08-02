#!/bin/sh

cp -fr ../sysroot/HNApp ./
cp -fr ../sysroot/etc ./
cp -fr ../sysroot/usr ./


rm -f HNApp/K1160PRO
cp -f ../build-K1160PRO-mips_32-Release/K1160PRO HNApp/


cp -fr DPApp/* HNApp/


rm -f upgrade.tar.gz

tar czvf upgrade.tar.gz HNApp etc usr


