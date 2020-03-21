@echo off
echo Cleaning deps
cd deps
rd /s /q . 2>nul
copy nul .gitkeep 
cd .\..\

echo Cleaning modules
cd modules
rd /s /q physfs   2>nul
rd /s /q glfw     2>nul
rd /s /q fmt      2>nul
rd /s /q openal-soft   2>nul
rd /s /q freealut 2>nul

echo "Re-adding modules"
git submodule update --init --recursive

cd .\..\

pause