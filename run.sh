#!/bin/bash

cd build;
qmake ../QBilibili.pro
make
./QBilibili.app/Contents/MacOS/QBilibili
