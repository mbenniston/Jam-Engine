#!/bin/bash
echo Building GLFW...
# /Jam-Engine
cd ./../ || exit
# /Jam-Engine/modules/glfw
cd modules/glfw || exit

mkdir -p build
cd build || exit
cmake .. || exit

make -j4 config=debug || exit
mkdir -p "../../../deps/glfw/Debug/" && cp "src/" "../../../deps/glfw/Debug/" -r || exit

make -j4 config=release || exit
mkdir -p "../../../deps/glfw/Release/" && cp "src/" "../../../deps/glfw/Release/" -r || exit

# /Jam-Engine
cd ./../../../ || exit

echo Built GLFW


