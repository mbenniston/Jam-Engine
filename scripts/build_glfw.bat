@echo off
echo Building GLFW...
:: \Jam-Engine
cd .\..\ || goto :ERROR
:: \Jam-Engine\modules\glfw
cd modules\glfw || goto :ERROR

md build
cd build || goto :ERROR
cmake -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF .. || goto :ERROR

python.exe .\..\..\..\replacer.py src\glfw.vcxproj "<RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>" -oo
python.exe .\..\..\..\replacer.py src\glfw.vcxproj "<RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>" "<RuntimeLibrary>MultiThreaded</RuntimeLibrary>" -oo

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" GLFW.sln /property:Configuration=Debug || goto :ERROR
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" GLFW.sln /property:Configuration=Release || goto :ERROR

:: \Jam-Engine
cd .\..\..\..\ || goto :ERROR

xcopy /y /s /f "modules\glfw\build\src\Release" "deps\glfw\Release\" || goto :ERROR
xcopy /y /s /f "modules\glfw\build\src\Debug" "deps\glfw\Debug\" || goto :ERROR
echo Built GLFW

goto :END

:ERROR
echo Could not build GLFW!

:END

