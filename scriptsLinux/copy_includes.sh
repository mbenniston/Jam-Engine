#!/bin/bash
pushd .

cd ..
cp "modules/openal-soft/include/AL/." "include/AL" -r
cp "modules/freealut/include/AL/." "include/AL" -r
cp "modules/fmt/include/." "include" -r
cp "modules/glm/glm/." "include/glm" -r
cp "modules/json/single_include/nlohmann/json.hpp" "include/json.hpp"
cp "modules/glad/Debug/include/KHR/." "include/KHR" -r

popd 