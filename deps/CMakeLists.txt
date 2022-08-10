# glad
add_library(glad glad/include/glad/glad.h glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# glm
add_subdirectory(glm)

# imgui
add_library(imgui 
	imgui/imconfig.h
	imgui/imgui.cpp
	imgui/imgui.h
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_internal.h
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_glfw.h
	imgui/backends/imgui_impl_opengl3.cpp
	imgui/backends/imgui_impl_opengl3.h)
target_include_directories(imgui PUBLIC imgui glfw/include)