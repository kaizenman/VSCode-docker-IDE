#!/bin/bash

cp -v /usr/include /include -R

mkdir /include/machine
cp /usr/include/endian.h /include/machine/

mkdir /include/android-sdk
find /opt/android-sdk/ -name '*.h' -exec cp -v --parents \{\} /include/android-sdk \;

mkdir /include/android-sdk/llvm-libc++
cp -v /opt/android-sdk/ndk-bundle/sources/cxx-stl/llvm-libc++/include /include/android-sdk/llvm-libc++ -R