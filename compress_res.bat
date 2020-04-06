@echo off

pushd . 
del .\obj\default_res.zip
cd .\res\
powershell Compress-Archive * ..\obj\default_res.zip
cd ..\

cd packer
premake5.exe vs2019 

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" Res-Packer.sln /property:Configuration=Debug 
cd ..\

.\packer\packer obj\default_res.zip src/Gen\default_res DEFAULT_RES_SRC


popd 