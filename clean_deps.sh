#!/bin/sh

echo Cleaning deps
cd deps || exit
rm * -r
touch .gitkeep 
cd ..

echo Cleaning modules
cd modules
rm physfs -r
rm glfw -r    
rm fmt -r   
rm openal-soft -r
rm freealut -r
rm glad -r

echo "Re-adding modules"
git submodule update --init --recursive

cd ./../