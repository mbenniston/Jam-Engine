#!/bin/bash
echo Building fmt...
# /Jam-Engine
cd ./../ || exit
# /Jam-Engine/modules/fmt
cd modules/fmt || exit

mkdir -p build
cd build || exit
cmake .. || exit

make fmt -j4 config=debug || exit
mkdir -p "../../../deps/fmt/Debug/" && cp "./" "../../../deps/fmt/Debug" -r || exit

make fmt -j4 config=release || exit
mkdir -p "../../../deps/fmt/Release/" && cp "./" "../../../deps/fmt/Release" -r || exit

# /Jam-Engine
cd ./../../../ || exit

echo Built fmt


