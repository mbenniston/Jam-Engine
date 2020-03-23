#pragma once

struct GLFWwindow;

namespace ImGuiHelper
{
    void setup(GLFWwindow* window);
    void startFrame();
    void endFrame(GLFWwindow* window);
    void cleanup();
}