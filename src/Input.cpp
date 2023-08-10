#include "Input.h"

#include <iostream>

#define EVENT 0
#define MODS 1

namespace Input
{
    static GLFWwindow* g_ctxWindow;
    static int lastKey = GLFW_KEY_UNKNOWN;
    static KeyEvent lastEvent = KeyEvent::UNDEFINED;

    /*
        [a][b]
        a: Key Code (GLFW_KEY_*)
        b: 0=Key Event, 1=Key Modifier
    */
    static int keyStates[349][2];

    void registerKeyState(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        keyStates[key][EVENT] = action;
        keyStates[key][MODS] = mods;
        std::cout << "Key: " << key << " Action: " << action << "\n";
    }

    void setupKeyCallback(GLFWwindow* ctxWindow)
    {
        if (!ctxWindow)
            return;
        
        glfwSetKeyCallback(ctxWindow, Input::registerKeyState);
    }
    

    void SetCtxWindow(GLFWwindow* ctxWindow)
    {
        g_ctxWindow = ctxWindow;
        setupKeyCallback(ctxWindow);
    }


    KeyEvent GetKey(int glfwKey)
    {
        if (!g_ctxWindow)
            return KeyEvent::UNDEFINED;

        return (KeyEvent)(keyStates[glfwKey][EVENT]);
    }
} 