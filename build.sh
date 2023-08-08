g++ -o build/app \
    src/main.cpp \
    src/Shader.cpp \
    src/StaticMesh.cpp \
    src/Entity.cpp \
    src/UIEntityManager.cpp \
    ext/glad/src/glad.c \
    ext/imgui/imgui.cpp \
    ext/imgui/imgui_draw.cpp \
    ext/imgui/imgui_tables.cpp \
    ext/imgui/imgui_widgets.cpp \
    ext/imgui/backends/imgui_impl_glfw.cpp \
    ext/imgui/backends/imgui_impl_opengl3.cpp -Iext/ -Iext/glad/include/ -Iext/glm/ -Iext/imgui/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl