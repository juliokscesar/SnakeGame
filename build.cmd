g++ -o build/app src/main.cpp src/Shader.cpp src/StaticMesh.cpp src/Entity.cpp ext/glad/src/glad.c ext/imgui/imgui.cpp ext/imgui/imgui_draw.cpp ext/imgui/imgui_tables.cpp ext/imgui/imgui_widgets.cpp ext/imgui/backends/imgui_impl_glfw.cpp ext/imgui/backends/imgui_impl_opengl3.cpp -Iext/ -Iext/glad/include/ -Iext/glfw-win32/include/ -Iext/glm/ -Iext/imgui/ -Lext/glfw-win32/lib-mingw/ -lglfw3dll -lopengl32