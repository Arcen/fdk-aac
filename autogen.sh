#!/bin/sh
touch README NEWS AUTHORS ChangeLog
ln -s sbr_ram.cpp libSBRdec/src/sbr_ram_dec.cpp
ln -s sbr_rom.cpp libSBRdec/src/sbr_rom_dec.cpp
autoreconf -vfi
./configure
make
mkdir include
cp libFDK/include/* include/ -r
cp libSYS/include/* include/ -r
cp libPCMutils/include/* include/ -r
cp libMpegTPDec/include/* include/ -r
cp libMpegTPEnc/include/* include/ -r
cp libSBRdec/include/* include/ -r
cp libSBRenc/include/* include/ -r
cp libAACdec/include/* include/ -r
cp libAACenc/include/* include/ -r

