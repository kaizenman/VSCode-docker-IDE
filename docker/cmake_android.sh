#!/bin/bash

cd Projects
./gradlew assembleRelease
cp -vf /Projects/app/build/outputs/apk/release/app-release.apk /Projects/bin

rm -r .gradle
rm -r app/.externalNativeBuild
rm -r app/build
