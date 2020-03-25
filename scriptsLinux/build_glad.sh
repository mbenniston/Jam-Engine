#!/bin/bash
echo Building glad...
# /Jam-Engine
cd ./../ || exit
# /Jam-Engine/modules/glad
cd modules/glad || exit

premake5 gmake

make -j4 config=debug || exit
mkdir -p "../../deps/glad/Debug/" && cp "./bin/Debug/libglad.a" "../../deps/glad/Debug/libglad.a" || exit

make -j4 config=release || exit
mkdir -p "../../deps/glad/Release/" && cp "./bin/Release/libglad.a" "../../deps/glad/Release/libglad.a" || exit

# /Jam-Engine
cd ./../../../ || exit

echo Built glad


