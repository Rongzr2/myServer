# 自动编译脚本
set -x
rm -rf `pwd`/build/*
cd `pwd`/build &&
    cmake .. &&
    make