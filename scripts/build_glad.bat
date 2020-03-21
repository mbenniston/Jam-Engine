@echo off
echo Building glad...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\glad
cd modules\glad || goto :ERROR

premake5.exe vs2019

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" glad-workspace.sln /t:glad /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" glad-workspace.sln /t:glad /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\ || goto :ERROR

xcopy /y /s /f "modules\glad\bin\Release" "deps\glad\Release\" || goto :ERROR
xcopy /y /s /f "modules\glad\bin\Debug" "deps\glad\Debug\" || goto :ERROR
echo Built glad

goto :END

:ERROR
echo Could not build glad!

:END
