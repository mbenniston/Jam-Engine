@echo off

pushd .

cd ..
"../modules/json/single_include/nlohmann/json.hpp"
xcopy /y /s /f "modules\openal-soft\include\AL" "include\AL\"
xcopy /y /s /f "modules\freealut\include" "include\"
xcopy /y /s /f "modules\fmt\include" "include\"
xcopy /y /s /f "modules\glm\glm" "include\glm\"
copy "modules\json\single_include\nlohmann\json.hpp" "include\json.hpp"
xcopy /y /s /f "modules\glad\Debug\include\KHR" "include\KHR\"

popd 