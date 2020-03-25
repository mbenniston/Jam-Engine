#!/bin/bash
echo Building physfs...
# /Jam-Engine
cd ./../ || exit
# /Jam-Engine/modules/physfs
cd modules/physfs || exit

mkdir -p build
cd build || exit
cmake .. || exit

make config=debug || exit
mkdir -p "../../../deps/physfs/Debug/" && cp "./" "../../../deps/physfs/Release" -r || exit

make config=release || exit
mkdir -p "../../../deps/physfs/Release/" && cp "./" "../../../deps/physfs/Debug" -r || exit

# /Jam-Engine
cd ./../../../ || exit

echo Built physfs


