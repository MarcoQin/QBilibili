#!/bin/sh
mkdir -p debug
EXDIR=`cd $(dirname $0); pwd`
cd "$EXDIR/$1"
yes | cp Makefile_Decrypt Makefile
make clean
make

#echo please input source dir:
#read FROMDIR
#echo please input output dir:
#read TODIR

FROMDIR="out_encrypt"
TODIR="out_decrypt"

rm -rf $TODIR
cp -r $FROMDIR $TODIR

deepls(){
    for x in $1/*
    do
        y=`basename $x .lua`
        if [ -f $x ]
        then
            $EXDIR/debug/decryptor "$EXDIR/$1/$y.lua" "$EXDIR/$2/$y.lua"
        fi
        if [ -d $x ]
        then
            deepls "$1/$y" "$2/$y"
        fi
    done
}

deepls $FROMDIR $TODIR

# find $TODIR -name '*.lua' -exec rm {} \;
