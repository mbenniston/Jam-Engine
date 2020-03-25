#!/bin/bash
echo Building deps

cd scriptsLinux/
pushd .
./build_glfw.sh
popd 

pushd .
./build_openal.sh
popd 

pushd .
./build_fmt.sh
popd 

pushd .
./build_glad.sh
popd 

pushd .
./build_physfs.sh
popd 

pushd .
./build_alut.sh
popd 

pushd .
./copy_includes.sh
popd 