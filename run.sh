#!/bin/bash

yes | cp -rf slaxml.lua md5.lua bi.lua boot.lua Colors.lua build/QBilibili.app/Contents/Resources
cd build;
qmake ../QBilibili.pro
make
./QBilibili.app/Contents/MacOS/QBilibili
