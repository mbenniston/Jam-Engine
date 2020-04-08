@echo off
echo Building fmt...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\fmt
cd modules\fmt || goto :ERROR

md build
cd build || goto :ERROR
cmake -D FMT_TEST=OFF .. || goto :ERROR

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" FMT.sln /t:ALL_BUILD /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" FMT.sln /t:ALL_BUILD /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\..\ || goto :ERROR

xcopy /y /s /f "modules\fmt\build\Release" "deps\fmt\Release\" || goto :ERROR
xcopy /y /s /f "modules\fmt\build\Debug" "deps\fmt\Debug\" || goto :ERROR
echo Built FMT

goto :END

:ERROR
echo Could not build FMT!

:END
