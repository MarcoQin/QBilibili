#!/bin/sh
EXDIR=`cd $(dirname $0); pwd`
cd "$EXDIR/$1"
yes | cp Makefile_Encrypt Makefile
make clean
make

#echo please input source dir:
#read FROMDIR
#echo please input output dir:
#read TODIR

FROMDIR="lua"
TODIR="out_encrypt"

rm -rf $TODIR
cp -r $FROMDIR $TODIR

deepls(){
    for x in $1/*
    do
        y=`basename $x .lua`
        if [ -f $x ]
        then
            $EXDIR/debug/encryptor "$EXDIR/$1/$y.lua" "$EXDIR/$2/$y.lua"
        fi
        if [ -d $x ]
        then
            deepls "$1/$y" "$2/$y"
        fi
    done
}

deepls $FROMDIR $TODIR

# find $TODIR -name '*.lua' -exec rm {} \;
