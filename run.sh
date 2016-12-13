#!/bin/bash
mkdir -p build/QBilibili.app/Contents/Resources
yes | cp -rf middleclass.lua LUBE.lua slaxml.lua md5.lua bi.lua boot.lua Colors.lua build/QBilibili.app/Contents/Resources
cd build;
qmake ../QBilibili.pro
make
./QBilibili.app/Contents/MacOS/QBilibili
