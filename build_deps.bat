@echo off

cd scripts
pushd .
call build_glfw.bat
popd

pushd .
call build_physfs.bat
popd 
pause