#!/bin/bash
echo Building freealut...
# /Jam-Engine
cd ./../ || exit
# /Jam-Engine/modules/freealut
cd modules/freealut || exit

mkdir -p build
cd build || exit
cmake .. -D BUILD_STATIC=ON  -D OPENAL_INCLUDE_DIR="../../openal-soft/include/" -D OPENAL_LIBRARY="../../openal-soft/build/libopenal.so" || exit

make config=debug || exit
mkdir -p "../../../deps/freealut/Debug/" && cp "./" "../../../deps/freealut/Release" -r || exit

make config=release || exit
mkdir -p "../../../deps/freealut/Release/" && cp "./" "../../../deps/freealut/Debug" -r || exit

# /Jam-Engine
cd ./../../../ || exit

echo Built freealut


