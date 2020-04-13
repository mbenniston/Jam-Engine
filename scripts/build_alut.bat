@echo off
echo Building ALUT...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\ALUT
cd modules\freealut || goto :ERROR

md build
cd build || goto :ERROR
cmake -D BUILD_TESTS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_STATIC=ON  -D OPENAL_INCLUDE_DIR="../../openal-soft/include/" -D OPENAL_LIBRARY="../../openal-soft/build/Debug/OpenAL32.lib" .. || goto :ERROR

python3.8.exe .\..\..\..\replacer.py src\alut_static.vcxproj "<RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>" -oo
python3.8.exe .\..\..\..\replacer.py src\alut_static.vcxproj "<RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreaded</RuntimeLibrary>" -oo

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