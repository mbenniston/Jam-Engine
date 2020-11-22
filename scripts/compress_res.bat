@echo off

pushd . 
del ..\obj\default_res.zip
cd ..\res\
powershell Compress-Archive * ..\obj\default_res.zip
cd ..\

cd modules/packer
premake5.exe vs2019 

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" packer.sln /property:Configuration=Debug 
cd ..\..\

.\modules\packer\packer -i obj\default_res.zip -o src\Gen\default_res.c -d src\Gen\default_res.h -v DEFAULT_RES_SRC
popd 