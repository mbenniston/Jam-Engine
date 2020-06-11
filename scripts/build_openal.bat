@echo off
echo Building OpenAL...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\openal-soft
cd modules\openal-soft || goto :ERROR

md build
cd build || goto :ERROR
cmake -D ALSOFT_EXAMPLES=OFF -D ALSOFT_TESTS=OFF .. || goto :ERROR

python.exe .\..\..\..\replacer.py OpenAL.vcxproj "<RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>" -oo
python.exe .\..\..\..\replacer.py OpenAL.vcxproj "<RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreaded</RuntimeLibrary>" -oo

python.exe .\..\..\..\replacer.py ex-common.vcxproj "<RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>" -oo
python.exe .\..\..\..\replacer.py ex-common.vcxproj "<RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreaded</RuntimeLibrary>" -oo

python.exe .\..\..\..\replacer.py common.vcxproj "<RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>" -oo
python.exe .\..\..\..\replacer.py common.vcxproj "<RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreaded</RuntimeLibrary>" -oo

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" OpenAL.sln /t:ALL_BUILD;ex-common /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" OpenAL.sln /t:ALL_BUILD;ex-common /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\..\ || goto :ERROR

xcopy /y /s /f "modules\openal-soft\build\Release" "deps\openal-soft\Release\" || goto :ERROR
xcopy /y /s /f "modules\openal-soft\build\Debug" "deps\openal-soft\Debug\" || goto :ERROR
echo Built OpenAL

goto :END

:ERROR
echo Could not build OpenAL!

:END