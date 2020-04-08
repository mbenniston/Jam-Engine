@echo off
echo Building OpenAL...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\openal-soft
cd modules\openal-soft || goto :ERROR

md build
cd build || goto :ERROR
cmake -D ALSOFT_EXAMPLES=OFF -D ALSOFT_TESTS=OFF .. || goto :ERROR

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" OpenAL.sln /t:ALL_BUILD /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" OpenAL.sln /t:ALL_BUILD /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\..\ || goto :ERROR

xcopy /y /s /f "modules\openal-soft\build\Release" "deps\openal-soft\Release\" || goto :ERROR
xcopy /y /s /f "modules\openal-soft\build\Debug" "deps\openal-soft\Debug\" || goto :ERROR
echo Built OpenAL

goto :END

:ERROR
echo Could not build OpenAL!

:END