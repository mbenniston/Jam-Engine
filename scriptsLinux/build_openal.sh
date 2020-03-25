#!/bin/bash
echo Building OpenAL...
# /Jam-Engine
cd ./../ || exit
# /Jam-Engine/modules/openal-soft
cd modules/openal-soft || exit

mkdir -p build
cd build || exit
cmake .. || exit

make -j4 config=debug || exit
mkdir -p "../../../deps/openal-soft/Debug/" && cp "./" "../../../deps/openal-soft/Debug" -r || exit

make -j4 config=release || exit
mkdir -p "../../../deps/openal-soft/Release/" && cp "./" "../../../deps/openal-soft/Release" -r || exit

# /Jam-Engine
cd ./../../../ || exit

echo Built OpenAL


