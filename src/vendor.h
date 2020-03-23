
#include "../modules/glm/glm/glm.hpp"

#if defined(JAM_DEBUG)
#include "../modules/glad/Debug/include/glad/glad.h"

#elif defined(JAM_RELEASE)
#include "../modules/glad/Release/include/glad/glad.h"

#else
#error build symbol not defined
#endif

#include "../modules/glfw/include/GLFW/glfw3.h"
#include "../modules/fmt/include/fmt/format.h"
#include "../modules/rlutil/rlutil.h"
#include "../modules/json/single_include/nlohmann/json.hpp"

#include "../modules/openal-soft/include/AL/al.h"
#include "../modules/openal-soft/include/AL/alc.h"
#include "../modules/openal-soft/include/AL/alext.h"

#include "../modules/freealut/include/AL/alut.h"

#include "../modules/imgui/imgui.h"

#include "../modules/stb/stb_image.h"