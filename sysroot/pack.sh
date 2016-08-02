#!/bin/sh

rm -f HNApp/K1160PRO
cp -f ../build-K1160PRO-mips_32-Release/K1160PRO HNApp/


rm -f upgrade.tar.gz

tar czvf upgrade.tar.gz HNApp etc usr


