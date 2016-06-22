#!/bin/sh

rm -f ../sysroot/HNApp/K1160PRO
cp -f ../build-K1160PRO-mips_32-Release/K1160PRO ../sysroot/HNApp/
rm -f upgrade.tar.gz
tar czvf upgrade.tar.gz -C ../sysroot/ HNApp usr etc

