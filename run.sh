#!/bin/bash
mkdir -p build/QBilibili.app/Contents/Resources
yes | cp -rf src/lua/scripts/*.lua build/QBilibili.app/Contents/Resources
cd build;
qmake ../QBilibili.pro
make
./QBilibili.app/Contents/MacOS/QBilibili
