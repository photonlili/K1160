#!/bin/sh

cp -f ../build-K1160PRO-mips_32-Release/K1160PRO ./HNApp/
rm -f upgrade.tar.gz
tar czvf upgrade.tar.gz etc/ HNApp/ usr/

