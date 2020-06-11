@echo off
echo Building Physfs...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\physfs
cd modules\physfs || goto :ERROR

md build
cd build || goto :ERROR
cmake -D PHYSFS_BUILD_SHARED=OFF .. || goto :ERROR

python.exe .\..\..\..\replacer.py physfs-static.vcxproj "<RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>" -oo
python.exe .\..\..\..\replacer.py physfs-static.vcxproj "<RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreaded</RuntimeLibrary>" -oo

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" PhysicsFS.sln /t:ALL_BUILD /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" PhysicsFS.sln /t:ALL_BUILD /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\..\ || goto :ERROR

xcopy /y /s /f "modules\physfs\build\Release" "deps\physfs\Release\" || goto :ERROR
xcopy /y /s /f "modules\physfs\build\Debug" "deps\physfs\Debug\" || goto :ERROR
echo Built Physfs

goto :END

:ERROR
echo Could not build Physfs!

:END