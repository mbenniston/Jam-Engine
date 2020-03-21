@echo off
echo Building ALUT...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\ALUT
cd modules\freealut || goto :ERROR

md build
cd build || goto :ERROR
cmake .. -D BUILD_STATIC=ON  -D OPENAL_INCLUDE_DIR="../../openal-soft/include/AL/" -D OPENAL_LIBRARY="../../openal-soft/build/Debug/OpenAL32.lib" || goto :ERROR

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" Alut.sln /t:ALL_BUILD /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" Alut.sln /t:ALL_BUILD /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\..\ || goto :ERROR

xcopy /y /s /f "modules\freealut\build\src\Release" "deps\freealut\Release\" || goto :ERROR
xcopy /y /s /f "modules\freealut\build\src\Debug" "deps\freealut\Debug\" || goto :ERROR
echo Built ALUT

goto :END

:ERROR
echo Could not build ALUT!

:END