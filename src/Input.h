#pragma once

#include <GLFW/glfw3.h>

enum class KeyEvent
{
    PRESS = GLFW_PRESS,
    HOLD = GLFW_REPEAT,
    RELEASE = GLFW_RELEASE,
    UNDEFINED = GLFW_KEY_UNKNOWN
};

namespace Input
{
    void SetCtxWindow(GLFWwindow* ctxWindow);

    KeyEvent GetKey(int glfwKey);
}
