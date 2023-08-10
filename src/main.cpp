#include <iostream>
#include <vector>
#include <chrono>
#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "Input.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "Entity.h"
#include "UIEntityManager.h"
#include "Snake.h"

uint32_t screenWidth = 800, screenHeight = 600;

void framebufferResizeCallback(GLFWwindow* window, GLint width, GLint height);
void updateAndDrawEntities(const std::vector<Entity*>& entityDB, const Shader& shader, float deltaTime);

int main()
{
    glfwInit();

    // Basic Initialization Config
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Snake Game", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Couldn't create GLFW window\n";
        glfwTerminate();
        return 1;
    }
    // Set our current context to the window's context
    glfwMakeContextCurrent(window);

    Input::SetCtxWindow(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Couldn't initalize GLAD\n";
        return 1;
    }

    /// IMGUI
    // Setup Dear ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup ImGui Style
    ImGui::StyleColorsDark();

    // Setup ImGui Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    // Enable Mouse Cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // Setup Viewport
    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    // Enable OpenGL z-buffer for Depth Test
    glEnable(GL_DEPTH_TEST);

    // Shader Loading
    Shader mainShader("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");

    // Setup how OpenGL should sample 2D Textures with Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


    float planeVertices[] = {
        // position             // color
        // First Triangle
        -0.5f,  0.5f, 0.0f,     0.114f, 0.537f, 0.082f,   // top left
        -0.5f, -0.5f, 0.0f,     0.114f, 0.537f, 0.082f,   // bottom left
         0.5f, -0.5f, 0.0f,     0.114f, 0.537f, 0.082f,   // bottom right

        // Second Triangle
        -0.5f,  0.5f, 0.0f,     0.114f, 0.537f, 0.082f,   // top left
         0.5f,  0.5f, 0.0f,     0.114f, 0.537f, 0.082f,   // top right
         0.5f, -0.5f, 0.0f,     0.114f, 0.537f, 0.082f    // bottom right
    };
    StaticMesh planeMesh(planeVertices, sizeof(planeVertices), 6);

    /*
        Vertex Attribute 0: POSITION
        - Location = 0
        - Size = 3 (vec3)
        - Type = GL_FLOAT
        - Normalized = GL_FALSE
        - Stride = 6 * sizeof(float) (about 24 bytes) (space from 2 consecutive vertex attributes)
        - Offset = 0
    */
    planeMesh.SetVertexAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);

    /*
        Vertex Attribute 1: COLOR
        - Location = 1
        - Size = 3 (vec3)
        - Type = GL_FLOAT
        - Normalized = GL_FALSE
        - Stride = 6 * sizeof(float) (about 24 bytes) (space from 2 consecutive vertex attributes)
        - Offset = 3 * sizeof(float)
    */
    planeMesh.SetVertexAttribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    Entity plane("plane", planeMesh);
    plane.Transform.Rotation.x = -55.0f;

    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
    };
    StaticMesh cubeMesh(cubeVertices, sizeof(cubeVertices), 36);

    cubeMesh.SetVertexAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    cubeMesh.SetVertexAttribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    Snake head("Snake", cubeMesh);
    head.Transform.Position.z = 0.6f;
    head.Transform.Rotation.x = -55.0f;
    head.Transform.Scale = glm::vec3(0.1f);

    std::vector<Snake*> snakeBody;

    std::vector<Entity*> entityDB;
    entityDB.push_back(&plane);
    entityDB.push_back(&head);

    UIEntityManager entityManager(entityDB);


    // Time stuff for deltaTime
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame, currentFrame;
    lastFrame = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (Input::GetKey(GLFW_KEY_ESCAPE) == KeyEvent::PRESS)
            glfwSetWindowShouldClose(window, true);

        if (Input::GetKey(GLFW_KEY_B) == KeyEvent::PRESS)
        {
            std::cout << "B PRESS\n";
            head.BodySize++;
            char* bodyPartName = new char[7];
            sprintf(bodyPartName, "snake%n", head.BodySize);
            
            glm::vec3 newPos = head.Transform.Position + glm::vec3(0.0f, 4.0f, 0.0f);
            Snake* newPart = new Snake(std::string(bodyPartName), cubeMesh, newPos, head.Transform.Rotation, head.Transform.Scale);
            snakeBody.push_back(newPart);
            entityDB.push_back(newPart);

            delete[] bodyPartName;
        }

        currentFrame = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTimeDur = currentFrame - lastFrame;
        lastFrame = std::chrono::high_resolution_clock::now();
        float deltaTime = deltaTimeDur.count();

        // Start new ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate Shader
        mainShader.Use();

        // 3D setup
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(screenWidth / screenHeight), 0.1f, 100.0f);


        // Send Transform Matrices to shader's uniforms
        mainShader.SetUniformMat4("view", view);
        mainShader.SetUniformMat4("projection", projection);

        updateAndDrawEntities(entityDB, mainShader, deltaTime);
        entityManager.Draw(deltaTime);

        // ImGui Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        
        glfwSwapBuffers(window);
    }

    for (Snake* part : snakeBody)
            delete part;


    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebufferResizeCallback(GLFWwindow* window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
}

void updateAndDrawEntities(const std::vector<Entity*>& entityDB, const Shader& shader, float deltaTime)
{
    shader.Use();
    for (Entity* entity : entityDB)
    {
        entity->Update(deltaTime);
        shader.SetUniformMat4("model", entity->ModelMatrix);
        entity->Mesh.Draw();
    }
}
