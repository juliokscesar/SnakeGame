#include "Input.h"

namespace Input
{
    static GLFWwindow* g_ctxWindow;

    void SetCtxWindow(GLFWwindow* ctxWindow)
    {
        g_ctxWindow = ctxWindow;
    }

    KeyEvent GetKey(int glfwKey)
    {
        return (g_ctxWindow != nullptr) ? (KeyEvent)glfwGetKey(g_ctxWindow, glfwKey) : KeyEvent::UNDEFINED;
    }
}